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

void map_gen_rooms(Component *c, char *map_array, int map_width, int map_height, int number_of_rooms, int room_max_width, int room_max_height){

}

