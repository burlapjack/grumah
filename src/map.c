/* map.c * by burlapjack 2021
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

/*--------------------- Convert 2d coords to 1d array position --------------------------------------------------------------*/
int map_xy(int x, int y, int map_width){
	int i;
	i = y*map_width + x;
	return i;
}

/*---------------------- Init a map that is all walls ------------------------------------------------------------------------*/
char** map_init(char **map, int map_width, int map_height){
	map = malloc(sizeof (char) * map_height );

	for (int i = 0; i < (map_height); i++){
		for (int j = 0; i < (map_width); j++){
			map[i][j] = '#';
		}
	}
	return map;
}

/*---------------------- Simple-Room-Placement Map Gen Algorithm -------------------------------------------------------------*/

void map_generate_srp(char **map, int map_width, int map_height, int room_size_max, int room_size_min, int num_rooms){
	
	int x,y,h,w;
	int i,j,k,cell;
	int n = 3;
	unsigned int collision;

	ComponentPosition rm_pos[num_rooms];
	ComponentSize rm_size[num_rooms];

	/*------------ Place rooms -------------------------------*/
	while(n < num_rooms ){
		/*-------- Propose new randomized room coords --------*/
		x = rand_int(map_width - 2);	
		y = rand_int(map_height - 2);	
		w = rand_int(room_size_max);	
		h = rand_int(room_size_max);	

		/*-------- Check coords are within bounds of map -----*/
		/*-------- Correct coords as needed ------------------*/

		x = (x > 1 ? x : 2);
		y = (y > 1 ? y : 2);
		w = (w < map_width-2-x ? w : map_width - 2);
		h = (h < map_height-2-y ? h : map_height - 2);
		
		/*-------- Prevent collisions with other rooms -------*/
		if( n > 0){
			collision = 0;
			for(i = 0; i < n; i++){
				if( x < rm_pos[i].x + rm_size[i].width && (x + w) > rm_pos[i].x && y < rm_pos[i].y + rm_size[i].height && (y + h) > rm_pos[i].y){
					collision = 1;
					break;	
				}
			}	
			if(collision == 0){
				n++;
				rm_pos[n].x = x;
				rm_pos[n].y = y;
				rm_size[n].width = w;
				rm_size[n].height = h;
			}
		}
		else{
			n++;
			rm_pos[n].x = x;
			rm_pos[n].y = y;
			rm_size[n].width = w;
			rm_size[n].height = h;
		}
	}

	for(i = 0; i < num_rooms; i++){
		for(j = rm_pos[i].y; j < rm_size[i].height + rm_pos[i].y; j++){
			for(k = rm_pos[i].x; k < rm_size[i].width + rm_pos[i].x; k++){
				//cell = map_xy(k,j,map_width);
				map[j][k] = '.';
			}
		}
	}
}

