/* map.h by burlapjack 2021
 *
 */

#ifndef MAP_H
#define MAP_H

#include "component.h"

typedef struct{
	int map_width;
	int map_height;
	int number_of_rooms;
	int room_max_width;
	int room_max_height;
	int room_min_width;
	int room_min_height;
	int room_padding;
	char door_horizontal_closed;
	char door_horizontal_open;
	char door_vertical_closed;
	char door_vertical_open;
	char entrance;
	char exit;
	char floor;
	char hallway;
	char wall;

	int color_entrance;
	int color_exit;
	int color_door_horizontal;
	int color_door_vertical;
	int color_floor;
	int color_wall;

	char *map;

}MapData;

typedef struct{
	int x,y,x2,y2;
}Room;

typedef struct{
	int x,y,x2,y2;
}Hall;

struct pathnode{
	int id;
	int x,y;
	int number_of_neighbors;
	struct PathNode **neighbors; /* array of pointers to neighboring nodes */
	int *weights; /* array of neighbor weights in the same order that neighbors array is in */
	int heuristic; /* distance from the node to goal */
};
typedef struct pathnode PathNode;

typedef struct{
	int node_count; /* Number of nodes on the graph */
	int iterations; /* number of times the loop has run */
	PathNode **unvisited_nodes; /* ordered array of PathNode pointers on the graph */
	PathNode **visited_nodes; /* array of pointers to PathNodes marked as "visited".  Empty by default */
	PathNode **parents; /* array of pointers to each node's parent node which creates  the shortest distance from origin */
	int *distances; /* array that represents the total distance from an origin node to every other node */
}PathGraph;

/*--------Map Init / Free from memory ----------------------------------------------------------------------------------------*/
void map_init(MapData *m, int map_width, int map_height);
void map_free(MapData *m);

/*--------Map Generation Style -----------------------------------------------------------------------------------------------*/
void map_generate_srp(MapData *m);
void map_generate_ca(MapData *m);

/*--------Map generation helper functions ------------------------------------------------------------------------------------*/
void map_carve_hallways(MapData *m, Room *rooms, int rooms_added);
void map_carve_hall_horizontally(MapData *m, Hall *halls_array, int hall_index, int xstart, int xend);
void map_carve_hall_vertically(MapData *m, Hall *halls_array, int hall_index, int ystart, int yend);
void map_carve_room(MapData *m, Room *rooms, int rooms_added);
void map_fill(MapData *m);
void map_generate_doors(MapData *m, Room *rooms, int number_of_rooms);

/*-------- Pathfinding-related functions -------------------------------------------------------------------------------------*/
int map_count_floor(MapData *m);
int map_get_manhattan_distance(MapData *m, int x1, int y1, int x2, int y2);
void map_find_path(MapData *m, int x1, int y1, int x2, int y2);

/*--------Misc math functions ------------------------------------------------------------------------------------------------*/
int map_xy(int x, int y, int map_width);
double max_double(double a, double b);
double min_double(double a, double  b);
int max_int(int a, int b);
int min_int(int a, int b);
int rand_int(int n);

#endif /* MAP_H */
