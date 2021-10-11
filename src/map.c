/* map.c * by burlapjack 2021
 * procedural map generation
 */
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include "../include/map.h"
#include "../include/component.h"
#include "../include/path.h"


/*---------------------- Initialize map data ---------------------------------------------------------------------------------*/
void map_init(MapData *m, int map_width, int map_height){
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
	map_gen_fill(m);
}

/*---------------------- Deallocate map data ---------------------------------------------------------------------------------*/
void map_free(MapData *m){
	free(m->terrain);
	m->terrain = NULL;
	free(m);
	m = NULL;
}

int map_count_tile(MapData *m, char tile){
	int count = 0;
	for(int i = 0; i < m->map_height; i++){
		for(int j = 0; j < m->map_width; j++){
			if(m->terrain[ i * m->map_width + j ] == tile) count++;
		}
	}
	return count;
}

/*------ Find the largest of two integers ------------------------------------------------------------------------------------*/
int max_int(int a, int b){
	if (a > b) return a; else return b;
}

/*------ Find the smallest of two integers -----------------------------------------------------------------------------------*/
int min_int(int a, int b){
	if (a < b) return a; else return b;
}

/*--------------------- Pseudo-random number generator ----------------------------------------------------------------------*/
int rand_int(int n){
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
void map_gen_carve_hall_horizontally(MapData *m, Hall *halls_array, int hall_index, int xstart, int xend){
	for(int j = xstart; j <= xend; j++){
		if(m->terrain[(halls_array[hall_index].y * m->map_width) + j ] != m->entrance && m->terrain[(halls_array[hall_index].y * m->map_width) + j ] != m->exit){
			m->terrain[ (halls_array[hall_index].y * m->map_width) + j ] = m->hallway_horizontal;
		}
	}
}

/*------ "Carve" a verticle hallway int the map array ------------------------------------------------------------------------*/
void map_gen_carve_hall_vertically(MapData *m, Hall *halls_array, int hall_index, int ystart, int yend){
	for(int j = ystart; j <= yend; j++){
		if(m->terrain[ (j * m->map_width) + halls_array[hall_index].x2  ] != m->entrance && m->terrain[ (j * m->map_width) + halls_array[hall_index].x2 ] != m->exit){
			m->terrain[ (j * m->map_width) + halls_array[hall_index].x2 ] = m->hallway_vertical;
		}
	}
}

/*---------------------- Carve rooms -----------------------------------------------------------------------------------------*/
void map_gen_carve_room(MapData *m, Room *rooms, int rooms_added){
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
void map_gen_carve_hallways(MapData *m, Room *rooms, int rooms_added){
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
		halls[i].x = rooms[i].x + rand_int(rooms[i].x2 - rooms[i].x);
		halls[i].y = rooms[i].y + rand_int(rooms[i].y2 - rooms[i].y);
		halls[i].x2 = rooms[i + 1].x + rand_int(rooms[i + 1].x2 - rooms[i + 1].x);
		halls[i].y2 = rooms[i + 1].y + rand_int(rooms[i + 1].y2 - rooms[i + 1].y);
	}
	/* "Carve" hallways in the map array */
	for(int i = 0; i < (rooms_added - 1); i++){
		/* define hallway endpoints */
		xa = min_int(halls[i].x,halls[i].x2);
		xb = max_int(halls[i].x,halls[i].x2);
		ya = min_int(halls[i].y,halls[i].y2);
		yb = max_int(halls[i].y,halls[i].y2);

		/* Randomly pick the horizontal and verticle carve order of hallway. */
		random_direction = rand_int(4);
		if(random_direction > 2){
			map_gen_carve_hall_horizontally(m, halls, i, xa, xb);
			map_gen_carve_hall_vertically(m, halls, i, ya, yb);
		}
		else{
			map_gen_carve_hall_vertically(m, halls, i, ya, yb);
			map_gen_carve_hall_horizontally(m, halls, i, xa, xb);
		}
	}
}

/*---------------------- Fill a map so that it is all walls ------------------------------------------------------------------*/
void map_gen_fill(MapData *m){
	for ( int i = 0; i < m->map_height; i++){
		for ( int j = 0; j < m->map_width; j++){
			m->terrain[ i * m->map_width + j] = m->wall;
		}
	}
}

/*---------------------- Generate doors on the edges of each room ------------------------------------------------------------*/
void map_gen_doors(MapData *m, Room *rooms, int number_of_rooms){
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
void map_gen_style_dungeon(MapData *m, Component *c){
	int room_x,room_y, room_x2, room_y2;
	int rooms_added = 0;
	int collision_detected = 0;
	int fails = 0;         /* number of times in a row a new random room has collided with other room positions */
	int fail_limit = 100;  /* prevents an endless loop */
	Room rooms[m->number_of_rooms];

	/* Start a fresh map, filled with all walls. */
	map_gen_fill(m);

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
	map_gen_carve_room(m, rooms, rooms_added);
	map_gen_entrance_and_exit(m);
	map_gen_carve_hallways(m, rooms, rooms_added);
	map_gen_doors(m, rooms, rooms_added);

	map_gen_add_components(m, c);
}

/*---------------------- Map Generation: Cellular Automata -------------------------------------------------------------------*/
void map_gen_style_cave(MapData *m, Component *c){
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
					rand_tile = rand_int(10);
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
		rand_x = max_int( rand_int(m->map_width - 2), 2);
		rand_y = max_int( rand_int(m->map_height - 2), 2);
		if(m->terrain[rand_y * m->map_width + rand_x] == m->floor){
			map_flood_fill(m, rand_x, rand_y, 'o');
			break;
		}
	}
	for(int i = 0; i < m->map_height; i++){ /* fill in unwanted parts of the map */
		for(int j = 0; j < m->map_width; j++){
			if(m->terrain[ i * m->map_width + j ] == m->floor) m->terrain[ i * m->map_width + j ] = m->wall;
			if(m->terrain[ i * m->map_width + j ] == 'o') m->terrain[ i * m->map_width + j ] = m->floor;
		}
	}
	map_gen_entrance_and_exit(m);
	map_gen_add_components(m, c);
}

void map_gen_entrance_and_exit(MapData *m){
int entrance_x, entrance_y;
	int exit_x, exit_y;
	while(1){
		entrance_x = max_int( rand_int(m->map_width - 2), 2); /* randomly place an entrance and an exit */
		entrance_y = max_int( rand_int(m->map_height - 2), 2);
		exit_x = max_int( rand_int(m->map_width - 2), 2);
		exit_y = max_int( rand_int(m->map_height - 2), 2);
		if(m->terrain[entrance_y * m->map_width + entrance_x] == m->floor && m->terrain[exit_y * m->map_width + exit_x] == m->floor){ /* check if the entrance and exit are on floor tiles */
			if( path_get_manhattan_distance(entrance_x, entrance_y, exit_x, exit_y) > 2 ){ /* ensure that the entrance and exit arent right next to each other. */
				m->terrain[(exit_y * m->map_width) + exit_x] = m->exit;
				m->terrain[(entrance_y * m->map_width) + entrance_x] = m->entrance;
				break; /* end while loop */
			}
		}
	}
}

void map_gen_add_components(MapData *m, Component *c){
	for(int i = 0; i < m->map_height; i++){
		for(int j = 0; j < m->map_width; j++){
			component_add_position(c, j, i);
			component_add_draw(c, 0, 1, m->terrain[i * m->map_width + j]);
			c->next_id++;
		}
	}
}


/*--------------------- Fill an area with a given symbol/tile. --------------------------------------------------------------*/
void map_flood_fill(MapData *m, int rand_x, int rand_y, char symbol){

	int current_index = 0;
	int number_of_nodes = 1;
	int list_size = path_count_floor(m);
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

void map_shadow_cast_cell_list_init(Cell cell_list[], int size_cell_list){
	for(int i = 0; i < size_cell_list; i++){
		for(int j = 0; j < 4; j++){
			cell_list[i].edge_id[j] = -1;
			cell_list[i].edge_exist[j] = 0;
		}
	}
}

void map_shadow_cast_edge_list_init(Edge edge_list[], int size_edge_list){
	for(int i = 0; i < size_edge_list; i++){
		edge_list[i].x1 = -1;
		edge_list[i].y1 = -1;
		edge_list[i].x2 = -1;
		edge_list[i].y2 = -1;
	}
}

void map_shadow_cast_poly_list_init(VisPoly poly_list[], int size_poly_list){
	for(int i = 0; i < size_poly_list; i++){
		poly_list[i].angle = 0;
		poly_list[i].x = -1;
		poly_list[i].y = -1;
	}
}

int map_compare_angles (const void *a, const void *b){
	VisPoly *poly1 = (VisPoly *)a;
	VisPoly *poly2 = (VisPoly *)b;
	return ( poly1->angle - poly2->angle);
}


	// return the int pointer of the value of a - the int pointer of the value of b
/* ---------- Line-of-sight calculations ------------------------------------------------------------------------------------*/
void map_shadow_cast(MapData *m, int origin_x, int origin_y, int distance){
	int tile_width = 10; /* an arbitrary width given to tiles for better angle accuracy */
	int size_edge_list = m->map_width * m->map_height;
	int size_cell_list = m->map_width * m->map_height;
	int size_poly_list = m->map_width * m->map_height;
	int number_of_edges = 0;
	int current, north, east, south, west;
	Edge edge_list[size_edge_list];
	Cell cell_list[size_cell_list];
	VisPoly poly_list[size_poly_list];
	int number_of_polys = 0;
	map_shadow_cast_cell_list_init(cell_list, size_cell_list);
	map_shadow_cast_edge_list_init(edge_list, size_edge_list);
	map_shadow_cast_poly_list_init(poly_list, size_poly_list);

	for(int i = 1; i < m->map_height - 1; i++){
		for(int j = 1; j < m->map_width - 1; j++){

			current = i * m->map_width + j;
			north   = (i - 1) * m->map_width + j;
			east    = i * m->map_width + j + 1;
			south   = (i + 1) * m->map_width + j;
			west    = i * m->map_width + j - 1;

			if(m->terrain[current] == m->wall){

				if( m->terrain[north] != m->wall){
					if(cell_list[west].edge_exist[0] == 1){
						cell_list[current].edge_id[0] = cell_list[west].edge_id[0]; /* extend edge id from western neighbor. */
						edge_list[ cell_list[current].edge_id[0] ].x2 = j; /* extend edge coords in edge_list */
						edge_list[ cell_list[current].edge_id[0] ].y2 = i;
					}
					else{ /* no wall to west, create new edge. */
						cell_list[current].edge_id[0] = number_of_edges;
						edge_list[number_of_edges].x1 = j;
						edge_list[number_of_edges].y1 = i;
						edge_list[number_of_edges].x2 = j;
						edge_list[number_of_edges].y2 = i;
						number_of_edges++;
					}
				}

				if( m->terrain[east] != m->wall){
					if(cell_list[north].edge_exist[1] == 1){
						cell_list[current].edge_id[1] = cell_list[north].edge_id[1]; /* extend edge id from northern neighbor. */
						edge_list[ cell_list[current].edge_id[1] ].x2 = j; /* extend edge coords in edge_list */
						edge_list[ cell_list[current].edge_id[1] ].y2 = i;
					}
					else{ /* no wall to north, create new edge. */
						cell_list[current].edge_id[1] = number_of_edges;
						edge_list[number_of_edges].x1 = j;
						edge_list[number_of_edges].y1 = i;
						edge_list[number_of_edges].x2 = j;
						edge_list[number_of_edges].y2 = i;
						number_of_edges++;
					}
				}

				if( m->terrain[south] != m->wall){
					if( cell_list[west].edge_exist[2] == 1){
						cell_list[current].edge_id[2] = cell_list[west].edge_id[2]; /* extend edge id from western neighbor. */
						edge_list[ cell_list[current].edge_id[2] ].x2 = j; /* extend edge coords in edge_list */
						edge_list[ cell_list[current].edge_id[2] ].y2 = i;
					}
					else{ /* no wall to west, create new edge. */
						cell_list[current].edge_id[2] = number_of_edges;
						edge_list[number_of_edges].x1 = j;
						edge_list[number_of_edges].y1 = i;
						edge_list[number_of_edges].x2 = j;
						edge_list[number_of_edges].y2 = i;
						number_of_edges++;
					}
				}
				if( m->terrain[east] != m->wall){
					if(cell_list[north].edge_exist[3] == 1){
						cell_list[current].edge_id[3] = cell_list[north].edge_id[3]; /* extend edge id from northern neighbor. */
						edge_list[ cell_list[current].edge_id[3] ].x2 = j; /* extend edge coords in edge_list */
						edge_list[ cell_list[current].edge_id[3] ].y2 = i;
					}
					else{ /* no wall to west, create new edge. */
						cell_list[current].edge_id[3] = number_of_edges;
						edge_list[number_of_edges].x1 = j;
						edge_list[number_of_edges].y1 = i;
						edge_list[number_of_edges].x2 = j;
						edge_list[number_of_edges].y2 = i;
						number_of_edges++;
					}
				}
			}
		}
	}


	for(int i = 0; i < number_of_edges; i++){ /* iterate edge_list */
		for(int j = 0; j < 2; j++){
			float rdx, rdy; /* ray vector */

			rdx = (j == 0 ? edge_list[i].x1 : edge_list[i].x2) - origin_x; /* start or end point */
			rdy = (j == 0 ? edge_list[i].y1 : edge_list[i].y2) - origin_y;

			float base_ang = atan2f(rdy, rdx); /* return angle of ray vector */
			float ang = 0; /* angle of shot ray */

			for(int k = 0; k < 3; k++){ /* create 3 rays: one that hits an edge end-point, and 2 that over-shoot it very slightly. */
				if(k == 0) ang = base_ang - 0.0001f;
				if(k == 1) ang = base_ang;
				if(k == 2) ang = base_ang + 0.0001f;

				rdx = distance * cosf(ang); /* shoot ray specified distance. */
				rdy = distance * sinf(ang);

				float min_t1 = INFINITY;
				float min_px = 0, min_py = 0, min_ang = 0;

				/* check ray intersections with edges */
				for(int n = 0; n < size_edge_list; n++){
					/* create line segment vector to represent the edge from start to end */
					float edx = edge_list[n].x2 - edge_list[i].x1;
					float edy = edge_list[n].y2 - edge_list[i].y1;

					if (fabs(edx - rdx) > 0.0f && fabs(edy - rdy) > 0.0f){
						/* use line segment intersect point line algorithm */
						/* t2 is normalized distance from line segment start to line segment end of intersect point. */
						float t2 = (rdx * (edge_list[n].y1 - origin_y) + (rdy * (origin_x - edge_list[n].x1))) / (edx * rdy - edy * rdx);
						/* t1 is normalized distance from source along ray to ray lenge of intersect point. */
						float t1 = (edge_list[n].x1 + edx * t2 - origin_x) / rdx;

						/* if intersect point exists along ray and edge line segment, then intersect point is valid. */
						if(t1 > 0 && t2 >= 0 && t2 <= 1.0f){
							/* if this point is closest to origin, store it and reject the others */
							if(t1 < min_t1){
								min_t1 = t1;
								min_px = origin_x + rdx * t1;
								min_py = origin_y + rdy * t1;
								min_ang = atan2f(min_py - origin_y, min_px - origin_x);
							}
						}
					}
				}
				/* add intersection point to poly_list. */
				poly_list[number_of_polys].angle = min_ang;
				poly_list[number_of_polys].x = min_px;
				poly_list[number_of_polys].y = min_py;
				number_of_polys++;
			}
		}
	}
	qsort(poly_list,number_of_polys, sizeof(VisPoly), map_compare_angles); /* sort rays by angle */
}
