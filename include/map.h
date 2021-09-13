/* map.h by burlapjack 2021
 * 
 */

#ifndef MAP_H
#define MAP_H

#include "component.h"

typedef struct{
	char *map;
	int map_width;
	int map_height;
	int number_of_rooms;
	int room_max_width;
	int room_max_height;
	int room_min_width;
	int room_min_height;	

	char door_horizontal_closed;
	char door_horizontal_open;
	char door_vertical_closed;
	char door_vertical_open;
	char entrance;
	char exit;	
	char floor;	
	char wall;

	int color_entrance;
	int color_exit;
	int color_door_horizontal;
	int color_door_vertical;
	int color_floor;
	int color_wall;	
	
}MapData;

typedef struct{
	int x,y,x2,y2;
}Room;

typedef struct{
	int x,y,x2,y2;
}Hall;

//void map_generate_srp(char *map_array, int map_width, int map_height, int number_of_rooms, int room_min_width, int room_min_height, int room_max_width, int room_max_height);
void map_generate_srp(MapData *m);

void map_init(MapData *m, int map_width, int map_height);

void map_fill(MapData *m);

int map_xy(int x, int y, int map_width);

#endif /* MAP_H */
