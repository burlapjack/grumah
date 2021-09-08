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

void map_init(Component *c, int map_width, int map_height, unsigned int *next_id){

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
	unsigned int id = 0;
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
	unsigned int id = 0;
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
void map_generate_rooms(Component *c, size_t number_of_rooms, int map_height, int map_width, int room_max_width, int room_max_height){
	int room_x, room_x2, room_y, room_y2;	
	int room_padding = 2;
	size_t i = 0;
	int px, py;
	int collision;
	char ch;	
	while (i < number_of_rooms){
		room_x = rand_int( map_width - room_max_width - room_padding );
		room_x = max_int(2,room_x);
		room_y = rand_int( map_height - room_max_height - room_padding );
		room_y = max_int(2,room_y);
		room_x2 = rand_int( room_max_width ) + room_x;
		room_x2 = min_int((map_width - room_padding), room_x2);
		room_y2 = rand_int( room_max_height ) + room_y;
		room_y2 = min_int((map_height - room_padding), room_y2);
		collision = 0;
		for(size_t j = 0; j < c->size_position; j++){
			px = c->position[j].x;
			py = c->position[j].y;
			if(
					(room_x == px && room_y == py)  || 
					(room_x2 == px && room_y2 == py)|| 
					(room_x2 == px && room_y == py) ||
					(room_x == px && room_y2 == py) ){
				collision = 1;
				break;
			}	
		}
		if(collision == 0){
			for(size_t j = room_y; j < room_y2; j++){
				for(size_t k = room_x; k < room_x2; k++){
					map_replace_symbol(c, j, k, '#', '.');
				}
			}
		}
	}	
}
