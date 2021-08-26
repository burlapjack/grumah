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
	int pxy, px2y,pxy2,px2y2; 
	int n = 0;

	/*------------ Place rooms -------------------------------*/
	while(n < num_rooms ){
		x = rand_int(map_width - 2);	
		y = rand_int(map_height - 2);	
		x2 = rand_int(room_size_max) + x + room_size_min;	
		y2 = rand_int(room_size_max) + y + room_size_min;	

		/*-------- Check coords are within bounds ------------*/
		x = ((x > 0) ? x : 2);
		y = ((y > 0) ? y : 2);
		x2 = (x2 < (map_width-2) ? x2 : map_width - 2);
		y2 = (y2 < (map_height-2) ? y2 : map_height - 2);

		/*-------- Translate 2D coords into 1D coords---------*/
		rxy = y*map_width + x;
		pxy = (y-1)*map_width + (x-1);
		
		rx2y = y*map_width + x2;
		px2y = (y-1)*map_width + (x2+1);

		rxy2 = y2*map_width + x;
		pxy2 = (y2+1)*map_width + (x-1);

		rx2y2 = y2*map_width + x2;
		px2y2 = (y2+1)*map_width + (x2+1);


		/*-------- Room Padding ------------------------------*/	
		int obstructions = 4;
		int i,j,pw,ph;
		pw = px2y - pxy;
		ph = pxy2 - pxy;
		for(i = 0; i < pw; i++){
			if( map[pxy + i] != '#')break;
			if( map[pxy + i] == '#' && i == pw) obstructions -= 1;
		}
		for(i = 0; i < pw; i++){
			if( map[pxy2 + i] != '#')break;
			if( map[pxy2 + i] == '#' && i == pw) obstructions -= 1;
		}
		for(i = 0; i < ph; i++ ){
			if( map[pxy + i] != '#')break;
			if( map[pxy + i] == '#' && i == ph) obstructions -= 1;
		}
		for(i = 0; i < ph; i++ ){
			if( map[px2y + (i*map_width)] != '#')break;
			if( map[px2y + (i*map_width)] == '#' && i == ph) obstructions -= 1;
		}
		
		/*-------- Check collisions with other rooms ---------*/
		if( map[rxy]=='#' && map[rx2y]=='#' && map[rxy2]=='#' && map[rx2y2]=='#'){ 
			//printw("x = %d y = %d x2 = %d y2 = %d ", x,y,x2,y2);
			for(i = y; i < y2; i++){
				for(j = x; j < x2; j++){
					map[(i*map_width)+j] = '.';	
				}
			}

			n++;	
		}
	}
	
}

