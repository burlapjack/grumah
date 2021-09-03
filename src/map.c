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


/*---------------------- Init a map that is all walls ------------------------------------------------------------------------*/
char** map_init(char **map,int map_width, int map_height){
	unsigned int i;
	map = malloc( sizeof(*map) * map_height );
	for(i = 0; i < map_height; i++){
		map[i] = malloc( sizeof (*map) * map_width);
	};
};

/*---------------------- Simple-Room-Placement Map Gen Algorithm -------------------------------------------------------------*/


