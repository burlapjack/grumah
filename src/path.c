/* path.c
 * by burlapjack 2021
 * functions and data structures related
 * to pathfinding.
 */

#include <stdlib.h>
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
void path_flood_list_add_node(FloodGraph *g, int x, int y){
		g->node_list[g->number_of_nodes].x = x;
		g->node_list[g->number_of_nodes].y = y;
		g->number_of_nodes += 1; /* iterate open_node count */
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

/*---------------------- Check to see if the given criteria are matched by a flood node --------------------------------------*/
bool path_node_exists_in_flood_list(FloodGraph *g, int x, int y){
	bool exists = false;
	int n = max_int(g->number_of_nodes - 1, 0);
	for(int i = 0; i < n; i++){
		if( g->node_list[i].x == x && g->node_list[i].y == y){
			exists = true;
			break;
		}
	}
	return exists;
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

	//FloodGraph *g = malloc( sizeof (*g) ); /* allocate new graph */
	FloodGraph g;
	g.number_of_nodes = path_count_floor(m); /* record the total number of possible nodes. In this case, the number of floor tiles on the map. */
	g.node_list = malloc( sizeof (*(g.node_list)) * g.number_of_nodes ); /* allocate open_list */

	for(int i = 0; i < g.number_of_nodes; i++){
		g.node_list[i].x = 0;
		g.node_list[i].y = 0;
	}



	/* Add the first node outside of the main loop. */
	g.node_list[0].x = rand_x;
	g.node_list[0].y = rand_y;
	m->map[rand_y * m->map_width + rand_x] = symbol;

	g.current_index = 0; /* initialize the current index. */

	int nx = 0;
	int ny = 0;
	int north,northeast,east,southeast,south,southwest,west,northwest;

	while(1){ /* main loop */

		nx = g.node_list[g.current_index].x; /* the x coord of the current node */
		ny = g.node_list[g.current_index].y; /* the y coord of the current node */

		north      = (ny - 1) * m->map_width + nx;
		northeast  = (ny - 1) * m->map_width + nx + 1;
		east       = ny * m->map_width + nx + 1;
		southeast  = (ny + 1) * m->map_width + nx + 1;
		south      = (ny + 1) * m->map_width + nx;
		southwest  = (ny + 1) * m->map_width + nx - 1;
		west       = ny * m->map_width + nx - 1;
		northwest  = (ny - 1) * m->map_width + nx - 1;


		/*---- check the map for neighboring nodes ---- */

		if(ny > 1){ /* North  ny - 1, nx*/
			if(m->map[north] == m->floor ){
				if(!path_node_exists_in_flood_list(&g, nx, ny-1) ){
					path_flood_list_add_node(&g, nx, ny - 1); /* if this neighbor doesn't exist in the node_list, add it. */
					m->map[north] = symbol;
				}
			}
		}
		if(nx < m->map_width - 1 && ny > 1){ /* NorthEast nx + 1, ny - 1*/
			if( m->map[northeast] == m->floor ){
				if( !path_node_exists_in_flood_list(&g, nx + 1, ny - 1) ){
					path_flood_list_add_node(&g, nx + 1, ny - 1);
					m->map[northeast] = symbol;
				}
			}
		}
		if(nx < m->map_width - 1){ /* East nx + 1, ny*/
			if( m->map[east] == m->floor ){
				if( !path_node_exists_in_flood_list(&g, nx + 1, ny) ){
					path_flood_list_add_node(&g, nx + 1, ny); /* if this neighbor doesn't exist in any of the lists, add it to open_list */
					m->map[east] = symbol;
				}
			}
		}
		if(nx < m->map_width - 1 && ny < m->map_height - 1){ /* SouthEast nx + 1, ny + 1*/
			if( m->map[southeast] == m->floor ){
				if( !path_node_exists_in_flood_list(&g, nx + 1, ny + 1) ){
					path_flood_list_add_node(&g, nx + 1, ny + 1); /* if this neighbor doesn't exist in any of the lists, add it to open_list */
					m->map[southeast] = symbol;
				}
			}
		}
		if(ny < m->map_height - 1){ /* South  nx, ny + 1 */
			if( m->map[south] == m->floor ){
				if( !path_node_exists_in_flood_list(&g, nx, ny + 1) ){
					path_flood_list_add_node(&g, nx, ny + 1); /* if this neighbor doesn't exist in any of the lists, add it to open_list */
					m->map[south] = symbol;
				}
			}
		}
		if(nx > 1 && ny < m->map_height - 1){ /* Southwest nx - 1, ny + 1*/
			if( m->map[southwest] == m->floor ){
				if( !path_node_exists_in_flood_list(&g, nx - 1, ny + 1) ){
					path_flood_list_add_node(&g, nx - 1, ny + 1); /* if this neighbor doesn't exist in any of the lists, add it to open_list */
					m->map[southwest] = symbol;
				}
			}
		}
		if(nx > 1){ /* West  nx - 1, ny */
			if( m->map[west] == m->floor ){
				if( !path_node_exists_in_flood_list(&g, nx - 1, ny) ){
					path_flood_list_add_node(&g, nx - 1, ny); /* if this neighbor doesn't exist in any of the lists, add it to open_list */
					m->map[west] = symbol;
				}
			}
		}
		if(nx > 1 && ny > 1){/* Northwest nx - 1, ny - 1 */
			if( m->map[northwest] == m->floor ){
				if( !path_node_exists_in_flood_list(&g, nx - 1, ny - 1) ){
					path_flood_list_add_node(&g, nx - 1, ny - 1); /* if this neighbor doesn't exist in any of the lists, add it to open_list */
					m->map[northwest] = symbol;
				}
			}
		}
		if(g.current_index < (g.number_of_nodes)) g.current_index++;
		else break;
	}
}
