//entity.h
//by burlapjack 2021


#ifndef ENTITY_H
#define ENTITY_H



void entity_list_expand_draw(ComponentDraw **l, size_t list_size_original, size_t list_size_final);


void entity_add_component_position(ComponentPosition *p, int list_size, unsigned int id, int x, int y);
void entity_add_component_draw(ComponentDraw *d, int list_size, unsigned int id, int xoff, int yoff, int col, char sym);
void entity_add_component_stats(ComponentStats *s, int list_size, unsigned int id, int hp, int str, int per, int agi);

#endif /*ENTITY_H*/
