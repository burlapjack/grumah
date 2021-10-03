/* path.h
 * by burlapjack 2021
 */

#ifndef PATH_H
#define PATH_H

#include "map.h"

int    path_count_floor(MapData *m); /* Returns the number of floor tiles on a given map. */
int    path_closed_list_get_index(MapGraph *g, int x, int y); /* Returns the closed_list node index given the map coords. */
int    path_get_manhattan_distance(int x1, int y1, int x2, int y2); /* Returns the manhattan distance between two points. */
void   path_free_graph(MapGraph *g); /* Deallocates a MapGraph struct. */
bool   path_is_contiguous(MapData *m, int ax, int ay, int bx, int by); /* Returns true if point a and point b share contiguous floor space. */
bool   path_node_exists_in_lists(MapGraph *g, int x, int y); /* Returns true if the given coordinates exist as a node in open_list or closed_list. */
bool   path_node_exists_in_open_list(MapGraph *g, int x, int y);
void   path_node_get_neighbors(MapData *m, MapGraph *g); /* Finds the neighboring nodes from the map, adds them to open_list and calculates their f,g,h. */
void   path_node_update(MapGraph *g, int nx, int ny);
void   path_open_list_add_node(MapGraph *g, int parent_index, int x, int y); /* Adds a new node to open_list given the parent index, and coordinates on the map. */
int    path_open_list_get_index(MapGraph *g, int x, int y); /* Returns the index of a node from open_list given the coordinates on the map. */
int    path_open_list_get_index_lowest_f(MapGraph *g); /* finds the index of the node with the lowest f value in open_list. */
int    path_open_list_get_lowest_f(MapGraph *g); /* finds the value of the node with the lowest f value in open_list. */

#endif /* PATH_H */
