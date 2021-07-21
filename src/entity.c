//entity.c
//by burlapjack 2021

#include <stdlib.h>
#include "../include/component.h"
#include "../include/entity.h"


void entity_list_expand_position(ComponentPosition *l, int list_size_original, int list_size_final){
	if (list_size_original == 0) {
		l = malloc(sizeof (*l) * list_size_final);
	}

	for(int i = list_size_original; i < list_size_final-1; ++i){
		l[i].id = 0;
	}	
}

void entity_list_expand_draw(ComponentDraw *l, int list_size_original, int list_size_final){
	if (list_size_original == 0) {
		l = (ComponentDraw*) calloc(list_size_final,sizeof (ComponentDraw));
	}

	for(int i = list_size_original; i < list_size_final-1; ++i){
		l[i].id = 0;
	}	
}

void entity_list_expand_stats(ComponentStats *l, int list_size_original, int list_size_final){
	if (list_size_original == 0) {
		l = malloc(sizeof (*l) * list_size_final);
	}

	for(int i = list_size_original; i < list_size_final-1; ++i){
		l[i].id = 0;
	}	
}


void entity_add_component_position(ComponentPosition p[],int list_size, unsigned int id, int x, int y){
		p->id = id;	
		p->x = x;
		p->y = y;
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
