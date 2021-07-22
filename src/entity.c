//entity.c
//by burlapjack 2021

#include <stdlib.h>
#include "../include/component.h"
#include "../include/entity.h"


void entity_add_component_position(ComponentPosition p[],int list_size, unsigned int id, int x, int y){

	for(int i = 0; i < list_size; ++i){
		if (p[i].id == 0){
			p[i].id = id;	
			p[i].x = x;
			p[i].y = y;
			break;
		}
	}
}

void entity_add_component_draw(ComponentDraw d[], int list_size, unsigned int id, int xoff, int yoff, int col, char sym){
	d->id = id;
	d->xoffset = xoff;
	d->yoffset = yoff;
	d->color = col;
	d->symbol = sym;
}

void entity_add_component_stats(ComponentStats s[], int list_size, unsigned int id, int hp, int str, int per, int agi){
	s->id = id;
	s->hp = hp;
	s->strength = str;
	s->perception = per;
	s->agility = agi;
}
