/* map.h by burlapjack 2021
 * 
 */

#ifndef MAP_H
#define MAP_H

#include "component.h"

typedef struct{
	int map_width;
	int map_height;
	int number_of_rooms;
	int room_max_width;
	int room_max_height;
	int room_min_width;
	int room_min_height;	
	int room_padding;
	char door_horizontal_closed;
	char door_horizontal_open;
	char door_vertical_closed;
	char door_vertical_open;
	char entrance;
	char exit;	
	char floor;	
	char hallway;
	char wall;

	int color_entrance;
	int color_exit;
	int color_door_horizontal;
	int color_door_vertical;
	int color_floor;
	int color_wall;	

	char *map;

}MapData;

typedef struct{
	int x,y,x2,y2;
}Room;

typedef struct{
	int x,y,x2,y2;
}Hall;

struct node {
	int x,y;
	float f; // g + h
	float g; // distance taken so far
	float h; // distance to end node
	struct Node *neighbor[4];
	struct Node *parent;
};
typedef struct node Node;


void map_init(MapData *m, int map_width, int map_height);
void map_free(MapData *m);

bool map_a_to_b_possible(MapData *m, int a, int b);
void map_carve_hallways(MapData *m, Room *rooms, int rooms_added);
void map_carve_hall_horizontally(MapData *m, Hall *halls_array, int hall_index, int xstart, int xend);
void map_carve_hall_vertically(MapData *m, Hall *halls_array, int hall_index, int ystart, int yend);
void map_carve_room(MapData *m, Room *rooms, int rooms_added);
void map_fill(MapData *m);
float  map_get_distance(MapData *m, int ax, int ay, int bx, int by);
void map_generate_doors(MapData *m, Room *rooms, int number_of_rooms);
void map_generate_srp(MapData *m);
void map_generate_ca(MapData *m);
int map_xy(int x, int y, int map_width);
double max_double(double a, double b);
double min_double(double a, double  b);
int max_int(int a, int b);
int min_int(int a, int b);
int rand_int(int n);


#endif /* MAP_H */
