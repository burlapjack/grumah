/* map.h by burlapjack 2021
 * 
 */

#ifndef MAP_H
#define MAP_H

#include "component.h"

int map_xy(int x, int y, int map_width);

//void map_init(size_t map_rows, size_t map_columns, char(**map)[map_rows][map_columns]);

void map_init(Component *c, int map_width, int map_height, unsigned int *next_id);

#endif /* MAP_H */
