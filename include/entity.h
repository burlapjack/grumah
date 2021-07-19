//entity.h
//by burlapjack 2021


#ifndef ENTITY_H
#define ENTITY_H

void entity_add_component_position(unsigned int id, ComponentPosition *c, int x,int y);
void entity_add_component_draw(unsigned int id, ComponentDraw *d, int xoff, int yoff,int col,char sym);
void entity_add_component_stats(unsigned int id, ComponentStats *s, int hp, int str, int per, int agi);

#endif /*ENTITY_H*/
