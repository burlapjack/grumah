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
char* map_init(char *map, int map_width, int map_height){
	map = (char *)malloc((map_height * map_width) * sizeof (char));

	for (int i = 0; i < (map_height * map_width); i++){
		map[i] = '#';
	}
	return map;
}

/*---------------------- Simple-Room-Placement Map Gen Algorythm -------------------------------------------------------------*/

void map_generate_srp(char *map, int map_width, int map_height, int room_size_max, int room_size_min, int num_rooms){
	int x,y,x2,y2;
	int rxy, rx2y,rxy2,rx2y2; 
	int n = 0;

	/*------------ Place rooms -------------------------------*/
	while(n < num_rooms ){
		x = rand_int(map_width - 2);	
		x = ((x > 0) ? x : 1);
		y = rand_int(map_height - 2);	
		y = ((y > 0) ? y : 1);
		
		x2 = rand_int(room_size_max) + x + room_size_min;	
		y2 = rand_int(room_size_max) + y + room_size_min;	

	/*------------ Check coords are within bounds ------------*/
		x2 = (x2 < (map_width-2) ? x2 : map_width - 1);
		y2 = (y2 < (map_height-2) ? y2 : map_height - 1);

		/*-------- Translate 2D coords into 1D coords---------*/
		rxy = y*map_width + x;
		rx2y = y*map_width + x2;
		rxy2 = y2*map_width + x;
		rx2y2 = y2*map_width + x2;

		if(map[rxy]=='#' && map[rx2y]=='#' && map[rxy2]=='#' && map[rx2y2]=='#'){ 
			//printw("x = %d y = %d x2 = %d y2 = %d ", x,y,x2,y2);
			int i,j;
			for(i = y; i < y2; i++){
				for(j = x; j < x2; j++){
					map[(i*map_width)+j] = '.';	
				}
			}

			n++;	
		}
	}
	
}

