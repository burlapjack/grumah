// component.h
// declares component types
// by burlapjack 2021

#ifndef COMPONENT_H
#define COMPONENT_H

typedef struct{
	unsigned int id;
	unsigned int x,y;
}ComponentPosition;

typedef struct{
	unsigned int id;
	char symbol;
	unsigned int color;
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

typedef struct{
	unsigned int id;
	unsigned int durability;
}ComponentWall;

typedef struct {
	unsigned int id;
	unsigned int key_pushed;
}ComponentInput;

typedef struct {
	ComponentPosition *position;
	ComponentDraw *draw;
	ComponentStats *stats;
	ComponentMenuOption *menu_option;
	ComponentTrigger *trigger;
	unsigned int size_position;
	unsigned int size_draw;
	unsigned int size_stats;
	unsigned int size_menu_option;
	unsigned int size_trigger;
}Component;


/*----------- Init Component Lists ----------------------------*/
ComponentDraw* component_init_draw(ComponentDraw **c, unsigned int size_list);
ComponentMenuOption* component_init_menu_option(ComponentMenuOption **c, unsigned int size_list);
ComponentPosition* component_init_position(ComponentPosition **c,unsigned int size_list);
ComponentStats* component_init_stats(ComponentStats **c, unsigned int size_list);
ComponentTrigger* component_init_trigger(ComponentTrigger **c, unsigned int size_list);

void component_list_init_all(unsigned int list_size, ComponentPosition **cp, ComponentDraw **cd, ComponentStats **cs, ComponentMenuOption **co);

Component* component_init(Component *c, unsigned int size_lists);

/*----------- Deallocate Component List Memory ----------------*/
void component_list_free_all(ComponentPosition *cp, ComponentDraw *cd, ComponentStats *cs, ComponentMenuOption *co);

void component_free_all(Component *c);

/*----------- Component List Manipulation ---------------------*/
void component_list_size_double_draw(ComponentDraw** component_list, unsigned int *list_size);
void component_list_size_double_menu_option(ComponentMenuOption** component_list, unsigned int *list_size);
void component_list_size_double_position(ComponentPosition** component_list, unsigned int *list_size);
void component_list_size_double_stats(ComponentStats** component_list, unsigned int *list_size);
void component_list_size_double_trigger(ComponentTrigger** component_list, unsigned int *list_size);

void component_list_double_draw(Component *c);
void component_list_double_menu_option(Component *c);
void component_list_double_position(Component *c);
void component_list_double_stats(Component *c);
void component_list_double_trigger(Component *c);

/*----------- Component Additions -----------------------------*/
void component_list_add_draw(ComponentDraw **component_list, unsigned int *list_size, unsigned int id, unsigned int color, char symbol);
void component_list_add_menu_option(ComponentMenuOption **component_list, unsigned int *list_size, unsigned int id, char name[32], unsigned int game_state, unsigned int highlighted);
void component_list_add_position(ComponentPosition **component_list, unsigned int *list_size, unsigned int id, unsigned int x, unsigned int y);
void component_list_add_stats(ComponentStats **component_list, unsigned int *list_size, unsigned int id, unsigned int hp, unsigned int str, unsigned int per, unsigned int agi);
void component_list_add_trigger(ComponentTrigger**component_list, unsigned int *list_size, unsigned int id, unsigned int game_state);


void component_add_draw(Component *c, unsigned int id, unsigned int color, char symbol);
void component_add_position(Component *c, unsigned int id, unsigned int x, unsigned int y);
void component_add_menu_option(Component *c, unsigned int id, char name[32], unsigned int game_state, unsigned int highlighted);
void component_add_stats(Component *c, unsigned int id, unsigned int hp, unsigned int str, unsigned int per, unsigned int agi);
void component_add_trigger(Component *c, unsigned int id, unsigned int game_state);


#endif /*COMPONENT_H*/
