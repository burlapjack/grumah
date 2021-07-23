//entity.c
//defines entity-related functions
//by burlapjack 2021

#include <stdlib.h>
#include "../include/component.h"
#include "../include/entity.h"


void entity_list_size_double(ComponentPosition** entity, size_t *list_size){
	*entity = realloc(*entity, sizeof (**entity) * (*list_size * 2));	
	for(int i = (*list_size-1); i < (*list_size * 2 - 1); ++i ){
		(*entity)[i].id = 0;	
	}
	*list_size = *list_size * 2;
};



void entity_add_component_position(ComponentPosition c[],int list_size, unsigned int id, int x, int y){

	for(int i = 0; i < list_size-1; ++i){
		if (c[i].id == 0){
			c[i].id = id;	
			c[i].x = x;
			c[i].y = y;
			break;
		}
	}
}

void entity_add_component_draw(ComponentDraw c[], int list_size, unsigned int id, int xoffset, int yoffset, int color, char symbol){

	for(int i = 0; i < list_size-1; ++i){
		if (c[i].id == 0){
			c[i].id = id;	
			c[i].xoffset = xoffset;
			c[i].yoffset = yoffset;
			c[i].color = color;
			c[i].symbol = symbol;
			break;
		}
	}
}

void entity_add_component_stats(ComponentStats c[], int list_size, unsigned int id, int hp, int str, int per, int agi){

	for(int i = 0; i < list_size-1; ++i){
		if (c[i].id == 0){
			c[i].id = id;	
			c[i].hp = hp;
			c[i].strength = str;
			c[i].perception = per;
			c[i].agility = agi;
			break;
		}
	}
}

