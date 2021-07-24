//entity.c
//Functions that manipulated entity lists
//by burlapjack 2021

#include <stdlib.h>
#include <stdio.h>
#include "../include/component.h"
#include "../include/entity.h"


void entity_list_size_double_position(ComponentPosition** entity, size_t *list_size){

	ComponentPosition *temp = realloc(*entity, sizeof **entity * (*list_size * 2));
	//test the reallocation
	if (temp == NULL) {
		perror("Failure to reallocate entity_list_position");
		exit(EXIT_FAILURE);
	}	

	*entity = temp;	

	for(size_t i = *list_size; i < (*list_size * 2 ); ++i ){
		(*entity)[i].id = i;
	}
	*list_size = *list_size * 2;
};


void entity_list_size_double_draw(ComponentDraw** entity, size_t *list_size){

	ComponentDraw* temp = realloc(*entity, sizeof (**entity) * (*list_size * 2));
	//test the reallocation
	if (temp == NULL) {
		perror("Failure to reallocate entity_list_draw");
		exit(EXIT_FAILURE);
	}	

	*entity = temp;	

	for(size_t i = (*list_size); i < (*list_size * 2 ); ++i ){
		(*entity)[i].id = 0;
	}
	*list_size = *list_size * 2;
};

void entity_list_size_double_stats(ComponentStats** entity, size_t *list_size){

	ComponentStats*temp = realloc(*entity, sizeof (**entity) * (*list_size * 2));
	//test the reallocation
	if (temp == NULL) {
		perror("Failure to reallocate entity_list_stats");
		exit(EXIT_FAILURE);
	}	

	*entity = temp;	

	for(size_t i = (*list_size); i < (*list_size * 2 ); ++i ){
		(*entity)[i].id = 0;
	}
	*list_size = *list_size * 2;
};



void entity_add_component_position(ComponentPosition *c,size_t list_size, unsigned int id, unsigned int x, unsigned int y){

	for(size_t i = 0; i < list_size; ++i){
		if (c[i].id == 0){
			c[i].id = id;	
			c[i].x = x;
			c[i].y = y;
			break;
		}
	}
}

void entity_add_component_draw(ComponentDraw *c, size_t list_size, unsigned int id, unsigned int color, char symbol){

	for(size_t i = 0; i < list_size; ++i){
		if (c[i].id == 0){
			c[i].id = id;	
			c[i].color = color;
			c[i].symbol = symbol;
			break;
		}
	}
}

void entity_add_component_stats(ComponentStats *c, size_t list_size, unsigned int id, unsigned int hp, unsigned int str, unsigned int per, unsigned int agi){

	for(size_t i = 0; i < list_size; ++i){
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

