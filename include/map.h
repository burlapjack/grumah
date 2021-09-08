/* map.h by burlapjack 2021
 * 
 */

#ifndef MAP_H
#define MAP_H

#include "component.h"

int map_xy(int x, int y, int map_width);

void map_init(Component *c, int map_width, int map_height, unsigned int *next_id);

void map_generate_rooms(Component *c, size_t number_of_rooms, int map_height, int map_width, int room_max_width, int room_max_height);

char map_lookup_symbol(Component *c, int x, int y);

void map_replace_symbol(Component *c, int x, int y, char char_old, char char_new);

#endif /* MAP_H */
