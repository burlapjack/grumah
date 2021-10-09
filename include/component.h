// component.h
// declares component types
// by burlapjack 2021

#ifndef COMPONENT_H
#define COMPONENT_H

/*----------- Component Types --------------------------------------------------------------------*/
typedef struct{
	int id;
	int strength;
	int perception;
	int agility;
}ComponentAttributes;

typedef struct{
	int id;
	int max;
	int current;
}ComponentHitPoints;

typedef struct {
	int id;
	int key_pressed;
}ComponentInput;

typedef struct{
	int id;
	int x;
	int y;
}ComponentPosition;

typedef struct{
	int id;
	int width;
	int height;
}ComponentSize;

typedef struct{
	int id;
	int layer;
	char symbol;
	int visibility;
	int color;
}ComponentDraw;

typedef struct{
	int id;
	int parent_id;
	char name[32];
	int highlighted;
}ComponentMenuOption;

typedef struct{
	int id;
	int game_state;
}ComponentTrigger;

/*----------- Component Container -------------------------------------------------------------------*/
typedef struct {
	ComponentAttributes *attributes;
	ComponentDraw *draw;
	ComponentHitPoints *hit_points;
	ComponentInput *input;
	ComponentMenuOption *menu_option;
	ComponentPosition *position;
	ComponentSize *size;
	ComponentTrigger *trigger;
	int size_draw;
	int size_hit_points;
	int size_input;
	int size_menu_option;
	int size_position;
	int size_size;
	int size_attributes;
	int size_trigger;
}Component;

void component_init(Component *c, int size_lists);

/*----------- Deallocate Component List Memory ---------------------------------------------------*/
void component_free(Component *c);

/*----------- Component List Size-Doubling -------------------------------------------------------*/
void component_list_double_attributes(Component *c);
void component_list_double_draw(Component *c);
void component_list_double_hitpoints(Component *c);
void component_list_double_input(Component *c);
void component_list_double_menu_option(Component *c);
void component_list_double_position(Component *c);
void component_list_double_size(Component *c);
void component_list_double_trigger(Component *c);

/*----------- Component Container Additions ------------------------------------------------------*/
void component_add_attributes(Component *c, int id, int str, int per, int agi);
void component_add_draw(Component *c, int id, int layer, int color, char symbol);
void component_add_hitpoints(Component *c, int id, int value);
void component_add_input(Component *c, int id);
void component_add_position(Component *c, int id, int x, int y);
void component_add_menu_option(Component *c, int id, char name[32], int parent_id, int highlighted);
void component_add_size(Component *c, int id, int width, int height);
void component_add_trigger(Component *c, int id, int game_state);

/*----------- Clear components without deallocation ----------------------------------------------*/
void component_clear_all_attributes(Component *c);
void component_clear_all_draw(Component *c);
void component_clear_all_hitpoints(Component *c);
void component_clear_all_input(Component *c);
void component_clear_all_menu_option(Component *c);
void component_clear_all_menu_position(Component *c);
void component_clear_all_size(Component *c);
void component_clear_all_trigger(Component *c);

void component_clear_all(Component *c);

/*----------- Component container free memory ----------------------------------------------------*/
void component_free__all(Component *c);

/*----------- Component Queries ------------------------------------------------------------------*/
int component_count_attributes(Component *c);
int component_count_draw(Component *c);
int component_count_hit_points(Component *c);
int component_count_menu_option(Component *c);
int component_count_position(Component *c);
int component_count_size(Component *c);
int component_count_trigger(Component *c);
int component_count_all(Component *c);

int component_count_invisible(Component *c);

/*----------- Component Set Values ---------------------------------------------------------------*/
void component_set_draw_layer(Component *c, int component_id, int draw_layer);
void component_set_visibility(Component *c, int component_id, int visibility);

#endif /*COMPONENT_H*/
