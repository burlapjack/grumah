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

static int max_int(int a, int b){
	if (a > b) return a; else return b;
}

static int min_int(int a, int b){
	if (a < b) return a; else return b;
}

/*---------------------- Init a map that is all walls ------------------------------------------------------------------------*/

void map_init(Component *c, int map_width, int map_height, unsigned int *next_id){

	for ( int i = 0; i < map_height; i++){
		for ( int j = 0; j < map_width; j++){
			component_add_position(c, *next_id, j, i);
			component_add_draw(c, *next_id, 0, 1, '#'); 
			*next_id += 1;
		}
	}	
}

void map_generate_rooms(Component *c, size_t number_of_rooms, int map_height, int map_width, int room_max_width, int room_max_height){
	int room_x, room_x2, room_y, room_y2;	
	int room_padding = 2;
	size_t i = 0;
	while (i < number_of_rooms){
		room_x = rand_int( map_width - room_max_width - room_padding );
		room_x = max_int(2,room_x);
		room_y = rand_int( map_height - room_max_height - room_padding );
		room_y = max_int(2,room_y);
		room_x2 = rand_int( room_max_width ) + room_x;
		room_x2 = min_int((map_width - room_padding), room_x2);
		room_y2 = rand_int( room_max_height ) + room_y;
		room_y2 = min_int((map_height- room_padding), room_y2);


	}	
		
}
