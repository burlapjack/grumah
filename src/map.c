/* map.c * by burlapjack 2021
 * procedural map generation
 */

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../include/map.h"
#include "../include/component.h"

/*---------------------- Initialize map data ---------------------------------------------------------------------------------*/
void map_init(MapData *m, int map_width, int map_height){

	m->map_width = map_width;
	m->map_height = map_height;

	m->map = malloc( sizeof (*(m->map)) * (map_width * map_height));
	

	m->number_of_rooms = 12;
	m->room_max_width = 7;
	m->room_max_height = 7;
	m->room_min_width = 4;
	m->room_min_height = 4;	
	m->room_padding = 2;

	m->entrance = '.';
	m->exit = '<';	
	m->door_horizontal_closed = '-';
	m->door_horizontal_open = '/';
	m->door_vertical_closed = '|';
	m->door_vertical_open= '-';
	m->floor = '.';	
	m->hallway = '.';
	m->wall = '#';

	m->color_entrance = 1;
	m->color_exit = 1;
	m->color_door_horizontal = 1;
	m->color_door_vertical = 1;
	m->color_floor = 1;
	m->color_wall = 1;	

	map_fill(m);
}

/*---------------------- Deallocate map data ---------------------------------------------------------------------------------*/
void map_free(MapData *m){
	free(m->map);
	m->map = NULL;
	free(m);
	m = NULL;
}

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

/*---------------------- Carve doors -----------------------------------------------------------------------------------------*/
static void map_carve_room(MapData *m, Room *rooms, int rooms_added){
	/* "Carve" rooms into the map array */ 
	for(int i = 0; i < rooms_added; ++i){
		for(int j = rooms[i].y; j < rooms[i].y2; ++j){
			for(int k = rooms[i].x; k < rooms[i].x2; ++k){
				m->map[ j * m->map_width + k ] = m->floor;	
			}
		}
	}
}

/*---------------------- Generate doors on the edges of each room ------------------------------------------------------------*/
void map_generate_doors(MapData *m, Room *rooms, int number_of_rooms){
	char top, bottom, left, right;
	/* y coord */
	for(int i = 1; i < (m->map_height-1); ++i){
		/* x coord */
		for(int j = 1; j < (m->map_width-1); ++j){
			/* surrounding tiles */
			top = m->map[(i - 1) * m->map_width + j];
			bottom = m->map[(i + 1) * m->map_width + j];
			left = m->map[ i * m->map_width + j - 1];
			right = m->map[i * m->map_width + j + 1];
			/* check surrounding area of each floor tile  */
			if( m->map[i * m->map_width + j] == m->floor){	
				/* horizontal doors */
				if( top == m->floor && bottom ==  m->floor && left == m->wall && right == m->wall){
					for(int k = 0; k < number_of_rooms; ++k){
						if(rooms[k].x <= j && rooms[k].x2 >= j && (rooms[k].y == i + 1 || rooms[k].y2 == i)){
							m->map[i * m->map_width + j] = m->door_horizontal_closed;
						}	
					}
				}
				/* vertical doors */
				else if( top == m->wall && bottom == m->wall && left == m->floor && right == m->floor){
					for(int k = 0; k < number_of_rooms; ++k){
						if((rooms[k].x == j + 1 || rooms[k].x2 == j) && rooms[k].y <= i && rooms[k].y2 >= i){
							m->map[i * m->map_width + j] = m->door_vertical_closed;
						}	
					}
				}
			}
		}
	}
}

void map_generate_hallways(MapData *m, Room *rooms, int rooms_added){
	int xa,xb,ya,yb;
	int random_direction;
	Hall halls[rooms_added - 1];

	Room temp;
	/* sort rooms from right to left */
	/* this will prevent hallways from looking like a mess */
	for(int i = 0; i < rooms_added-1; ++i){
		for( int j = 0; j < rooms_added; ++j){
			if (rooms[i].x > rooms[j].x){
				temp = rooms[i];
				rooms[i] = rooms[j];
				rooms[j] = temp;			
			}
		}	
	}

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
		random_direction = rand_int(4);	
		if(random_direction > 2){
			map_carve_hall_horizontally(m, halls, i, xa, xb);
			map_carve_hall_vertically(m, halls, i, ya, yb);
		}
		else{
			map_carve_hall_vertically(m, halls, i, ya, yb);
			map_carve_hall_horizontally(m, halls, i, xa, xb);
		}
	}
}

/*---------------------- Map Generation: Simple Room Placement ---------------------------------------------------------------*/
/* Rooms are added one at a time wherever they will fit, then hallways are created between them. */
void map_generate_srp(MapData *m){
	int room_x,room_y, room_x2, room_y2;
	int rooms_added = 0;
	int collision_detected = 0;
	int fails = 0;         /* number of times in a row a new random room has collided with other room positions */
	int fail_limit = 100;  /* prevents an endless loop */
	Room rooms[m->number_of_rooms];	

	/* Start a fresh map, filled with all walls. */
	map_fill(m);

	/* Room Creation */
	while(rooms_added < m->number_of_rooms){
		/* Propose random room coordinates */
		room_x = rand_int(m->map_width - m->room_max_width - 2 );
		room_x = max_int(2, room_x);
		room_y = rand_int(m->map_height - m->room_max_height - 2 );
		room_y = max_int(2, room_y);
		room_x2 = rand_int(m->room_max_width) + room_x + m->room_min_width;
		room_x2 = min_int(m->map_width - 2, room_x2);
		room_y2 = rand_int(m->room_max_height) + room_y + m->room_min_height;
		room_y2 = min_int(m->map_height - 2, room_y2);

		/* Check for collisions with existing rooms */
		for(int i = 0; i < rooms_added; ++i){
			if(room_x - m->room_padding <= rooms[i].x2 &&
			room_x2 + m->room_padding  >= rooms[i].x &&
			room_y - m->room_padding <= rooms[i].y2  &&
			room_y2 + m->room_padding  >= rooms[i].y ){
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
	map_carve_room(m, rooms, rooms_added);
	map_generate_hallways(m, rooms, rooms_added);
	map_generate_doors(m, rooms, rooms_added);
}

void map_generate_bsp(MapData *m){
	int room_x,room_y, room_x2, room_y2;
	Room partition;
	int split_x, split_y;
	int div; /* 1=horizontal, 2=verticle */
	int rooms_added = 0;
	int collision_detected = 0;
	int fails = 0;         /* number of times in a row a new random room has collided with other room positions */
	int fail_limit = 100;  /* prevents an endless loop */
	int part_min_w = m->room_min_width + m->room_padding * 2;
	int part_min_h = m->room_min_height + m->room_padding * 2;
	int part_max_w = m->room_max_width + m->room_padding * 2;
	int part_max_h = m->room_max_height + m->room_padding * 2;
	Room rooms[m->number_of_rooms];	

	/* Start a fresh map, filled with all walls. */
	map_fill(m);

	/* Room loop */	
	while(rooms_added < m->number_of_rooms){
		partition.x = 0;
		partition.y = 0;
		partition.x2 = m->map_width;
		partition.y2 = m->map_height;
		split_x = 0;
		split_y = 0;
		int w = partition.x2 - partition.x;
		int h = partition.y2 - partition.y;
		/* partitioning loop */	
		while(1){
			div = rand_int(3);
			if(div == 1){ /* horizontal split */
				split_y = rand_int(partition.y2 - partition.y);
				if(max_int(split_y, (partition.y2 - split_y)) > part_min_h){
					/* choose the smaller section */
					if(split_y > (partition.y2 - split_y)) partition.y2 = split_y;	
					else partition.y = split_y;
				}
			} 
			else{ /* verticle split */
				split_x = rand_int(partition.x2 - partition.x);
				if(max_int(split_x, (partition.x2 - split_x)) > part_min_w){
					/* choose the smaller section */
					if(split_x > (partition.x2 - split_x)) partition.x2 = split_x;	
					else partition.x = split_x;
				}
			}
			w = partition.x2 - partition.x;
			h = partition.y2 - partition.y;

			/* Determine if the partition is large enough to hold a room */
			if(w <= part_max_w &&  w >= part_min_w && h <= part_max_h && h >= part_min_h){
				room_x = partition.x + m->room_padding;
				room_y = partition.y + m->room_padding;
				room_x2 = partition.x2 - m->room_padding;
				room_y2 = partition.y2 - m->room_padding;
				break;
			}
		}

		/* check collisions with existing rooms */
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
		/* store map coordinates */
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

	map_carve_room(m, rooms, rooms_added);
	map_generate_hallways(m, rooms, rooms_added);
}

void map_generate_ca(MapData *m){
	int iterations = 4;
	int rand_tile;
	int neighbor_walls;
	char map_copy[m->map_width * m->map_height];

	/* generate random noise (wall and floor tiles) on the map copy */	
	for(int i = 0; i < m->map_height; ++i){
		for(int j = 0; j < m->map_width; ++j){
			/* everything  is random - wall or floor */	
			rand_tile = rand_int(10);
			if(rand_tile > 3) map_copy[ i * m->map_width + j ] = m->floor;
			else map_copy[ i * m->map_width + j ] = m->wall;
		}
	}
	int n = 0;
	while(n < iterations){	
		for(int i = 1; i < m->map_height - 1; ++i){
			for(int j = 1; j < m->map_width - 1; ++j){
				neighbor_walls = 0;
				if( map_copy[ i * m->map_width + j - 1 ] == m->wall) ++neighbor_walls; /* left */	
				if( map_copy[ i * m->map_width + j + 1 ] == m->wall) ++neighbor_walls; /* right */	
				if( map_copy[ (i - 1) * m->map_width + j ] == m->wall) ++neighbor_walls; /* top */	
				if( map_copy[ (i + 1) * m->map_width + j ] == m->wall) ++neighbor_walls; /* bottom */	
				if( map_copy[ (i - 1) * m->map_width + j - 1 ] == m->wall) ++neighbor_walls; /* top-left */	
				if( map_copy[ (i - 1) * m->map_width + j + 1 ] == m->wall) ++neighbor_walls; /* top-right */	
				if( map_copy[ (i + 1) * m->map_width + j + 1 ] == m->wall) ++neighbor_walls; /* bottom-right */	
				if( map_copy[ (i + 1) * m->map_width + j - 1 ] == m->wall) ++neighbor_walls; /* bottom-left */	
				
				if( m->map[ i * m->map_width + j ] == m->wall && neighbor_walls >= 4) m->map[ i * m->map_width + j] = m->wall;
				else if( m->map[ i * m->map_width + j ] == m->floor && neighbor_walls >= 5) m->map[ i * m->map_width + j] = m->wall;
				else m->map[ i * m->map_width + j] = m->floor;
			}
		}	
		memcpy(map_copy, m->map, m->map_width * m->map_height);
		++n;
	}
}
