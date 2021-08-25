/* map_generate.c * by burlapjack 2021
 * procedural map generation
 */

#include <stdlib.h>
#include <assert.h>
#include <ncurses.h>
#include "../include/map.h"

/*--------------------- Pseudo-random number generator ----------------------------------------------------------------------*/
static int rand_int(int n){
	if((n - 1) == RAND_MAX){
		return rand();
	} else {
		assert(n <= RAND_MAX);
		int end = RAND_MAX / n;
		assert (end > 0);
		end *= n;
		int r;
		while ((r = rand()) >= end);
		return r % n;
	}
}

/*---------------------- Init a map that is all walls ------------------------------------------------------------------------*/
void map_generate_init(char *map, int map_width, int map_height){
	for (unsigned int i = 0; i < map_height; i++){
		for (unsigned int j = 0; j < map_width; j++){
			*((map + i) + j) = '#';	
		}
	}
}

/*---------------------- Simple-Room-Placement Map Gen Algorythm -------------------------------------------------------------*/

void map_generate_srp(char *map, int map_width, int map_height, int room_size_max, int room_size_min){
	int x,y,x2,y2;
	unsigned int room_fits = 0;
	/*------------ Initialize map ----------------------------*/
	map_generate_init(map, map_width, map_height);	

	/*------------ Place rooms -------------------------------*/
	while( room_fits == 0){
		x = rand_int(map_width - 5);	
		x2 = rand_int(room_size_max) + x + room_size_min;	
		y = rand_int(map_height- 5);	
		y2 = rand_int(room_size_max) + y + room_size_min;	
		if( *(map + (y * sizeof (char)) + (x * sizeof (char))) 
				&& *(map + (y * sizeof (char) *  map_width) + (x2 * sizeof (char))) 
				&& *(map + (y2 * sizeof (char) * map_width) + (x * sizeof (char))) 
				&& *(map + (y2 * sizeof (char) * map_width) + (x2 * sizeof (char)))){ 

			for(int i = y; i < y2; i++){
				for(int j = x; j < x2; j++){
					//*(map + (i * sizeof (char) * map_width) + (j * sizeof (char))) = '.';
				}
			}
			room_fits = 1;	
		}
	}
}

