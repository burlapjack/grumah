//entity.h
//by burlapjack 2021


#ifndef ENTITY_H
#define ENTITY_H

typedef struct {
	int n_position, n_draw, n_stats;
	ComponentPosition *list_position;	
	ComponentDraw *list_draw;
	ComponentStats *list_stats;	
} Entity;


void entity_list_expand_position(ComponentPosition l[], int list_size_original, int list_size_final);
void entity_list_expand_draw(ComponentDraw l[], int list_size_original, int list_size_final);
void entity_list_expand_stats(ComponentStats l[], int list_size_original, int list_size_final);


void entity_add_component_position(ComponentPosition *p, int list_size, unsigned int id, int x, int y);
void entity_add_component_draw(ComponentDraw *d, int list_size, unsigned int id, int xoff, int yoff, int col, char sym);
void entity_add_component_stats(ComponentStats *s, int list_size, unsigned int id, int hp, int str, int per, int agi);

#endif /*ENTITY_H*/
