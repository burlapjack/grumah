/* map.h by burlapjack 2021
 *
 */

#ifndef MAP_H
#define MAP_H

#include "component.h"


typedef struct data MapData;

typedef struct{
	int x,y,x2,y2;
}Room;

typedef struct{
	int x,y,x2,y2;
}Hall;

typedef struct node MapNode;
typedef struct graph MapGraph;

/*--------Map Init / Free from memory ----------------------------------------------------------------------------------------*/
void   map_init(MapData *m, int map_width, int map_height); /* Initializes a MapData struct. */
void   map_free(MapData *m); /* Deallocates MapData memory. */

/*--------Map Generation Style -----------------------------------------------------------------------------------------------*/
void   map_gen_srp(MapData *m); /* Simple-Room-Placement procedurally generated map. Rectangular rooms connected by hallways. */
void   map_gen_ca(MapData *m); /* Cellular-Automata procedurally generated map.  Cave-like design. */

/*--------Map generation helper functions ------------------------------------------------------------------------------------*/
void   map_gen_carve_hallways(MapData *m, Room *rooms, int rooms_added); /* Designates the carving of hallways for an srp map, connects rooms left to right. */
void   map_gen_carve_hall_horizontally(MapData *m, Hall *halls_array, int hall_index, int xstart, int xend); /* Called on to carve horizontal section of hallway */
void   map_gen_carve_hall_vertically(MapData *m, Hall *halls_array, int hall_index, int ystart, int yend); /* Called on to carve vertical section of hallway */
void   map_gen_carve_room(MapData *m, Room *rooms, int rooms_added); /* For srp maps, carves out rectangular rooms */
void   map_gen_fill(MapData *m); /* Fills a map entirely with walls. */
void   map_gen_doors(MapData *m, Room *rooms, int number_of_rooms); /* For srp maps, creates doors where hallways meet rooms. */

/*-------- Pathfinding-related functions -------------------------------------------------------------------------------------*/
int    map_count_floor(MapData *m); /* Returns the number of floor tiles on a given map. */
int    map_path_closed_list_get_index(MapGraph *g, int x, int y); /* Returns the closed_list node index given the map coords. */
int    map_path_get_manhattan_distance(int x1, int y1, int x2, int y2); /* Returns the manhattan distance between two points. */
void   map_path_free_graph(MapGraph *g); /* Deallocates a MapGraph struct. */
void   map_path_init_lists(MapData *m, MapGraph *g); /* Initializes MapGraph open_list and closed_list. */
bool   map_path_is_contiguous(MapData *m, int ax, int ay, int bx, int by); /* Returns true if point a and point b share contiguous floor space. */
bool   map_path_node_exists_in_lists(MapGraph *g, int x, int y); /* Returns true if the given coordinates exist as a node in open_list or closed_list. */
void   map_path_node_get_neighbors(MapData *m, MapGraph *g, int current_index); /* Finds the neighboring nodes from the map, adds them to open_list and calculates their f,g,h. */
void   map_path_open_list_add_node(MapGraph *g, int parent_index, int x, int y); /* Adds a new node to open_list given the parent index, and coordinates on the map. */
void   map_path_open_list_clear_node(MapGraph *g, int node_index); /* "Clears" a node from the open_list by giving the indicated node index garbage data that won't be queried. */
int    map_path_open_list_get_index(MapGraph *g, int x, int y); /* Returns the index of a node from open_list given the coordinates on the map. */

/*--------Misc math functions ------------------------------------------------------------------------------------------------*/
int    map_xy(int x, int y, int map_width); /* Returns a converted one-dimensional array index given the equivelent two-dimensional x and y coordinates. */
int    max_int(int a, int b); /* returns the greater of two given integers. */
int    min_int(int a, int b); /* returns the lesser of two given integers. */
int    rand_int(int n); /* returns a random integer */

#endif /* MAP_H */
