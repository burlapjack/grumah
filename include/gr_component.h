// component.h
// declares component types
// by burlapjack 2021
//

#ifndef COMPONENT_H
#define COMPONENT_H

/*----------- Component Types ------------------------------------------------------------------------------------------------*/
typedef struct{
	int id;
	int strength;
	int perception;
	int agility;
}ComponentAttributes;

typedef struct{
	int id;
	int x;
	int y;
	int layer;
	char symbol;
	int visibility;
	int color;
}ComponentDraw;

typedef struct{
	int id;
	int max;
	int current;
}ComponentHitPoints;

typedef struct {
	int id;
	int requested;
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
	int game_state;
}ComponentTrigger;

/*----------- Component Container --------------------------------------------------------------------------------------------*/
typedef struct {
	ComponentAttributes *attributes;
	ComponentDraw *draw;
	ComponentHitPoints *hit_points;
	ComponentInput *input;
	ComponentSize *size;
	ComponentTrigger *trigger;
	int next_id;
	int size_draw;
	int size_hit_points;
	int size_input;
	int size_size;
	int size_attributes;
	int size_trigger;
}Component;

extern void gr_component_init(Component *c, int size_lists);

/*----------- Deallocate Component List Memory -------------------------------------------------------------------------------*/
extern void gr_component_free(Component *c);

/*----------- Component List Size-Doubling -----------------------------------------------------------------------------------*/
extern void gr_component_list_double_attributes(Component *c);
extern void gr_component_list_double_draw(Component *c);
extern void gr_component_list_double_hitpoints(Component *c);
extern void gr_component_list_double_input(Component *c);
extern void gr_component_list_double_size(Component *c);
extern void gr_component_list_double_trigger(Component *c);

/*----------- Component Container Additions ----------------------------------------------------------------------------------*/
extern void gr_component_add_attributes(Component *c, int str, int per, int agi);
extern void gr_component_add_draw(Component *c, int x, int y, int layer, int color, char symbol);
extern void gr_component_add_hitpoints(Component *c, int value);
extern void gr_component_add_input(Component *c);
extern void gr_component_add_size(Component *c, int width, int height);
extern void gr_component_add_trigger(Component *c, int game_state);

/*----------- Clear components from component arrays without deallocation ----------------------------------------------------*/
extern void gr_component_clear_all_attributes(Component *c);
extern void gr_component_clear_all_draw(Component *c);
extern void gr_component_clear_all_hitpoints(Component *c);
extern void gr_component_clear_all_input(Component *c);
extern void gr_component_clear_all_size(Component *c);
extern void gr_component_clear_all_trigger(Component *c);

extern void gr_component_clear_all(Component *c);

/*----------- Component container free memory --------------------------------------------------------------------------------*/
extern void gr_component_free__all(Component *c);

/*----------- Component Queries ----------------------------------------------------------------------------------------------*/
extern int gr_component_count_attributes(Component *c);
extern int gr_component_count_draw(Component *c);
extern int gr_component_count_hit_points(Component *c);
extern int gr_component_count_size(Component *c);
extern int gr_component_count_trigger(Component *c);
extern int gr_component_count_all(Component *c);


/*----------- Component Set Values -------------------------------------------------------------------------------------------*/
extern void gr_component_set_draw_layer(Component *c, int component_id, int draw_layer);
extern void gr_component_set_visibility(Component *c, int component_id, int visibility);

#endif /*COMPONENT_H*/
