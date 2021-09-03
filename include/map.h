/* map.h by burlapjack 2021
 * 
 */

#ifndef MAP_H
#define MAP_H

typedef struct{
	unsigned int id;
	int width;
	int height;
	char *data;
}Map;



int map_xy(int x, int y, int map_width);

#endif /* MAP_H */
