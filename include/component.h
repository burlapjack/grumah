// component.h
// declares component types
// by burlapjack 2021

#ifndef COMPONENT_H
#define COMPONENT_H

/*----------- Component Types --------------------------------*/
typedef struct {
	unsigned int id;
	int key_pressed;
}ComponentInput;

typedef struct{
	unsigned int id;
	int x;
	int y;
}ComponentPosition;

typedef struct{
	unsigned int id;
	int width;
	int height;
}ComponentSize;

typedef struct{
	unsigned int id;
	unsigned int layer;
	char symbol;
	int color;
}ComponentDraw;

typedef struct{
	unsigned int id;
	unsigned int hp;
	unsigned int strength;
	unsigned int perception;
	unsigned int agility;
}ComponentStats;

typedef struct{
	unsigned int id;
	unsigned int parent_id;
	char name[32];
	unsigned int highlighted;
}ComponentMenuOption;

typedef struct{
	unsigned int id;
	unsigned int game_state;
}ComponentTrigger;

/*----------- Component Container ----------------------------*/
typedef struct {
	ComponentInput *input;
	ComponentDraw *draw;
	ComponentMenuOption *menu_option;
	ComponentPosition *position;
	ComponentSize *size;
	ComponentStats *stats;
	ComponentTrigger *trigger;
	size_t size_draw;
	size_t size_input;
	size_t size_menu_option;
	size_t size_position;
	size_t size_size;
	size_t size_stats;
	size_t size_trigger;
}Component;

void component_init(Component *c, size_t size_lists);

/*----------- Deallocate Component List Memory ----------------*/
void component_free_all(Component *c);

/*----------- Component List Size-Doubling --------------------*/
void component_list_double_input(Component *c);
void component_list_double_draw(Component *c);
void component_list_double_menu_option(Component *c);
void component_list_double_position(Component *c);
void component_list_double_size(Component *c);
void component_list_double_stats(Component *c);
void component_list_double_trigger(Component *c);

/*----------- Component Container Additions -------------------*/
void component_add_input(Component *c, unsigned int id);
void component_add_draw(Component *c, unsigned int id, unsigned int layer, int color, char symbol);
void component_add_position(Component *c, unsigned int id, int x, int y);
void component_add_menu_option(Component *c, unsigned int id, char name[32], unsigned int parent_id, unsigned int highlighted);
void component_add_size(Component *c, unsigned int id, int width, int height);
void component_add_stats(Component *c, unsigned int id, unsigned int hp, unsigned int str, unsigned int per, unsigned int agi);
void component_add_trigger(Component *c, unsigned int id, unsigned int game_state);

/*----------- Component deletion without deallocation ---------*/
void component_delete_all_draw(Component *c);
void component_delete_all_input(Component *c);
void component_delete_all_menu_option(Component *c);
void component_delete_all_menu_position(Component *c);
void component_delete_all_size(Component *c);
void component_delete_all_stats(Component *c);
void component_delete_all_trigger(Component *c);

void component_delete_all(Component *c);

/*----------- Component container free memory -----------------*/
void component_free__all(Component *c);

/*----------- Component Queries -------------------------------*/
unsigned int component_count_draw(Component *c);
unsigned int component_count_menu_option(Component *c);
unsigned int component_count_position(Component *c);
unsigned int component_count_size(Component *c);
unsigned int component_count_stats(Component *c);
unsigned int component_count_trigger(Component *c);
unsigned int component_count_all(Component *c);

unsigned int component_count_invisible(Component *c);

/*----------- Component Set Values ----------------------------*/
void component_set_draw_layer(Component *c, unsigned int component_id, unsigned int draw_layer);

#endif /*COMPONENT_H*/
