/* map.h by burlapjack 2021
 * 
 */

#ifndef MAP_H
#define MAP_H

#include "component.h"

typedef struct{
	int x,y,x2,y2;
}Room;

int map_xy(int x, int y, int map_width);

void map_init(Component *c, int map_width, int map_height, int *next_id);

void map_generate_rooms(Component *c, char *map_array, int map_width, int map_height, int number_of_rooms, int room_max_width, int room_max_height);

char map_lookup_symbol(Component *c, int x, int y);

void map_replace_symbol(Component *c, int x, int y, char char_old, char char_new);

#endif /* MAP_H */
