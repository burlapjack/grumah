/* map.c * by burlapjack 2021
 * procedural map generation
 */
#include <stdlib.h>
#include <ncurses.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include "../include/gr_map.h"
#include "../include/gr_component.h"
#include "../include/gr_path.h"


/*---------------------- Initialize map data ---------------------------------------------------------------------------------*/
void gr_map_init(MapData *m, int map_width, int map_height){
	m->map_width = map_width;
	m->map_height = map_height;
	m->map_x_offset = 0;
	m->map_y_offset = 0;
	m->terrain = malloc( sizeof (*(m->terrain)) * (map_width * map_height));
	m->number_of_rooms = 12;
	m->room_max_width = 7;
	m->room_max_height = 7;
	m->room_min_width = 4;
	m->room_min_height = 4;
	m->room_padding = 2;
	m->entrance = '<';
	m->exit = '>';
	m->door_horizontal_closed = '+';
	m->door_horizontal_open = '|';
	m->door_vertical_closed = '+';
	m->door_vertical_open= '-';
	m->floor = '.';
	m->hallway_horizontal = '.';
	m->hallway_vertical = '.';
	m->wall = '#';
	m->color_entrance = 1;
	m->color_exit = 1;
	m->color_door_horizontal = 1;
	m->color_door_vertical = 1;
	m->color_floor = 1;
	m->color_wall = 1;
	gr_map_gen_fill(m);
}

/*---------------------- Deallocate map data ---------------------------------------------------------------------------------*/
void gr_map_free(MapData *m){
	free(m->terrain);
	m->terrain = NULL;
	free(m);
	m = NULL;
}

int gr_map_count_tile(MapData *m, char tile){
	int count = 0;
	for(int i = 0; i < m->map_height; i++){
		for(int j = 0; j < m->map_width; j++){
			if(m->terrain[ i * m->map_width + j ] == tile) count++;
		}
	}
	return count;
}

/*------ Find the largest of two integers ------------------------------------------------------------------------------------*/
int gr_max_int(int a, int b){
	if (a > b) return a; else return b;
}

/*------ Find the smallest of two integers -----------------------------------------------------------------------------------*/
int gr_min_int(int a, int b){
	if (a < b) return a; else return b;
}

/*--------------------- Pseudo-random number generator ----------------------------------------------------------------------*/
int gr_rand_int(int n){
	if((n - 1) == RAND_MAX) return rand();
	else {
		assert(n <= RAND_MAX);
		int end = RAND_MAX / n;
		assert (end > 0);
		end *= n;
		int r;
		while ((r = rand()) >= end);
		return r % n;
	}
}

/*------ "Carve" a horizontal hallway int the map array ----------------------------------------------------------------------*/
void gr_map_gen_carve_hall_horizontally(MapData *m, Hall *halls_array, int hall_index, int xstart, int xend){
	for(int j = xstart; j <= xend; j++){
		if(m->terrain[(halls_array[hall_index].y * m->map_width) + j ] != m->entrance && m->terrain[(halls_array[hall_index].y * m->map_width) + j ] != m->exit){
			m->terrain[ (halls_array[hall_index].y * m->map_width) + j ] = m->hallway_horizontal;
		}
	}
}

/*------ "Carve" a verticle hallway int the map array ------------------------------------------------------------------------*/
void gr_map_gen_carve_hall_vertically(MapData *m, Hall *halls_array, int hall_index, int ystart, int yend){
	for(int j = ystart; j <= yend; j++){
		if(m->terrain[ (j * m->map_width) + halls_array[hall_index].x2  ] != m->entrance && m->terrain[ (j * m->map_width) + halls_array[hall_index].x2 ] != m->exit){
			m->terrain[ (j * m->map_width) + halls_array[hall_index].x2 ] = m->hallway_vertical;
		}
	}
}

/*---------------------- Carve rooms -----------------------------------------------------------------------------------------*/
void gr_map_gen_carve_room(MapData *m, Room *rooms, int rooms_added){
	/* "Carve" rooms into the map array */
	for(int i = 0; i < rooms_added; i++){
		for(int j = rooms[i].y; j < rooms[i].y2; j++){
			for(int k = rooms[i].x; k < rooms[i].x2; k++){
				m->terrain[ j * m->map_width + k ] = m->floor;
			}
		}
	}
}

/*---------------------- Generate doors on the edges of each room ------------------------------------------------------------*/
void gr_map_gen_carve_hallways(MapData *m, Room *rooms, int rooms_added){
	int xa,xb,ya,yb;
	int random_direction;
	Hall halls[rooms_added - 1];

	Room temp;
	/* sort rooms from right to left */
	/* this will prevent hallways from looking like a mess */
	for(int i = 0; i < rooms_added-1; i++){
		for( int j = 0; j < rooms_added; j++){
			if (rooms[i].x > rooms[j].x){
				temp = rooms[i];
				rooms[i] = rooms[j];
				rooms[j] = temp;
			}
		}
	}

	/* Create hallways in between rooms */
	/* Hall coords start at random points within a */
	/* room and end randomly within the next room. */
	for(int i = 0; i < (rooms_added - 1); i++){
		halls[i].x = rooms[i].x + gr_rand_int(rooms[i].x2 - rooms[i].x);
		halls[i].y = rooms[i].y + gr_rand_int(rooms[i].y2 - rooms[i].y);
		halls[i].x2 = rooms[i + 1].x + gr_rand_int(rooms[i + 1].x2 - rooms[i + 1].x);
		halls[i].y2 = rooms[i + 1].y + gr_rand_int(rooms[i + 1].y2 - rooms[i + 1].y);
	}
	/* "Carve" hallways in the map array */
	for(int i = 0; i < (rooms_added - 1); i++){
		/* define hallway endpoints */
		xa = gr_min_int(halls[i].x,halls[i].x2);
		xb = gr_max_int(halls[i].x,halls[i].x2);
		ya = gr_min_int(halls[i].y,halls[i].y2);
		yb = gr_max_int(halls[i].y,halls[i].y2);

		/* Randomly pick the horizontal and verticle carve order of hallway. */
		random_direction = gr_rand_int(4);
		if(random_direction > 2){
			gr_map_gen_carve_hall_horizontally(m, halls, i, xa, xb);
			gr_map_gen_carve_hall_vertically(m, halls, i, ya, yb);
		}
		else{
			gr_map_gen_carve_hall_vertically(m, halls, i, ya, yb);
			gr_map_gen_carve_hall_horizontally(m, halls, i, xa, xb);
		}
	}
}

/*---------------------- Fill a map so that it is all walls ------------------------------------------------------------------*/
void gr_map_gen_fill(MapData *m){
	for ( int i = 0; i < m->map_height; i++){
		for ( int j = 0; j < m->map_width; j++){
			m->terrain[ i * m->map_width + j] = m->wall;
		}
	}
}

/*---------------------- Generate doors on the edges of each room ------------------------------------------------------------*/
void gr_map_gen_doors(MapData *m, Room *rooms, int number_of_rooms){
	char top, bottom, left, right;
	/* y coord */
	for(int i = 1; i < (m->map_height-1); i++){ /* y coord */
		for(int j = 1; j < (m->map_width-1); j++){ /* x coord */
			/* surrounding tiles */
			top = m->terrain[(i - 1) * m->map_width + j];
			bottom = m->terrain[(i + 1) * m->map_width + j];
			left = m->terrain[ i * m->map_width + j - 1];
			right = m->terrain[i * m->map_width + j + 1];
			if( m->terrain[i * m->map_width + j] == m->floor){ /* check all candidates for doors */
				/* horizontal doors */
				if( ((top == m->hallway_vertical && bottom ==  m->floor) || (top == m->floor && bottom ==  m->hallway_vertical)) && left == m->wall && right == m->wall){ /* top and bottom are floor */
					for(int k = 0; k < number_of_rooms; k++){
						if(rooms[k].x <= j && rooms[k].x2 >= j && (rooms[k].y == i + 1 || rooms[k].y2 == i)){
							m->terrain[i * m->map_width + j] = m->door_horizontal_closed;
						}
					}
				}
				/* vertical doors */
				else if( top == m->wall && bottom == m->wall && ((left == m->hallway_horizontal && right == m->floor) || (left == m->floor && right == m->hallway_horizontal))){
					for(int k = 0; k < number_of_rooms; k++){
						if((rooms[k].x == j + 1 || rooms[k].x2 == j) && rooms[k].y <= i && rooms[k].y2 >= i){
							m->terrain[i * m->map_width + j] = m->door_vertical_closed;
						}
					}
				}
			}
		}
	}
}

/*---------------------- Map Generation: Simple Room Placement ---------------------------------------------------------------*/
/* Rooms are added one at a time wherever they will fit, then hallways are created between them. */
void gr_map_gen_style_dungeon(MapData *m, Component *c){
	int room_x,room_y, room_x2, room_y2;
	int rooms_added = 0;
	int collision_detected = 0;
	int fails = 0;         /* number of times in a row a new random room has collided with other room positions */
	int fail_limit = 100;  /* prevents an endless loop */
	Room rooms[m->number_of_rooms];

	/* Start a fresh map, filled with all walls. */
	gr_map_gen_fill(m);

	/* Room Creation */
	while(rooms_added < m->number_of_rooms){
		/* Propose random room coordinates */
		room_x = gr_rand_int(m->map_width - m->room_max_width - 2 );
		room_x = gr_max_int(2, room_x);
		room_y = gr_rand_int(m->map_height - m->room_max_height - 2 );
		room_y = gr_max_int(2, room_y);
		room_x2 = gr_rand_int(m->room_max_width) + room_x + m->room_min_width;
		room_x2 = gr_min_int(m->map_width - 2, room_x2);
		room_y2 = gr_rand_int(m->room_max_height) + room_y + m->room_min_height;
		room_y2 = gr_min_int(m->map_height - 2, room_y2);

		/* Check for collisions with existing rooms */
		for(int i = 0; i < rooms_added; i++){
			if(room_x - m->room_padding <= rooms[i].x2 &&
			room_x2 + m->room_padding  >= rooms[i].x &&
			room_y - m->room_padding <= rooms[i].y2  &&
			room_y2 + m->room_padding  >= rooms[i].y ){
			/* Collision detected */
				collision_detected = 1;
				fails++;
				break;
			}
		}
		/* Add new room to array */
		if(collision_detected == 0){
			rooms[rooms_added].x = room_x;
			rooms[rooms_added].y = room_y;
			rooms[rooms_added].x2 = room_x2;
			rooms[rooms_added].y2 = room_y2;
			rooms_added++;
			fails = 0;
		}
		collision_detected = 0;
		if(fails == fail_limit) break;
	}
	gr_map_gen_carve_room(m, rooms, rooms_added);
	gr_map_gen_entrance_and_exit(m);
	gr_map_gen_carve_hallways(m, rooms, rooms_added);
	gr_map_gen_doors(m, rooms, rooms_added);

	gr_map_gen_add_components(m, c);
}

/*---------------------- Map Generation: Cellular Automata -------------------------------------------------------------------*/
void gr_map_gen_style_cave(MapData *m, Component *c){
	int iterations = 2; /* number of times the map is "smoothed".  The default is 2. */
	int rand_tile;
	int neighbor_walls;
	char terrain_copy[m->map_width * m->map_height];

	/* generate random noise (wall and floor tiles) on the map copy */
	for(int i = 0; i < m->map_height; i++){
		for(int j = 0; j < m->map_width; j++){
			if( i == 0 || i == m->map_height || j == 0 || j == m->map_width){ /* surround the map with walls. */
				terrain_copy[ i * m->map_width + j ] = m->wall;
			}
			else{
				if( m->map_height > 4 && i > (m->map_height / 2) && i < (m->map_height / 2) + 2){ /* create empty strip in middle of map */
					terrain_copy[i * m->map_width + j] = m->floor;
				}
				else{
					rand_tile = gr_rand_int(10);
					if(rand_tile > 4) terrain_copy[ i * m->map_width + j ] = m->floor; /* everything  is random - wall or floor */
					else terrain_copy[ i * m->map_width + j ] = m->wall;
				}
			}
		}
	}
	int n = 0;
	while(n < iterations){
		for(int i = 2; i < m->map_height - 2; i++){
			for(int j = 2; j < m->map_width - 2; j++){
				neighbor_walls = 0;
				if( terrain_copy[ i * m->map_width + j - 1 ] == m->wall ) neighbor_walls++; /* left */
				if( terrain_copy[ i * m->map_width + j + 1 ] == m->wall ) neighbor_walls++; /* right */
				if( terrain_copy[ (i - 1) * m->map_width + j ] == m->wall ) neighbor_walls++; /* top */
				if( terrain_copy[ (i + 1) * m->map_width + j ] == m->wall ) neighbor_walls++; /* bottom */
				if( terrain_copy[ (i - 1) * m->map_width + j - 1 ] == m->wall ) neighbor_walls++; /* top-left */
				if( terrain_copy[ (i - 1) * m->map_width + j + 1 ] == m->wall ) neighbor_walls++; /* top-right */
				if( terrain_copy[ (i + 1) * m->map_width + j + 1 ] == m->wall ) neighbor_walls++; /* bottom-right */
				if( terrain_copy[ (i + 1) * m->map_width + j - 1 ] == m->wall ) neighbor_walls++; /* bottom-left */

				/* if 4 neighbor walls and current tile is a wall,  stay a wall */
				if( terrain_copy[ i * m->map_width + j ] == m->wall && neighbor_walls >= 4) m->terrain[ i * m->map_width + j] = m->wall;
				else if( terrain_copy[ i * m->map_width + j ] == m->floor && neighbor_walls >= 5) m->terrain[ i * m->map_width + j] = m->wall;
				else  m->terrain[ i * m->map_width + j] = m->floor;
			}
		}
		memcpy(terrain_copy, m->terrain, sizeof (char) * m->map_width * m->map_height);
		n++;
	}

	int rand_x, rand_y;
	while(1){  /* remove disconnected caves. */
		rand_x = gr_max_int( gr_rand_int(m->map_width - 2), 2);
		rand_y = gr_max_int( gr_rand_int(m->map_height - 2), 2);
		if(m->terrain[rand_y * m->map_width + rand_x] == m->floor){
			gr_map_flood_fill(m, rand_x, rand_y, 'o');
			break;
		}
	}
	for(int i = 0; i < m->map_height; i++){ /* fill in unwanted parts of the map */
		for(int j = 0; j < m->map_width; j++){
			if(m->terrain[ i * m->map_width + j ] == m->floor) m->terrain[ i * m->map_width + j ] = m->wall;
			if(m->terrain[ i * m->map_width + j ] == 'o') m->terrain[ i * m->map_width + j ] = m->floor;
		}
	}
	gr_map_gen_entrance_and_exit(m);
	gr_map_gen_add_components(m, c);
}

void gr_map_gen_entrance_and_exit(MapData *m){
	int entrance_x, entrance_y;
	int exit_x, exit_y;
	while(1){
		entrance_x = gr_max_int( gr_rand_int(m->map_width - 2), 2); /* randomly place an entrance and an exit */
		entrance_y = gr_max_int( gr_rand_int(m->map_height - 2), 2);
		exit_x = gr_max_int( gr_rand_int(m->map_width - 2), 2);
		exit_y = gr_max_int( gr_rand_int(m->map_height - 2), 2);
		if(m->terrain[entrance_y * m->map_width + entrance_x] == m->floor && m->terrain[exit_y * m->map_width + exit_x] == m->floor){ /* check if the entrance and exit are on floor tiles */
			if( gr_path_get_manhattan_distance(entrance_x, entrance_y, exit_x, exit_y) > 2 ){ /* ensure that the entrance and exit arent right next to each other. */
				m->terrain[(exit_y * m->map_width) + exit_x] = m->exit;
				m->terrain[(entrance_y * m->map_width) + entrance_x] = m->entrance;
				break; /* end while loop */
			}
		}
	}
}

void gr_map_gen_add_components(MapData *m, Component *c){
	for(int i = 0; i < m->map_height; i++){
		for(int j = 0; j < m->map_width; j++){
			gr_component_add_position(c, j, i);
			gr_component_add_draw(c, 0, 1, m->terrain[i * m->map_width + j]);
			c->next_id++;
		}
	}
}


/*--------------------- Fill an area with a given symbol/tile. --------------------------------------------------------------*/
void gr_map_flood_fill(MapData *m, int rand_x, int rand_y, char symbol){

	int current_index = 0;
	int number_of_nodes = 1;
	int list_size = gr_path_count_floor(m);
	FloodNode node_list[list_size];

	for(int i = 0; i < list_size; i++){
		node_list[i].x = -1;
		node_list[i].y = -1;
	};

	/* Add the first node outside of the main loop. */
	node_list[0].x = rand_x;
	node_list[0].y = rand_y;
	m->terrain[(rand_y * m->map_width) + rand_x] = symbol;

	int nx = node_list[0].x;
	int ny = node_list[0].y;

	int d[8][2] = {
		{ 0,  -1 }, /* north */     { 1,  -1 },	/* northeast */
		{ 1,   0 },	/* east  */     { 1,   1 },	/* southeast */
		{ 0,   1 },	/* south */     {-1,   1 },	/* southwest */
		{-1,   0 }, /* west  */	    {-1,  -1 }	/* northwest */
	};

	while(1){ /* main loop */

		nx = node_list[current_index].x;
		ny = node_list[current_index].y;

		/*---- check the map for neighboring nodes ---- */
		for(int i = 0; i < 8; i++){
			if(m->terrain[ (ny + d[i][1]) * m->map_width + (nx + d[i][0]) ] == m->floor){ /* check for floor tile on the map. */
				int exists = 0;

				for(int j = 0; j < number_of_nodes; j++){
					if( node_list[j].x == nx + d[i][0] && node_list[j].y == ny + d[i][1]) {
						exists = 1;
						break;
					}
				}
				if(exists == 0){
					node_list[number_of_nodes].x = nx + d[i][0];
					node_list[number_of_nodes].y = ny + d[i][1];
					number_of_nodes++;
					m->terrain[ ( (ny + d[i][1]) * m->map_width) +  nx + d[i][0] ] = symbol;
				}
			}
		}
		current_index++;
		if(node_list[current_index].x == -1) break;
	}
}

//float gr_map_dda(float slope, float dx, float dy){
	/* calculate the hypotenuse of a line at a given slope while you step 1 unit */
	/* in the x or 1 unit in the y direction. Return the lowest result. */

//	float sx = sqrtf( pow(1,2) + pow((dy/dx), 2) );
//	float sy = sqrtf( pow(1,2) + pow((dx/dy), 2) );
//	if(sx <= sy) return dx;
//	else if(sy < sx) return sy;
//}


void gr_map_los_raycast(MapData *m, Component *c, int origin_x, int origin_y, int range){
	double current_radians = 0;
	double  dx, dy;
	int mapx, mapy;

	for(int  j = 0; j < 360; j += 45){                     /* iterate radians. */
		for(int k = 0; k < range; k++){                    /* iterate length of ray. */
			current_radians = (double) j * M_PI / 180;
			dx = cos(current_radians) * (double) k;
			dy = sin(current_radians) * (double) k;
			mapx = origin_x + (int) dx;
			mapy = origin_y + (int) dy;
			if(m->terrain[ mapy * m->map_width + mapx ] == m->floor){
				/* light this tile up */
				for(int i = 0; i < c->size_position; i++){ /* search for position match. */
					if(c->position[i].x == dx && c->position[i].y == dy){
						c->draw[c->position[i].id].visibility = 2; /* set visibility to 2 (full visibility). */
					}
				}
			}
			else{
				break; /* move on to next ray angle */
			}
		}
	}

}
