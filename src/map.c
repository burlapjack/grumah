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
	int room_topleft, room_topright,room_bottomleft,room_bottomright; 
	int padding_topleft, padding_topright,padding_bottomleft,padding_bottomright; 
	int n = 0;

	/*------------ Place rooms -------------------------------*/
	while(n < num_rooms ){
		/*-------- Propose new randomized room coords --------*/
		x = rand_int(map_width - 2);	
		y = rand_int(map_height - 2);	
		x2 = rand_int(room_size_max) + x + room_size_min;	
		y2 = rand_int(room_size_max) + y + room_size_min;	

		/*-------- Check coords are within bounds of map -----*/
		/*-------- Correct coords as needed ------------------*/
		x = ((x > 1) ? x : 2);
		y = ((y > 1) ? y : 2);
		x2 = (x2 < (map_width-2) ? x2 : map_width - 2);
		y2 = (y2 < (map_height-2) ? y2 : map_height - 2);

		/*-------- Translate 2D coords into 1D coords---------*/
		room_topleft = y*map_width + x;
		room_topright = y*map_width + x2;
		room_bottomleft = y2*map_width + x;
		room_bottomright = y2*map_width + x2;

		/*-------- Room Padding ------------------------------*/	
		int i,j,k,p, padding_width,padding_height;
		padding_topleft = ((y-1) * map_width) + (x-1);
		padding_topright = ((y-1) * map_width) + (x2+1);
		padding_bottomleft = ((y2+1) * map_width) + (x-1);
		padding_bottomright = ((y2+1) * map_width) + (x2+1);
		padding_width = padding_topright - padding_topleft;
		padding_height = padding_bottomleft - padding_topleft;

		/*-------- Make sure room has walls all around it --------------------*/
		/*-------- Check padding on top and bottom sides of room -------------*/
		for(i = 0; i < padding_width; i++){

			if( map[padding_topleft + i] != '#')break;
			if( map[padding_bottomleft + i] != '#')break;
			if( map[padding_topleft + i] == '#' &&  map[padding_bottomleft + i] == '#' && i == padding_width){

				/*-------- Check padding on left and right sides of room -----*/
				for(j = 0; j < padding_height; j += map_width ){
					if( map[padding_topleft + j ] != '#')break;
					if( map[padding_topright + j] != '#')break;
					if( map[padding_topleft + j] == '#' && map[padding_topright + j] == '#' && j == padding_height){

						/*-------- Check collisions with other rooms ---------*/
					//	if( map[room_topleft]=='#' && map[room_topright]=='#' && map[room_bottomleft]=='#' && map[room_bottomright]=='#'){ 
							for(k = y; k < y2; k++){
								for(p = x; p < x2; p++){
									map[(k*map_width)+p] = '.';	
								}
							}
							n++;	
						//}
					}	
				}
			}	
		}
	}
}

