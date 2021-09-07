/* map.c * by burlapjack 2021
 * procedural map generation
 */

#include <stdlib.h>
#include <assert.h>
#include <ncurses.h>
#include "../include/map.h"
#include "../include/component.h"

/*--------------------- Pseudo-random number generator ----------------------------------------------------------------------*/

//static int rand_int(int n){
//	if((n - 1) == RAND_MAX){
//		return rand();
//	} else {
//		assert(n <= RAND_MAX);
//		int end = RAND_MAX / n;
//		assert (end > 0);
//		end *= n;
//		int r;
//		while ((r = rand()) >= end);
//		return r % n;
//	}
//}


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
