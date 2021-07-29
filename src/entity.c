//entity.c
//Functions that manipulated entity lists
//by burlapjack 2021

#include <stdlib.h>
#include <ncurses.h>
#include "../include/component.h"
#include "../include/entity.h"
#include "../include/system.h"

/*----Increase the size of an Entity list -----*/

void entity_list_size_double_position(ComponentPosition** entity, size_t *list_size){
	//test the reallocation
	ComponentPosition *temp = realloc(*entity, sizeof **entity * (*list_size * 2));
	if (temp == NULL) {
		perror("Failure to reallocate entity_list_position");
		exit(EXIT_FAILURE);
	}	
	*entity = temp;	

	for(size_t i = *list_size; i < (*list_size * 2 ); ++i ){
		(*entity)[i].id = 0;
	}
	*list_size = *list_size * 2;
}

void entity_list_size_double_draw(ComponentDraw** entity, size_t *list_size){
	//test the reallocation
	ComponentDraw* temp = realloc(*entity, sizeof (**entity) * (*list_size * 2));
	if (temp == NULL) {
		perror("Failure to reallocate entity_list_draw");
		exit(EXIT_FAILURE);
	}	
	*entity = temp;	

	for(size_t i = *list_size; i < (*list_size * 2 ); ++i ){
		(*entity)[i].id = 0;
	}
	*list_size = *list_size * 2;
}

void entity_list_size_double_stats(ComponentStats** entity, size_t *list_size){
	//test the reallocation
	ComponentStats*temp = realloc(*entity, sizeof **entity * (*list_size * 2));
	if (temp == NULL) {
		perror("Failure to reallocate entity_list_stats");
		exit(EXIT_FAILURE);
	}	
	*entity = temp;	

	for(size_t i = *list_size; i < (*list_size * 2 ); ++i ){
		(*entity)[i].id = 0;
	}
	*list_size = *list_size * 2;
}


void entity_add_component_position(ComponentPosition** c,size_t *list_size, unsigned int id, unsigned int x, unsigned int y){
	for(size_t i = 0; i < *list_size; ++i){
		if (i == *list_size-1 && (*c)[i].id != 0){
			entity_list_size_double_position(c,list_size);
		}
		else if ((*c)[i].id == 0){
			(*c)[i].id = id;	
			(*c)[i].x = x;
			(*c)[i].y = y;
			break;
		}
	}
}

void entity_add_component_draw(ComponentDraw **c, size_t *list_size, unsigned int id, unsigned int color, char symbol){
	for(size_t i = 0; i < *list_size; ++i){
		if (i == *list_size-1 && (*c)[i].id != 0){
			entity_list_size_double_draw(c,list_size);
		}
		else if ((*c)[i].id == 0){
			(*c)[i].id = id;	
			(*c)[i].color = color;
			(*c)[i].symbol = symbol;
			break;
		}
	}
}

void entity_add_component_stats(ComponentStats **c, size_t *list_size, unsigned int id, unsigned int hp, unsigned int str, unsigned int per, unsigned int agi){
	for(size_t i = 0; i < *list_size; ++i){
		if (i == *list_size-1 && (*c)[i].id != 0){
			entity_list_size_double_stats(c,list_size);
		}
		if ((*c)[i].id == 0){
			(*c)[i].id = id;	
			(*c)[i].hp = hp;
			(*c)[i].strength = str;
			(*c)[i].perception = per;
			(*c)[i].agility = agi;
			break;
		}
	}
}


