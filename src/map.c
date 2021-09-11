/* map.c * by burlapjack 2021
 * procedural map generation
 */

#include <stdlib.h>
#include <assert.h>
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

/*------ Find the largest of two integers ------------------------------------------------------------------------------------*/
static int max_int(int a, int b){
	if (a > b) return a; else return b;
}

/*------ Find the smallest of two integers -----------------------------------------------------------------------------------*/
static int min_int(int a, int b){
	if (a < b) return a; else return b;
}

/*---------------------- Init a map that is all walls ------------------------------------------------------------------------*/
void map_init(char *map_array, int map_width, int map_height){

	for ( int i = 0; i < map_height; i++){
		for ( int j = 0; j < map_width; j++){
			map_array[ i * map_width + j] = '#';
		}
	}	
}

/*---------------------- Replace symbol at map location ---------------------------------------------*/
void map_replace_symbol(Component *c, int x, int y, char char_old, char char_new){
	int id = 0;
	for(size_t i = 0; i < (c->size_position); i++){
		if( c->position[i].x == x && c->position[i].y == y){
			id = c->position[i].id;
			break;
		}
	}
	if(id != 0){
		for(size_t j = 0; j < c->size_draw; j++){
			if(c->draw[j].id == id && c->draw[j].symbol == char_old){
				c->draw[j].symbol = char_new;
				break;
			}	
		}
	}
}

/*---------------------- Find draw component index for map location ------------------------------*/
size_t map_lookup_draw_index(Component *c, int x, int y){
	size_t index;
	int id = 0;
	for (size_t i = 0; i < c->size_position; i++){
		if(c->position[i].x ==x || c->position[i].y == y){
			id = c->position[i].id;
		}	
	}
	for(size_t j = 0; j < c->size_draw; j++){
		if( c->draw[j].id == id ){
			index = j;
			break;
		}	
	}
	return index;
}

/*---------------------- Map Generation: Simple Room Placement -----------------------------------*/
/* Rooms are added one at a time wherever they will fit, then hallways are created between them.  */
void map_generate_srp(char *map_array, int map_width, int map_height, int number_of_rooms, int room_min_width, int room_min_height, int room_max_width, int room_max_height){
	int room_x,room_y, room_x2, room_y2;
	int rooms_added = 0;
	int padding = 2;
	int collision_detected = 0;
	Room rooms[number_of_rooms];	
	/* Room Creation */
	while(rooms_added < number_of_rooms){
		/* Propose random room coordinates */
		room_x = rand_int(map_width - room_max_width - padding);
		room_x = max_int(2, room_x);
		room_y = rand_int(map_height - room_max_height - padding);
		room_y = max_int(2, room_y);
		room_x2 = rand_int(room_max_width) + room_x + room_min_width;
		room_x2 = min_int(map_width - 2, room_x2);
		room_y2 = rand_int(room_max_height) + room_y + room_min_height;
		room_y2 = min_int(map_height - 2, room_y2);
		/* Check for collisions with existing rooms */
		for(int i = 0; i < rooms_added; ++i){
			if(room_x <= rooms[i].x2 &&
			room_x2 >= rooms[i].x &&
			room_y <= rooms[i].y2 &&
			room_y2 >= rooms[i].y){
			/* Collision detected */
				collision_detected = 1;
				break;	
			}		
		}
		/* Add new room to array */
		if(collision_detected == 0){
			rooms[rooms_added].x = room_x;
			rooms[rooms_added].y = room_y;
			rooms[rooms_added].x2 = room_x2;
			rooms[rooms_added].y2 = room_y2;
			++rooms_added;
		}
		collision_detected = 0;
	}
	/* "Carve" rooms into the map array */ 
	for(int i = 0; i < number_of_rooms; ++i){
		for(int j = rooms[i].y; j < rooms[i].y2; ++j){
			for(int k = rooms[i].x; k < rooms[i].x2; ++k){
				map_array[ j * map_width + k ] = '.';	
			}
		}
	}

	int xa,xb,ya,yb;
	Hall halls[number_of_rooms - 1];

	/* Create hallways in between rooms */ 
	/* Hall coords start at random points within a
	 * room and end randomly within the next room. */
	for(int i = 0; i < (number_of_rooms - 1); ++i){
		halls[i].x = rooms[i].x + rand_int(rooms[i].x2 - rooms[i].x);  
		halls[i].y = rooms[i].y + rand_int(rooms[i].y2 - rooms[i].y);  
		halls[i].x2 = rooms[i + 1].x + rand_int(rooms[i + 1].x2 - rooms[i + 1].x); 
		halls[i].y2 = rooms[i + 1].y + rand_int(rooms[i + 1].y2 - rooms[i + 1].y); 
	}	
	/* "Carve" hallways in the map array */
	for(int i = 0; i < (number_of_rooms - 1); ++i){
		/* define hallway endpoints */
		xa = min_int(halls[i].x,halls[i].x2);
		xb = max_int(halls[i].x,halls[i].x2);
		ya = min_int(halls[i].y,halls[i].y2);
		yb = max_int(halls[i].y,halls[i].y2);

		/* horizontal portions of hallways */
		for(int j = xa; j <= xb; ++j){
			map_array[ (halls[i].y * map_width) + j ] = '.';
		}
		/* verticle portions of hallways */
		for(int j = ya; j <= yb; ++j){
			map_array[ (j * map_width) + halls[i].x2 ] = '.';
		}
	}
}
