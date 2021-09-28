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
	map_gen_fill(m);
}

/*---------------------- Deallocate map data ---------------------------------------------------------------------------------*/
void map_free(MapData *m){
	free(m->map);
	m->map = NULL;
	free(m);
	m = NULL;
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
		m->map[ (halls_array[hall_index].y * m->map_width) + j ] = '.';
	}
}

/*------ "Carve" a verticle hallway int the map array ------------------------------------------------------------------------*/
void map_gen_carve_hall_vertically(MapData *m, Hall *halls_array, int hall_index, int ystart, int yend){
	for(int j = ystart; j <= yend; j++){
		m->map[ (j * m->map_width) + halls_array[hall_index].x2 ] = '.';
	}
}

/*---------------------- Carve rooms -----------------------------------------------------------------------------------------*/
void map_gen_carve_room(MapData *m, Room *rooms, int rooms_added){
	/* "Carve" rooms into the map array */
	for(int i = 0; i < rooms_added; i++){
		for(int j = rooms[i].y; j < rooms[i].y2; j++){
			for(int k = rooms[i].x; k < rooms[i].x2; k++){
				m->map[ j * m->map_width + k ] = m->floor;
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
			m->map[ i * m->map_width + j] = m->wall;
		}
	}
}

/*---------------------- Generate doors on the edges of each room ------------------------------------------------------------*/
void map_gen_doors(MapData *m, Room *rooms, int number_of_rooms){
	char top, bottom, left, right;
	/* y coord */
	for(int i = 1; i < (m->map_height-1); i++){
		/* x coord */
		for(int j = 1; j < (m->map_width-1); j++){
			/* surrounding tiles */
			top = m->map[(i - 1) * m->map_width + j];
			bottom = m->map[(i + 1) * m->map_width + j];
			left = m->map[ i * m->map_width + j - 1];
			right = m->map[i * m->map_width + j + 1];
			/* check surrounding area of each floor tile  */
			if( m->map[i * m->map_width + j] == m->floor){
				/* horizontal doors */
				if( top == m->floor && bottom ==  m->floor && left == m->wall && right == m->wall){
					for(int k = 0; k < number_of_rooms; k++){
						if(rooms[k].x <= j && rooms[k].x2 >= j && (rooms[k].y == i + 1 || rooms[k].y2 == i)){
							m->map[i * m->map_width + j] = m->door_horizontal_closed;
						}
					}
				}
				/* vertical doors */
				else if( top == m->wall && bottom == m->wall && left == m->floor && right == m->floor){
					for(int k = 0; k < number_of_rooms; k++){
						if((rooms[k].x == j + 1 || rooms[k].x2 == j) && rooms[k].y <= i && rooms[k].y2 >= i){
							m->map[i * m->map_width + j] = m->door_vertical_closed;
						}
					}
				}
			}
		}
	}
}

/*---------------------- Map Generation: Simple Room Placement ---------------------------------------------------------------*/
/* Rooms are added one at a time wherever they will fit, then hallways are created between them. */
void map_gen_srp(MapData *m){
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
	map_gen_carve_hallways(m, rooms, rooms_added);
	map_gen_doors(m, rooms, rooms_added);
}

/*---------------------- Map Generation: Cellular Automata -------------------------------------------------------------------*/
void map_gen_ca(MapData *m){
	int iterations = 4;
	int rand_tile;
	int neighbor_walls;
	char map_copy[m->map_width * m->map_height];

	/* generate random noise (wall and floor tiles) on the map copy */
	for(int i = 0; i < m->map_height; i++){
		for(int j = 0; j < m->map_width; j++){
			/* everything  is random - wall or floor */
			rand_tile = rand_int(10);
			if(rand_tile > 4) map_copy[ i * m->map_width + j ] = m->floor;
			else map_copy[ i * m->map_width + j ] = m->wall;
		}
	}
	int n = 0;
	while(n < iterations){
		for(int i = 1; i < m->map_height - 1; i++){
			for(int j = 1; j < m->map_width - 1; j++){
				neighbor_walls = 0;
				if( map_copy[ i * m->map_width + j - 1 ] == m->wall ) neighbor_walls++; /* left */
				if( map_copy[ i * m->map_width + j + 1 ] == m->wall ) neighbor_walls++; /* right */
				if( map_copy[ (i - 1) * m->map_width + j ] == m->wall ) neighbor_walls++; /* top */
				if( map_copy[ (i + 1) * m->map_width + j ] == m->wall ) neighbor_walls++; /* bottom */
				if( map_copy[ (i - 1) * m->map_width + j - 1 ] == m->wall ) neighbor_walls++; /* top-left */
				if( map_copy[ (i - 1) * m->map_width + j + 1 ] == m->wall ) neighbor_walls++; /* top-right */
				if( map_copy[ (i + 1) * m->map_width + j + 1 ] == m->wall ) neighbor_walls++; /* bottom-right */
				if( map_copy[ (i + 1) * m->map_width + j - 1 ] == m->wall ) neighbor_walls++; /* bottom-left */

				/* if 4 neighbor walls and current tile is a wall,  stay a wall */
				if( map_copy[ i * m->map_width + j ] == m->wall && neighbor_walls >= 4) m->map[ i * m->map_width + j] = m->wall;
				else if( map_copy[ i * m->map_width + j ] == m->floor && neighbor_walls >= 5) m->map[ i * m->map_width + j] = m->wall;
				else  m->map[ i * m->map_width + j] = m->floor;
			}
		}
		memcpy(map_copy, m->map, m->map_width * m->map_height);
		n++;
	}

	n = 0;
	int p = 0;
	int entrance;
	int exit;

	while(p == 0){
		entrance = rand_int(m->map_width * m->map_height);
		exit = rand_int(m->map_width * m->map_height);
		if(map_copy[entrance] == m->floor && map_copy[exit] == m->floor) p = 1;
	}

}

int map_path_get_manhattan_distance(int x1, int y1, int x2, int y2){
	return abs(x1 - x2) + abs(y1 - y2);
}

int map_count_floor(MapData *m){
	int count = 0;
	for(int i = 0; i < m->map_height; i++){
		for(int j = 0; j < m->map_width; j++){
			if(m->map[ (i * m->map_width) + j] == m->floor){
				count++;
			}
		}
	}
	return count;
}

/*====================== Pathfindinding ======================================================================================*/

/*---------------------- Initialize the open_list array ----------------------------------------------------------------------*/
void map_path_init_lists(MapData *m, MapGraph *g){
	for ( int n = 0; n < g->number_of_nodes; n++){
		for( int i = 0; i < m->map_height; i++){
			for( int j = 0; j < m->map_width; j++){
				if(m->map[ (i * m->map_width) * j] == m->floor){
					g->open_list[n].parent_index = -1; /* -1 is impossible */
					g->open_list[n].x = j;
					g->open_list[n].y = i;
					g->open_list[n].g = INT_MAX; /* initial value should be infinity, but the integer max will suffice */
					g->open_list[n].h = INT_MAX;
					g->open_list[n].f = INT_MAX;
					g->closed_list[n].parent_index = -1;
					g->closed_list[n].x = j;
					g->closed_list[n].y = i;
					g->closed_list[n].g = INT_MAX;
					g->closed_list[n].h = INT_MAX;
					g->closed_list[n].f = INT_MAX;
					for(int k = 0; k < 4; k++){
						g->open_list[n].neighbor_index[k] = -1;
						g->closed_list[n].neighbor_index[k] = -1;
					}
				}
			}
		}
	}
}

/*---------------------- Record neighbor information  ------------------------------------------------------------------------*/
void map_path_node_get_neighbors(MapData *m, MapGraph *g, int node_index){
	int nx = g->open_list[node_index].x;
	int ny = g->open_list[node_index].y;
	int north = (ny - 1) * m->map_width + nx;
	int south = (ny + 1) * m->map_width + nx;
	int east = ny * m->map_width + nx + 1;
	int west = ny * m->map_width + nx - 1;
	g->open_list[node_index].number_of_neighbors = 0; /* initialize number_of_neighbors value */

	/* check the map for neighboring nodes */
	if( m->map[north] == m->floor ){ /* North */
		g->open_list[node_index].neighbor_index[0] = g->number_of_open_nodes; /* add neighbor index to current node */
		g->open_list[node_index].number_of_neighbors++; /* iterate node neigbor count */
		/* if this neigbor doesn't exist in any of the lists, add it to open_list */
		if(map_path_node_exists_in_lists(g, nx, ny-1) == false) map_path_open_list_add_node(g, node_index, nx, ny - 1);
	}
	if( m->map[south] == m->floor ){ /* South */
		g->open_list[node_index].neighbor_index[1] = g->number_of_open_nodes; /* add neighbor index to current node */
		g->open_list[node_index].number_of_neighbors++;
		/* if this neigbor doesn't exist in any of the lists, add it to open_list */
		if( map_path_node_exists_in_lists(g, nx, ny+1) == false ) map_path_open_list_add_node(g, node_index, nx, ny + 1);
	}
	if( m->map[east] == m->floor ){ /* East */
		g->open_list[node_index].neighbor_index[2] = g->number_of_open_nodes; /* add neighbor index to current node */
		g->open_list[node_index].number_of_neighbors++;
		/* if this neigbor doesn't exist in any of the lists, add it to open_list */
		if(map_path_node_exists_in_lists(g, nx + 1, ny) == false ) map_path_open_list_add_node(g, node_index, nx + 1, ny);
	}
	if( m->map[west] == m->floor ){ /* West */
		g->open_list[node_index].neighbor_index[3] = g->number_of_open_nodes; /* add neighbor index to current node */
		g->open_list[node_index].number_of_neighbors++;
		/* if this neigbor doesn't exist in any of the lists, add it to open_list */
		if(map_path_node_exists_in_lists(g, nx - 1, ny) == false ) map_path_open_list_add_node(g, node_index, nx - 1, ny);
	}
}

/*---------------------- Add new node to open_list ---------------------------------------------------------------------------*/
void map_path_open_list_add_node(MapGraph *g, int parent_index, int x, int y){
	int i = g->number_of_open_nodes;
	g->open_list[i].x = x;
	g->open_list[i].y = y;
	/* g value = distance between this node and parent + parent g value. */
	g->open_list[i].g = map_path_get_manhattan_distance(x, y, g->open_list[parent_index].x, g->open_list[parent_index].y) + g->open_list[parent_index].g;
	g->open_list[i].h = map_path_get_manhattan_distance(x, y, g->endx, g->endy);
	/* if f is less than the existing f value, then update */
	if( (g->open_list[i].g + g->open_list[i].h) < g->open_list[i].f){
		g->open_list[i].parent_index = parent_index;
		g->open_list[i].f = g->open_list[i].g + g->open_list[i].h;
	}
	g->number_of_open_nodes++; /* iterate open_node count */
}

/*---------------------- "Clear" open_list node by giving it values that won't be prioritized --------------------------------*/
void map_path_open_list_clear_node(MapGraph *g, int node_index){
	g->open_list[node_index].x = -1; /* this might get me in trouble */
	g->open_list[node_index].y = -1; /* this also might get me in trouble */
	g->open_list[node_index].g = INT_MAX;
	g->open_list[node_index].h = INT_MAX;
	g->open_list[node_index].f = INT_MAX;
}

/*---------------------- Copy contents of indicated open_list node into closed_list ------------------------------------------*/
void map_path_closed_list_add_node(MapGraph *g, int open_list_index){
	/* I could use memcpy, but I hate surprises. */
	g->closed_list[g->number_of_closed_nodes].x = g->open_list[open_list_index].x;
	g->closed_list[g->number_of_closed_nodes].y = g->open_list[open_list_index].y;
	g->closed_list[g->number_of_closed_nodes].g = g->open_list[open_list_index].g;
	g->closed_list[g->number_of_closed_nodes].h = g->open_list[open_list_index].h;
	g->closed_list[g->number_of_closed_nodes].f = g->open_list[open_list_index].f;
	g->closed_list[g->number_of_closed_nodes].parent_index = g->open_list[open_list_index].parent_index;
	map_path_open_list_clear_node(g, open_list_index);
}

/*---------------------- Get the open_list[] index via map coords ------------------------------------------------------------*/
int map_path_open_list_get_index(MapGraph *g, int x, int y){
	int index;
	for( int i = 0; i < g->number_of_open_nodes; i++){
		if (g->open_list[i].x == x && g->open_list[i].y == y){
			index = i;
			break;
		}
	}
	return index;
}

/*---------------------- Get the closed_list[] index via map coords ----------------------------------------------------------*/
int map_path_closed_list_get_index(MapGraph *g, int x, int y){
	int index;
	for( int i = 0; i < g->number_of_closed_nodes; i++){
		if (g->closed_list[i].x == x && g->closed_list[i].y == y){
			index = i;
			break;
		}
	}
	return index;
}

/*---------------------- Deallocate MapGraph memory --------------------------------------------------------------------------*/
void map_path_free_graph(MapGraph *g){
	free(g->open_list);
	free(g->closed_list);
	free(g);
}

/*---------------------- Check to see if the given criteria are matched by a node in any list  -------------------------------*/
bool map_path_node_exists_in_lists(MapGraph *g, int x, int y){
	bool exists = false;
	/* checked open_list */
	for(int i = 0; i < g->number_of_open_nodes; i++){
		if( g->open_list[i].x == x && g->open_list[i].y == y){
			exists = true;
			break;
		}
	}
	if(exists == 0){
		/* check closed_list */
		for(int i = 0; i < g->number_of_closed_nodes; i++){
			if( g->closed_list[i].x == x && g->closed_list[i].y == y){
				exists = true;
				break;
			}
		}
	}
	return exists;
}

/*
typedef struct {
	int number_of_nodes;
	int startx,starty;
	int endx, endy;
	int number_of_open_nodes;
	int number_of_closed_nodes;
	MapNode *open_list;
	MapNode *closed_list;
}MapGraph;


typedef struct {
	int x,y;
	int f,g,h;
	int parent_index;
	int number_of_neighbors;
	int neighbor_index[4];
}MapNode;
*/

/*---------------------- Check to see if it is possible to go from point a to b ----------------------------------------------*/
bool map_path_is_contiguous(MapData *m, int ax, int ay, int bx, int by){
	bool contiguous = true;
	MapGraph *g = malloc( sizeof (*g) );
	g->number_of_nodes = map_count_floor(m);
	g->number_of_open_nodes = 0;
	g->number_of_closed_nodes = 0;
	g->open_list = malloc( sizeof (*(g->open_list)) * g->number_of_nodes );
	g->closed_list = malloc( sizeof (*(g->open_list)) * g->number_of_nodes );
	g->startx = ax;
	g->starty = ay;
	g->endx = bx;
	g->endy = by;

	/* add the starting node to open_list */
	g->open_list[0].x = ax;
	g->open_list[0].y = ay;
	g->open_list[0].parent_index = 0;
	g->open_list[0].h = map_path_get_manhattan_distance(ax, ay, bx, by);
	g->open_list[0].f = g->open_list[0].h;
	g->number_of_open_nodes = 1;
	int current_index = 0;

	/* The main loop */
	while(g->open_list[current_index].x != bx && g->open_list[current_index].y != by){ /* "while the current node is not the final node " */
		/*get current node's neighbors and calculate their h and g values */
		map_path_node_get_neighbors(m, g, current_index);
		map_path_closed_list_add_node(g, current_index);
	}
	return contiguous;
}
