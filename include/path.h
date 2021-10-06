/* path.h
 * by burlapjack 2021
 */

#ifndef PATH_H
#define PATH_H

#include "map.h"

typedef struct{
	int x,y;
}FloodNode;

typedef struct{
	int x,y;
	int f,g,h;
	int parent_index;
}PathNode;

typedef struct{
	int current_index;
	int size_node_list;
	int number_of_nodes;
	FloodNode *node_list;
}FloodGraph;

typedef struct{
	int number_of_nodes;
	int startx,starty;
	int endx, endy;
	int number_of_open_nodes;
	int number_of_closed_nodes;
	int current_index;
	PathNode *open_list;
	PathNode *closed_list;
}PathGraph;

int    path_count_floor(MapData *m); /* Returns the number of floor tiles on a given map. */
int    path_closed_list_get_index(PathGraph *g, int x, int y); /* Returns the closed_list node index given the map coords. */
int    path_get_manhattan_distance(int x1, int y1, int x2, int y2); /* Returns the manhattan distance between two points. */
void   path_flood_fill(MapData *m, int rand_x, int rand_y, char symbol);
void   path_flood_list_add_node(FloodNode *list, int *list_size, int x, int y);
void   path_free_graph(PathGraph *g); /* Deallocates a PathGraph struct. */
bool   path_is_contiguous(MapData *m, int ax, int ay, int bx, int by); /* Returns true if point a and point b share contiguous floor space. */
bool   path_node_exists_in_flood_list(FloodNode *list, int list_size, int x, int y);
bool   path_node_exists_in_lists(PathGraph *g, int x, int y); /* Returns true if the given coordinates exist as a node in open_list or closed_list. */
bool   path_node_exists_in_open_list(PathGraph *g, int x, int y); /* Returns true if the supplied coordinates matches a node in the open_list */
void   path_node_update(PathGraph *g, int nx, int ny); /* updates the heuristics of a neighbor node if it has already been added to the open_list */
void   path_open_list_add_node(PathGraph *g, int x, int y); /* Adds a new node to open_list given the parent index, and coordinates on the map. */
int    path_open_list_get_index(PathGraph *g, int x, int y); /* Returns the index of a node from open_list given the coordinates on the map. */
int    path_open_list_get_index_lowest_f(PathGraph *g); /* finds the index of the node with the lowest f value in open_list. */

#endif /* PATH_H */
