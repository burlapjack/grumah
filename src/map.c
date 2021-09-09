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

/*---------------------- Init a map that is all walls --------------------------------------------*/

void map_init(Component *c, int map_width, int map_height, int *next_id){

	for ( int i = 0; i < map_height; i++){
		for ( int j = 0; j < map_width; j++){
			component_add_position(c, *next_id, j, i);
			component_add_draw(c, *next_id, 0, 1, '#'); 
			*next_id += 1;
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

/*---------------------- Randomly Placed Rooms ---------------------------------------------------*/

void map_generate_rooms(Component *c, char *map_array, int map_width, int map_height, int number_of_rooms, int room_max_width, int room_max_height){
	int room_x,room_y, room_x2, room_y2;
	int rooms_added;
	int padding = 2;
	int collision_detected = 0;
	Room rooms[number_of_rooms];	

	while(rooms_added < number_of_rooms){
		/*--------- Propose random room coordinates -----------*/
		room_x = rand_int(map_width - room_max_width - padding);
		room_x = max_int(2, room_x);
		room_y = rand_int(map_height - room_max_height - padding);
		room_y = max_int(2, room_y);
		room_x2 = rand_int(room_max_width) + room_x;
		room_x2 = min_int(map_width - 2, room_x2);
		room_y2 = rand_int(room_max_height) + room_y;
		room_y2 = min_int(map_height - 2, room_y2);

		for(int i = 0; i < rooms_added; ++i){
			if(room_x < rooms[i].x2 &&
			room_x2 > rooms[i].x &&
			room_y < rooms[i].y2 &&
			room_y2 > rooms[i].y){
				/*--------- Collision detected ---------------*/
				collision_detected = 1;
				break;	
			}		
		}
		if(collision_detected == 0){
			rooms[rooms_added].x = room_x;
			rooms[rooms_added].y = room_y;
			rooms[rooms_added].x2 = room_x2;
			rooms[rooms_added].y2 = room_y2;
			++rooms_added;
		}
	}

	for(int i = 0; i < number_of_rooms; ++i){
		for(int j = rooms[i].y; j < rooms[i].y2; ++j){
			for(int k = rooms[i].x; k < rooms[i].x2; ++k){
				map_array[ j * map_width + k ] = '.';	
			}
		}
	}

}

