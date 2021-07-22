//entity.h
//by burlapjack 2021


#ifndef ENTITY_H
#define ENTITY_H



void entity_list_expand_draw(ComponentDraw **l, size_t list_size_original, size_t list_size_final);


void entity_add_component_position(ComponentPosition *c, int list_size, unsigned int id, int x, int y);
void entity_add_component_draw(ComponentDraw *c, int list_size, unsigned int id, int xoffset, int yoffset, int color, char symbol);
void entity_add_component_stats(ComponentStats *c, int list_size, unsigned int id, int hp, int str, int per, int agi);

#endif /*ENTITY_H*/
