/* map.h by burlapjack 2021
 * 
 */

#ifndef MAP_H
#define MAP_H

int map_xy(int x, int y, int map_width);

void map_init(size_t map_rows, size_t map_columns, char(**map)[map_rows][map_columns]);

#endif /* MAP_H */
