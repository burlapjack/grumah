/* map.h by burlapjack 2021
 *
 */

#ifndef MAP_H
#define MAP_H

#include "gr_component.h"
//#include <stdbool.h>

typedef struct{
	int map_width;
	int map_height;
	int map_x_offset;
	int map_y_offset;
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
	char hallway_horizontal;
	char hallway_vertical;
	char wall;
	int color_entrance;
	int color_exit;
	int color_door_horizontal;
	int color_door_vertical;
	int color_floor;
	int color_wall;
	char *terrain;
}MapData;

typedef struct{
	int x,y,x2,y2;
}Room;

typedef struct{
	int x,y,x2,y2;
}Hall;

typedef struct{
	float x1, y1;
	float x2, y2;
}Edge;

typedef struct{
	int edge_id[4];
	int edge_exist[4];
}Cell;

typedef struct{
	float angle;
	float x,y;
}VisPoly;

/*-------- Fill empty area of map with a given character/symbol --------------------------------------------------------------*/
void   gr_map_flood_fill(MapData *m, int rand_x, int rand_y, char symbol);

/*-------- Map Init / Free from memory ---------------------------------------------------------------------------------------*/
void   gr_map_free(MapData *m); /* Deallocates MapData memory. */
void   gr_map_init(MapData *m, int map_width, int map_height); /* Initializes a MapData struct. */

/*-------- Map generation helper functions -----------------------------------------------------------------------------------*/
void   gr_map_gen_add_components(MapData *m, Component *c);
void   gr_map_gen_carve_hallways(MapData *m, Room *rooms, int rooms_added); /* Designates the carving of hallways for an srp map, connects rooms left to right. */
void   gr_map_gen_carve_hall_horizontally(MapData *m, Hall *halls_array, int hall_index, int xstart, int xend); /* Called on to carve horizontal section of hallway */
void   gr_map_gen_carve_hall_vertically(MapData *m, Hall *halls_array, int hall_index, int ystart, int yend); /* Called on to carve vertical section of hallway */
void   gr_map_gen_carve_room(MapData *m, Room *rooms, int rooms_added); /* For srp maps, carves out rectangular rooms */
void   gr_map_gen_fill(MapData *m); /* Fills a map entirely with walls. */
void   gr_map_gen_doors(MapData *m, Room *rooms, int number_of_rooms); /* For srp maps, creates doors where hallways meet rooms. */
void   gr_map_gen_entrance_and_exit(MapData *m);

/*-------- Map Generation Style ----------------------------------------------------------------------------------------------*/
void   gr_map_gen_style_dungeon(MapData *m, Component *c); /* Simple-Room-Placement procedurally generated map. Rectangular rooms connected by hallways. */
void   gr_map_gen_style_cave(MapData *m, Component *c); /* Cellular-Automata procedurally generated map.  Cave-like design. */

/*-------- Misc math functions -----------------------------------------------------------------------------------------------*/
int    gr_map_xy(int x, int y, int map_width); /* Returns a converted one-dimensional array index given the equivelent two-dimensional x and y coordinates. */
int    gr_max_int(int a, int b); /* returns the greater of two given integers. */
int    gr_min_int(int a, int b); /* returns the lesser of two given integers. */
int    gr_rand_int(int n); /* returns a random integer */

/*------- Raycasting ---------------------------------------------------------------------------------------------------------*/
void   gr_map_los_raycast(MapData *m, Component *c, int id, int range);

/*------- Query map data  ----------------------------------------------------------------------------------------------------*/
int    gr_map_count_tile(MapData *m, char tile);
void   gr_map_component_set_random_position(MapData *m, Component *c, int id);

#endif /* MAP_H */
