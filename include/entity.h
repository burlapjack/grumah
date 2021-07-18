//entity.h
//by burlapjack 2021


#ifndef ENTITY_H
#define ENTITY_H


typedef struct{
	ComponentPosition position[100];
	ComponentDraw draw[100];
	ComponentStats stats[100];
}Entities;

void entity_add_position_component(Entities *e,int id, int x,int y);
void entity_add_draw_component(Entities *e, int id, int xoff, int yoff,int col,char sym);
void entity_add_stats_component(Entities *e, int id, int hp, int str, int per, int agi);
#endif /*ENTITY_H*/
