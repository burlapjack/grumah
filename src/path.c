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

struct node{
	int x,y;
	int f,g,h;
	int parent_index;
};

struct graph{
	int number_of_nodes;
	int startx,starty;
	int endx, endy;
	int number_of_open_nodes;
	int number_of_closed_nodes;
	int current_index;
	MapNode *open_list;
	MapNode *closed_list;
};

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
void path_closed_list_add_node(MapGraph *g, int open_list_index){
	g->closed_list[g->number_of_closed_nodes] = g->open_list[open_list_index];
	g->number_of_closed_nodes++;
	for(int i = open_list_index; i < g->number_of_open_nodes - 1; i++){ /* remove target node by overwriting it. */
		g->open_list[i] = g->open_list[i + 1];
	}
	if(g->number_of_open_nodes > 0) g->number_of_open_nodes -= 1;
}

/*---------------------- Deallocate MapGraph memory --------------------------------------------------------------------------*/
void path_free_graph(MapGraph *g){
	free(g->open_list);
	free(g->closed_list);
	free(g);
}

/*---------------------- Add new node to open_list ---------------------------------------------------------------------------*/
void path_open_list_add_node(MapGraph *g, int x, int y){
	int i = g->number_of_open_nodes;
	g->open_list[i].x = x;
	g->open_list[i].y = y;
	g->open_list[i].g = g->open_list[g->current_index].g + 1;
	g->open_list[i].h = path_get_manhattan_distance(x, y, g->endx, g->endy); /* h value: heuristic distance between this node and the final destination. */
	g->open_list[i].f = (g->open_list[i].g + g->open_list[i].h);
	g->open_list[i].parent_index = g->current_index;
	g->number_of_open_nodes++; /* iterate open_node count */
}

/*---------------------- Get the closed_list[] index via map coords ----------------------------------------------------------*/
int path_closed_list_get_index(MapGraph *g, int x, int y){
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
int path_open_list_get_index_lowest_f(MapGraph *g){
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
int path_open_list_get_index(MapGraph *g, int x, int y){
	int index;
	for( int i = 0; i < g->number_of_open_nodes; i++){
		if (g->open_list[i].x == x && g->open_list[i].y == y){
			index = i;
			break;
		}
	}
	return index;
}

/*---------------------- Check to see if the given criteria are matched by a node in any list  -------------------------------*/
bool path_node_exists_in_lists(MapGraph *g, int x, int y){
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
bool path_node_exists_in_open_list(MapGraph *g, int x, int y){
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
void path_node_update(MapGraph *g, int nx, int ny){
	int ni = path_open_list_get_index(g, nx, ny);
	int existing_f = g->open_list[ni].f; /* the current f value of this node. */
	int new_f = g->open_list[g->current_index].g + 1 + g->open_list[ni].h; /* the possible new f value */
	if(existing_f > new_f ){ /* check to see if this node is better off with a new parent node. */
		g->open_list[ni].parent_index = g->current_index; /* set parent */
		g->open_list[ni].g = g->open_list[g->current_index].g + 1; /* refresh g value. */
		g->open_list[ni].f = new_f; /* refresh f value. */
	}
}

/*---------------------- Record neighbor information  ------------------------------------------------------------------------*/
void path_node_get_neighbors(MapData *m, MapGraph *g){

	int nx = g->open_list[g->current_index].x; /* nx and ny = shorthand for current node x and y position */
	int ny = g->open_list[g->current_index].y;

	/*---- check the map for neighboring nodes ---- */
	if( m->map[(ny - 1) * m->map_width + nx] == m->floor ){ /* North */
		if(!path_node_exists_in_lists(g, nx, ny-1) )  path_open_list_add_node(g, nx, ny - 1); /* if this neighbor doesn't exist in any of the lists, add it to open_list */
		else if(path_node_exists_in_open_list(g, nx, ny - 1)) path_node_update(g, nx, ny - 1); /* if this neighbor is already in the open_list, update it if needed. */
	}
	if( m->map[(ny + 1) * m->map_width + nx] == m->floor ){ /* South */
		if( !path_node_exists_in_lists(g, nx, ny+1) ) path_open_list_add_node(g, nx, ny + 1); /* if this neighbor doesn't exist in any of the lists, add it to open_list */
		else if( path_node_exists_in_open_list(g, nx, ny + 1) ) path_node_update(g, nx, ny + 1);/* if this neighbor is already in the open_list */
	}

	if( m->map[ny * m->map_width + nx + 1] == m->floor ){ /* East */
		if( !path_node_exists_in_lists(g, nx + 1, ny) )  path_open_list_add_node(g, nx + 1, ny); /* if this neighbor doesn't exist in any of the lists, add it to open_list */
		else if(path_node_exists_in_open_list(g, nx + 1, ny)) path_node_update(g, nx + 1, ny); /* if this neighbor is already in the open_list */
	}

	if( m->map[ny * m->map_width + nx - 1] == m->floor ){ /* West */
		if( !path_node_exists_in_lists(g, nx - 1, ny) ) path_open_list_add_node(g, nx - 1, ny); /* if this neighbor doesn't exist in any of the lists, add it to open_list */
		else if(path_node_exists_in_open_list(g, nx - 1, ny )) path_node_update(g, nx - 1, ny); /* if this neighbor is already in the open_list */
	}
}

/*---------------------- Check to see if it is possible to go from point a to b ----------------------------------------------*/
bool path_is_contiguous(MapData *m, int ax, int ay, int bx, int by){
	bool contiguous = false;
	MapGraph *g = malloc( sizeof (*g) ); /* allocate new graph */
	g->number_of_nodes = path_count_floor(m); /* record the total number of possible nodes. In this case, the number of floor tiles on the map. */
	g->number_of_open_nodes = 0;
	g->number_of_closed_nodes = 0;
	g->open_list = malloc( sizeof (*(g->open_list)) * g->number_of_nodes ); /* allocate open_list */
	g->closed_list = malloc( sizeof (*(g->open_list)) * g->number_of_nodes ); /* allocate closed_list */
	g->startx = ax; /* record starting and ending node positions in the graph. */
	g->starty = ay;
	g->endx = bx;
	g->endy = by;

	/* add the starting node to open_list */
	g->open_list[0].x = ax;
	g->open_list[0].y = ay;
	g->open_list[0].parent_index = 0;
	g->open_list[0].h = path_get_manhattan_distance(ax, ay, bx, by);
	g->open_list[0].g = 0;
	g->open_list[0].f = g->open_list[0].h;
	g->number_of_open_nodes = 1;
	g->current_index = 0;

	/* The main loop */
	while(g->open_list[g->current_index].x != bx && g->open_list[g->current_index].y != by){ /* "while the current node is not the final node " */

		path_node_get_neighbors(m, g); /* 1. get current node's neighbors and calculate their h and g values. Then add those nodes to open_list. */

		if( g->current_index == path_open_list_get_index_lowest_f(g) ){ /* 2a. FAIL, PATH BLOCKED condition: destination not reachable. */
			contiguous = false;
			break;
		}
		else{
			path_closed_list_add_node(g, g->current_index); /* 2b. SUCCESS, PATH CONTINUES condition: put the current node into closed_list */
			g->current_index = path_open_list_get_index_lowest_f(g);
		}
	} /* end of main loop. */

	if( g->open_list[g->current_index].x == bx && g->open_list[g->current_index].y == by ){ /* check to see if destination has been reached */
		contiguous = true; /* path is found, set contiguous to true */

		for(int i = 0; i < g->number_of_closed_nodes; i++){ /* for testing */
			m->map[g->closed_list[i].y * m->map_width + g->closed_list[i].x] = 'P';
		}

	}
	path_free_graph(g); /* deallocate graph data */
	return contiguous;
}

void path_flood_fill(MapData *m, int rand_x, int rand_y, char symbol){

	MapGraph *g = malloc( sizeof (*g) ); /* allocate new graph */
	g->number_of_nodes = path_count_floor(m); /* record the total number of possible nodes. In this case, the number of floor tiles on the map. */
	g->number_of_open_nodes = 0;
	g->number_of_closed_nodes = 0;
	g->open_list = malloc( sizeof (*(g->open_list)) * g->number_of_nodes ); /* allocate open_list */
	g->closed_list = malloc( sizeof (*(g->open_list)) * g->number_of_nodes ); /* allocate closed_list */
	g->startx = rand_y; /* record starting and ending node positions in the graph. */
	g->starty = rand_x;

	g->open_list[0].x = rand_x;
	g->open_list[0].y = rand_y;
	g->open_list[0].parent_index = 0;
	g->number_of_open_nodes = 1;
	g->current_index = 0;

	int nx,ny;

	while(1){ /* main loop */
		nx = g->open_list[g->current_index].x;
		ny = g->open_list[g->current_index].y;
		/*---- check the map for neighboring nodes ---- */
		if(ny > 0){
			if(m->map[(ny - 1) * m->map_width + nx] == m->floor ){ /* North */
				if(!path_node_exists_in_lists(g, nx, ny-1) ){
					path_open_list_add_node(g, nx, ny - 1); /* if this neighbor doesn't exist in any of the lists, add it to open_list */
					m->map[(ny - 1) * m->map_width + nx] = symbol;
				}
			}
		}
		if(ny < m->map_height){
			if( m->map[(ny + 1) * m->map_width + nx] == m->floor ){ /* South */
				if( !path_node_exists_in_lists(g, nx, ny+1) ){
					path_open_list_add_node(g, nx, ny + 1); /* if this neighbor doesn't exist in any of the lists, add it to open_list */
					m->map[(ny + 1) * m->map_width + nx] = symbol;
				}
			}
		}
		if(nx < m->map_width){
			if( m->map[ny * m->map_width + nx + 1] == m->floor ){ /* East */
				if( !path_node_exists_in_lists(g, nx + 1, ny) ){
					path_open_list_add_node(g, nx + 1, ny); /* if this neighbor doesn't exist in any of the lists, add it to open_list */
					m->map[ ny * m->map_width + nx + 1] = symbol;
				}
			}
		}
		if(nx < m->map_width && ny > 0){
			if( m->map[(ny - 1) * m->map_width + nx + 1] == m->floor ){ /* NorthEast */
				if( !path_node_exists_in_lists(g, nx + 1, ny - 1) ){
					path_open_list_add_node(g, nx + 1, ny - 1); /* if this neighbor doesn't exist in any of the lists, add it to open_list */
					m->map[ (ny - 1) * m->map_width + nx + 1] = symbol;
				}
			}
		}
		if(nx < m->map_width && ny < m->map_height){
			if( m->map[(ny + 1) * m->map_width + nx + 1] == m->floor ){ /* SouthEast */
				if( !path_node_exists_in_lists(g, nx + 1, ny + 1) ){
					path_open_list_add_node(g, nx + 1, ny + 1); /* if this neighbor doesn't exist in any of the lists, add it to open_list */
					m->map[ (ny + 1) * m->map_width + nx + 1] = symbol;
				}
			}
		}
		if(nx > 0){
			if( m->map[ny * m->map_width + nx - 1] == m->floor ){ /* West */
				if( !path_node_exists_in_lists(g, nx - 1, ny) ){
					path_open_list_add_node(g, nx - 1, ny); /* if this neighbor doesn't exist in any of the lists, add it to open_list */
					m->map[ ny * m->map_width + nx - 1] = symbol;
				}
			}
		}
		if(nx > 0 && ny > 0){
			if( m->map[(ny - 1) * m->map_width + nx - 1] == m->floor ){ /* Northwest */
				if( !path_node_exists_in_lists(g, nx - 1, ny - 1) ){
					path_open_list_add_node(g, nx - 1, ny - 1); /* if this neighbor doesn't exist in any of the lists, add it to open_list */
					m->map[ (ny - 1) * m->map_width + nx - 1] = symbol;
				}
			}
		}
		if(nx > 0 && ny < m->map_height){
			if( m->map[(ny + 1) * m->map_width + nx - 1] == m->floor ){ /* Southwest */
				if( !path_node_exists_in_lists(g, nx - 1, ny + 1) ){
					path_open_list_add_node(g, nx - 1, ny + 1); /* if this neighbor doesn't exist in any of the lists, add it to open_list */
					m->map[ (ny + 1) * m->map_width + nx - 1] = symbol;
				}
			}
		}
		if(g->current_index < g->number_of_open_nodes) g->current_index++;
		else if(g->current_index == g->number_of_open_nodes) break;
	}
	path_free_graph(g); /* deallocate graph data */
}



