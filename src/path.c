/* path.c
 * by burlapjack 2021
 * functions and data structures related
 * to pathfinding.
 */

#include <stdlib.h>
#include <ncurses.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>
#include "../include/path.h"
#include "../include/map.h"

/*====================== Opaque Data Types =================================================================================*/



int path_get_manhattan_distance(int x1, int y1, int x2, int y2){
	return abs(x1 - x2) + abs(y1 - y2);
}

int path_count_floor(MapData *m){
	int count = 0;
	for(int i = 0; i < m->map_height; i++){
		for(int j = 0; j < m->map_width; j++){
			if(m->map[ (i * m->map_width) + j] == m->floor){
				count++;
			}
		}
	}
	return count;
}

/*---------------------- Copy contents of indicated open_list node into closed_list ------------------------------------------*/
void path_closed_list_add_node(PathGraph *g, int open_list_index){
	g->closed_list[g->number_of_closed_nodes] = g->open_list[open_list_index];
	g->number_of_closed_nodes++;
	for(int i = open_list_index; i < g->number_of_open_nodes - 1; i++){ /* remove target node by overwriting it. */
		g->open_list[i] = g->open_list[i + 1];
	}
	if(g->number_of_open_nodes > 0) g->number_of_open_nodes -= 1;
}

/*---------------------- Deallocate PathGraph memory --------------------------------------------------------------------------*/
void path_free_graph(PathGraph *g){
	free(g->open_list);
	free(g->closed_list);
	free(g);
}

/*---------------------- Add new node to open_list ---------------------------------------------------------------------------*/
void path_open_list_add_node(PathGraph *g, int x, int y){
	int i = g->number_of_open_nodes;
	g->open_list[i].x = x;
	g->open_list[i].y = y;
	//g->open_list[i].g = g->open_list[g->current_index].g + 1;
	//g->open_list[i].h = path_get_manhattan_distance(x, y, g->endx, g->endy); /* h value: heuristic distance between this node and the final destination. */
	//g->open_list[i].f = (g->open_list[i].g + g->open_list[i].h);
	g->open_list[i].parent_index = g->current_index;
	g->number_of_open_nodes++; /* iterate open_node count */
}

/*---------------------- Get the closed_list[] index via map coords ----------------------------------------------------------*/
int path_closed_list_get_index(PathGraph *g, int x, int y){
	int index;
	for( int i = 0; i < g->number_of_closed_nodes; i++){
		if (g->closed_list[i].x == x && g->closed_list[i].y == y){
			index = i;
			break;
		}
	}
	return index;
}
/*--------------------- Return the index of the node that has the lowest f value, and is a child of current_index node. ------*/
int path_open_list_get_index_lowest_f(PathGraph *g){
	int lowest = INT_MAX;
	int target_index;
	for( int i = 0; i < g->number_of_open_nodes; i++){
		if( g->open_list[i].f <= lowest  && g->open_list[i].parent_index == g->current_index) {
			lowest = g->open_list[i].f;
			target_index = i;
		}
	}
	return target_index;
}

/*---------------------- Get the open_list[] index via map coords ------------------------------------------------------------*/
int path_open_list_get_index(PathGraph *g, int x, int y){
	int index;
	for( int i = 0; i < g->number_of_open_nodes - 1; i++){
		if (g->open_list[i].x == x && g->open_list[i].y == y){
			index = i;
			break;
		}
	}
	return index;
}

/*---------------------- Check to see if the given criteria are matched by a node in any list  -------------------------------*/
bool path_node_exists_in_lists(PathGraph *g, int x, int y){
	bool exists = false;
	/* checked open_list */
	for(int i = 0; i < g->number_of_open_nodes; i++){
		if( g->open_list[i].x == x && g->open_list[i].y == y){
			exists = true;
			break;
		}
	}
	if(exists == false){
		/* check closed_list */
		for(int i = 0; i < g->number_of_closed_nodes; i++){
			if( g->closed_list[i].x == x && g->closed_list[i].y == y){
				exists = true;
				break;
			}
		}
	}
	return exists;
}


/*--------------------- Return true if the node with the given coordinates exist in the open list. -------------------------*/
bool path_node_exists_in_open_list(PathGraph *g, int x, int y){
	bool exists = false;
	for(int i = 0; i < g->number_of_open_nodes; i++){
		if( g->open_list[i].x == x && g->open_list[i].y == y){ /* find coordinate match */
			exists = true;
			break;
		}
	}
	return exists;
}

/*--------------------- Updates the g and f value of a node if it already has been added to the open_list. ------------------*/
void path_node_update(PathGraph *g, int nx, int ny){
	int ni = path_open_list_get_index(g, nx, ny);
	int existing_f = g->open_list[ni].f; /* the current f value of this node. */
	int new_f = g->open_list[g->current_index].g + 1 + g->open_list[ni].h; /* the possible new f value */
	if(existing_f > new_f ){ /* check to see if this node is better off with a new parent node. */
		g->open_list[ni].parent_index = g->current_index; /* set parent */
		g->open_list[ni].g = g->open_list[g->current_index].g + 1; /* refresh g value. */
		g->open_list[ni].f = new_f; /* refresh f value. */
	}
}

/*--------------------- Fill an area with a given symbol/tile. --------------------------------------------------------------*/
void path_flood_fill(MapData *m, int rand_x, int rand_y, char symbol){

	int current_index = 0;
	int number_of_nodes = 1;
	int list_size = path_count_floor(m);
	FloodNode node_list[list_size];

	for(int i = 0; i < list_size; i++){
		node_list[i].x = -1;
		node_list[i].y = -1;
	};

	/* Add the first node outside of the main loop. */
	node_list[0].x = rand_x;
	node_list[0].y = rand_y;
	m->map[(rand_y * m->map_width) + rand_x] = symbol;

	int nx = node_list[0].x;
	int ny = node_list[0].y;

	int d[8][2];
	d[0][0] =  0;  d[0][1] = -1;   /* north     */
	d[1][0] =  1;  d[1][1] = -1;   /* northeast */
	d[2][0] =  1;  d[2][1] =  0;   /* east      */
	d[3][0] =  1;  d[3][1] =  1;   /* southeast */
	d[4][0] =  0;  d[4][1] =  1;   /* south     */
	d[5][0] = -1;  d[5][1] =  1;   /* southwest */
	d[6][0] = -1;  d[6][1] =  0;   /* west      */
	d[7][0] = -1;  d[7][1] = -1;   /* northwest */

	while(1){ /* main loop */

		nx = node_list[current_index].x;
		ny = node_list[current_index].y;

		//printw("\n%2d %2d",nx, ny);
		/*---- check the map for neighboring nodes ---- */
		for(int i = 0; i < 8; i++){
				if(m->map[ (ny + d[i][1]) * m->map_width + nx + d[i][0] ] == m->floor){ /* check for floor tile on the map. */
					int exists = 0;

					for(int j = 0; j < number_of_nodes; j++){
						if( node_list[j].x == nx + d[i][0] && node_list[j].y == ny + d[i][1]) {
							exists = 1;
							break;
						}
					}
					if(exists == 0){
						node_list[number_of_nodes].x = nx + d[i][0];
						node_list[number_of_nodes].y = ny + d[i][1];
						number_of_nodes++;
						m->map[ ( (ny + d[i][1]) * m->map_width) +  nx + d[i][0] ] = 'o';
					}
				}
		}
		current_index+=1;
		if(node_list[current_index].x == -1) break;
	}
}
