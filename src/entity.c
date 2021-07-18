//entity.c
//by burlapjack 2021
#include "../include/component.h"
#include "../include/entity.h"

void entity_add_position_component(Entities *e,int id, int x,int y){
	e->position[1].x = x;
	e->position[1].y = y;
		
}

void entity_add_draw_component(Entities *e, int id, int xoff, int yoff,int col,char sym){
	e->draw[1].xoffset = xoff;
	e->draw[1].yoffset = xoff;
	e->draw[1].color = col;
	e->draw[1].symbol = sym;
		
}

void entity_add_stats_component(Entities *e, int id, int hp, int str, int per, int agi){
	e->stats[1].id = id;
	e->stats[1].hp = hp;
	e->stats[1].strength = str;
	e->stats[1].perception = per;
	e->stats[1].agility = agi;
}
