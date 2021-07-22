//entity.h
//by burlapjack 2021


#ifndef ENTITY_H
#define ENTITY_H

/*------------Component creation -----------*/
 
void entity_add_component_position(ComponentPosition *c, int list_size, unsigned int *id, int x, int y);
void entity_add_component_draw(ComponentDraw *c, int list_size, unsigned int *id, int xoffset, int yoffset, int color, char symbol);
void entity_add_component_stats(ComponentStats *c, int list_size, unsigned int *id, int hp, int str, int per, int agi);

#endif /*ENTITY_H*/
