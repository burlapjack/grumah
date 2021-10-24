/* path.h
 * by burlapjack 2021
 */

#ifndef PATH_H
#define PATH_H

#include "gr_map.h"

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

int    gr_path_count_floor(MapData *m); /* Returns the number of floor tiles on a given map. */
int    gr_path_closed_list_get_index(PathGraph *g, int x, int y); /* Returns the closed_list node index given the map coords. */
int    gr_path_get_manhattan_distance(int x1, int y1, int x2, int y2); /* Returns the manhattan distance between two points. */
void   gr_path_flood_fill(MapData *m, int rand_x, int rand_y, char symbol);
void   gr_path_free_graph(PathGraph *g); /* Deallocates a PathGraph struct. */
int    gr_path_node_exists_in_lists(PathGraph *g, int x, int y); /* Returns true if the given coordinates exist as a node in open_list or closed_list. */
int    gr_path_node_exists_in_open_list(PathGraph *g, int x, int y); /* Returns true if the supplied coordinates matches a node in the open_list */
void   gr_path_node_update(PathGraph *g, int nx, int ny); /* updates the heuristics of a neighbor node if it has already been added to the open_list */
void   gr_path_open_list_add_node(PathGraph *g, int x, int y); /* Adds a new node to open_list given the parent index, and coordinates on the map. */
int    gr_path_open_list_get_index(PathGraph *g, int x, int y); /* Returns the index of a node from open_list given the coordinates on the map. */
int    gr_path_open_list_get_index_lowest_f(PathGraph *g); /* finds the index of the node with the lowest f value in open_list. */

#endif /* PATH_H */
