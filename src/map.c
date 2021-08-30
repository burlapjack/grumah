/* map_generate.c * by burlapjack 2021
 * procedural map generation
 */

#include <stdlib.h>
#include <assert.h>
#include <ncurses.h>
#include "../include/map.h"
#include "../include/component.h"

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

/*---------------------- Simple-Room-Placement Map Gen Algorithm -------------------------------------------------------------*/

void map_generate_srp(char *map, int map_width, int map_height, int room_size_max, int room_size_min, int num_rooms){
	int x,y,x2,y2;
	int room_topleft, room_topright,room_bottomleft,room_bottomright; 
	int n = 0;
	
	//ComponentPosition position_list[num_rooms];
	//ComponentSize room_list[num_rooms];

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
		int i,j,k;
		room_topleft = y*map_width + x;
		room_topright = y*map_width + x2;
		room_bottomleft = y2*map_width + x;
		room_bottomright = y2*map_width + x2;

		/*-------- Prevent collisions with other rooms -------*/
		if(map[room_topleft] == '#' && map[room_topright] == '#' && map[room_bottomleft] == '#' && map[room_bottomright] =='#'){
			for(i = y; i < y2; i++){
				for(j = x; j < x2; j++){
					map[(i*map_width)+j]='.';
				}
			}	
			n++;
		}
	}	
}

