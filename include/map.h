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


/*--------Map Init / Free from memory ----------------------------------------------------------------------------------------*/
void   map_init(MapData *m, int map_width, int map_height); /* Initializes a MapData struct. */
void   map_free(MapData *m); /* Deallocates MapData memory. */

/*--------Map Generation Style -----------------------------------------------------------------------------------------------*/
void   map_gen_style_dungeon(MapData *m); /* Simple-Room-Placement procedurally generated map. Rectangular rooms connected by hallways. */
void   map_gen_style_cave(MapData *m); /* Cellular-Automata procedurally generated map.  Cave-like design. */

/*--------Map generation helper functions ------------------------------------------------------------------------------------*/
void   map_gen_carve_hallways(MapData *m, Room *rooms, int rooms_added); /* Designates the carving of hallways for an srp map, connects rooms left to right. */
void   map_gen_carve_hall_horizontally(MapData *m, Hall *halls_array, int hall_index, int xstart, int xend); /* Called on to carve horizontal section of hallway */
void   map_gen_carve_hall_vertically(MapData *m, Hall *halls_array, int hall_index, int ystart, int yend); /* Called on to carve vertical section of hallway */
void   map_gen_carve_room(MapData *m, Room *rooms, int rooms_added); /* For srp maps, carves out rectangular rooms */
void   map_gen_fill(MapData *m); /* Fills a map entirely with walls. */
void   map_gen_doors(MapData *m, Room *rooms, int number_of_rooms); /* For srp maps, creates doors where hallways meet rooms. */

/*--------Misc math functions ------------------------------------------------------------------------------------------------*/
int    map_count_tile(MapData *m, char tile);
int    map_xy(int x, int y, int map_width); /* Returns a converted one-dimensional array index given the equivelent two-dimensional x and y coordinates. */
int    max_int(int a, int b); /* returns the greater of two given integers. */
int    min_int(int a, int b); /* returns the lesser of two given integers. */
int    rand_int(int n); /* returns a random integer */

#endif /* MAP_H */
