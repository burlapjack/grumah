/* path.c
 * by burlapjack 2021
 * functions and data structures related
 * to pathfinding.
 */

#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include "../include/gr_path.h"
#include "../include/gr_map.h"

/*====================== Opaque Data Types =================================================================================*/



int
gr_path_get_manhattan_distance(int x1, int y1, int x2, int y2)
{
	return abs(x1 - x2) + abs(y1 - y2);
}

int
gr_path_count_floor(MapData *m)
{
	int count = 0;
	for (int i = 0; i < m->map_height; i++) {
		for (int j = 0; j < m->map_width; j++) {
			if (m->terrain[ (i * m->map_width) + j] == m->floor) {
				count++;
			}
		}
	}
	return count;
}

/*---------------------- Copy contents of indicated open_list node into closed_list ------------------------------------------*/
void 
gr_path_closed_list_add_node(PathGraph *g, int open_list_index)
{
	g->closed_list[g->number_of_closed_nodes] = g->open_list[open_list_index];
	g->number_of_closed_nodes++;
	for (int i = open_list_index; i < g->number_of_open_nodes - 1; i++) { /* remove target node by overwriting it. */
		g->open_list[i] = g->open_list[i + 1];
	}
	if (g->number_of_open_nodes > 0)
		g->number_of_open_nodes -= 1;
}

/*---------------------- Deallocate PathGraph memory --------------------------------------------------------------------------*/
void
gr_path_free_graph(PathGraph *g)
{
	free(g->open_list);
	free(g->closed_list);
	free(g);
}

/*---------------------- Add new node to open_list ---------------------------------------------------------------------------*/
void
gr_path_open_list_add_node(PathGraph *g, int x, int y)
{
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
int
gr_path_closed_list_get_index(PathGraph *g, int x, int y)
{
	int index;
	for ( int i = 0; i < g->number_of_closed_nodes; i++) {
		if (g->closed_list[i].x == x && g->closed_list[i].y == y) {
			index = i;
			break;
		}
	}
	return index;
}
/*--------------------- Return the index of the node that has the lowest f value, and is a child of current_index node. ------*/
int
gr_path_open_list_get_index_lowest_f(PathGraph *g)
{
	int lowest = INT_MAX;
	int target_index;
	for ( int i = 0; i < g->number_of_open_nodes; i++) {
		if ( g->open_list[i].f <= lowest  && g->open_list[i].parent_index == g->current_index) {
			lowest = g->open_list[i].f;
			target_index = i;
		}
	}
	return target_index;
}

/*---------------------- Get the open_list[] index via map coords ------------------------------------------------------------*/
int
gr_path_open_list_get_index(PathGraph *g, int x, int y)
{
	int index;
	for ( int i = 0; i < g->number_of_open_nodes - 1; i++) {
		if (g->open_list[i].x == x && g->open_list[i].y == y) {
			index = i;
			break;
		}
	}
	return index;
}

/*---------------------- Check to see if the given criteria are matched by a node in any list  -------------------------------*/
int
gr_path_node_exists_in_lists(PathGraph *g, int x, int y)
{
	int  exists = 0;
	/* checked open_list */
	for (int i = 0; i < g->number_of_open_nodes; i++) {
		if ( g->open_list[i].x == x && g->open_list[i].y == y) {
			exists = 1;
			break;
		}
	}
	if (exists == 0) {
		/* check closed_list */
		for (int i = 0; i < g->number_of_closed_nodes; i++) {
			if ( g->closed_list[i].x == x && g->closed_list[i].y == y) {
				exists = 1;
				break;
			}
		}
	}
	return exists;
}


/*--------------------- Return 1 if the node with the given coordinates exist in the open list. ------------------------------*/
int
gr_path_node_exists_in_open_list(PathGraph *g, int x, int y)
{
	int  exists = 0;
	for (int i = 0; i < g->number_of_open_nodes; i++) {
		if ( g->open_list[i].x == x && g->open_list[i].y == y) { /* find coordinate match */
			exists = 1;
			break;
		}
	}
	return exists;
}

/*--------------------- Updates the g and f value of a node if it already has been added to the open_list. ------------------*/
void
gr_path_node_update(PathGraph *g, int nx, int ny)
{
	int ni = gr_path_open_list_get_index(g, nx, ny);
	int existing_f = g->open_list[ni].f; /* the current f value of this node. */
	int new_f = g->open_list[g->current_index].g + 1 + g->open_list[ni].h; /* the possible new f value */
	if (existing_f > new_f) { /* check to see if this node is better off with a new parent node. */
		g->open_list[ni].parent_index = g->current_index; /* set parent */
		g->open_list[ni].g = g->open_list[g->current_index].g + 1; /* refresh g value. */
		g->open_list[ni].f = new_f; /* refresh f value. */
	}
}

void
gr_path_line_of_sight(Component *c, MapData *m, int x, int y)
{
}
