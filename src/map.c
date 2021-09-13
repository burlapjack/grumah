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

/*------ "Carve" a horizontal hallway int the map array ----------------------------------------------------------------------*/
static void map_carve_hall_horizontally(MapData *m, Hall *halls_array, int hall_index, int xstart, int xend){
	for(int j = xstart; j <= xend; ++j){
		m->map[ (halls_array[hall_index].y * m->map_width) + j ] = '.';
	}
}

/*------ "Carve" a verticle hallway int the map array ------------------------------------------------------------------------*/
static void map_carve_hall_vertically(MapData *m, Hall *halls_array, int hall_index, int ystart, int yend){
	for(int j = ystart; j <= yend; ++j){
		m->map[ (j * m->map_width) + halls_array[hall_index].x2 ] = '.';
	}
}

/*---------------------- Fill a map so that it is all walls ------------------------------------------------------------------*/
void map_fill(MapData *m){
	for ( int i = 0; i < m->map_height; i++){
		for ( int j = 0; j < m->map_width; j++){
			m->map[ i * m->map_width + j] = m->wall;
		}
	}	
}

/*---------------------- Initialize map settings -----------------------------------------------------------------------------*/
void map_init(MapData *m, int map_width, int map_height){
	m->map = malloc( sizeof (*(m->map)) * map_width * map_height);
	m->map_width = map_width;
	m->map_height = map_height;
	m->number_of_rooms = 8;
	m->room_max_width = 8;
	m->room_max_height = 8;
	m->room_min_width = 4;
	m->room_min_height = 4;	

	m->entrance = '.';
	m->exit = '<';	
	m->door_horizontal_closed = '-';
	m->door_horizontal_open = '/';
	m->door_vertical_closed = '|';
	m->door_vertical_open= '-';
	m->floor = '.';	
	m->wall = '#';

	m->color_entrance = 1;
	m->color_exit = 1;
	m->color_door_horizontal = 1;
	m->color_door_vertical = 1;
	m->color_floor = 1;
	m->color_wall = 1;	
}



/*---------------------- Map Generation: Simple Room Placement ---------------------------------------------------------------*/
/* Rooms are added one at a time wherever they will fit, then hallways are created between them.  */
//void map_generate_srp(char *map_array, int map_width, int map_height, int number_of_rooms, int room_min_width, int room_min_height, int room_max_width, int room_max_height){
void map_generate_srp(MapData *m){
	int room_x,room_y, room_x2, room_y2;
	int rooms_added = 0;
	int padding = 2;
	int collision_detected = 0;
	int fails = 0;         /* number of times in a row a new random room has collided with other room positions */
	int fail_limit = 100;  /* prevents an endless loop */
	Room rooms[m->number_of_rooms];	

	/* Start a fresh map, filled with all walls. */
	map_fill(m);

	/* Room Creation */
	while(rooms_added < m->number_of_rooms){
		/* Propose random room coordinates */
		room_x = rand_int(m->map_width - m->room_max_width - padding);
		room_x = max_int(2, room_x);
		room_y = rand_int(m->map_height - m->room_max_height - padding);
		room_y = max_int(2, room_y);
		room_x2 = rand_int(m->room_max_width) + room_x + m->room_min_width;
		room_x2 = min_int(m->map_width - 2, room_x2);
		room_y2 = rand_int(m->room_max_height) + room_y + m->room_min_height;
		room_y2 = min_int(m->map_height - 2, room_y2);
		/* Check for collisions with existing rooms */
		for(int i = 0; i < rooms_added; ++i){
			if(room_x <= rooms[i].x2 &&
			room_x2 >= rooms[i].x &&
			room_y <= rooms[i].y2 &&
			room_y2 >= rooms[i].y){
			/* Collision detected */
				collision_detected = 1;
				++fails;
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
			fails = 0;
		}
		collision_detected = 0;
		if(fails == fail_limit) break;
	}
	/* "Carve" rooms into the map array */ 
	for(int i = 0; i < rooms_added; ++i){
		for(int j = rooms[i].y; j < rooms[i].y2; ++j){
			for(int k = rooms[i].x; k < rooms[i].x2; ++k){
				m->map[ j * m->map_width + k ] = m->floor;	
			}
		}
	}
	int xa,xb,ya,yb;
	int random_direction;
	Hall halls[rooms_added - 1];

	/* Create hallways in between rooms */ 
	/* Hall coords start at random points within a
	 * room and end randomly within the next room. */
	for(int i = 0; i < (rooms_added - 1); ++i){
		halls[i].x = rooms[i].x + rand_int(rooms[i].x2 - rooms[i].x);  
		halls[i].y = rooms[i].y + rand_int(rooms[i].y2 - rooms[i].y);  
		halls[i].x2 = rooms[i + 1].x + rand_int(rooms[i + 1].x2 - rooms[i + 1].x); 
		halls[i].y2 = rooms[i + 1].y + rand_int(rooms[i + 1].y2 - rooms[i + 1].y); 
	}	
	/* "Carve" hallways in the map array */
	for(int i = 0; i < (rooms_added - 1); ++i){
		/* define hallway endpoints */
		xa = min_int(halls[i].x,halls[i].x2);
		xb = max_int(halls[i].x,halls[i].x2);
		ya = min_int(halls[i].y,halls[i].y2);
		yb = max_int(halls[i].y,halls[i].y2);

		/* Randomly pick the horizontal and verticle carve order of hallway. */
		random_direction = rand_int(10);	
		if(random_direction >= 6){
			map_carve_hall_horizontally(m, halls, i, xa, xb);
			map_carve_hall_vertically(m, halls, i, ya, yb);
		}
		else{
			map_carve_hall_vertically(m, halls, i, ya, yb);
			map_carve_hall_horizontally(m, halls, i, xa, xb);
		}
	}

}




