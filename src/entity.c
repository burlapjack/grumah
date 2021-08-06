//entity.c
//Functions that manipulated entity lists
//by burlapjack 2021

#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include "../include/component.h"
#include "../include/entity.h"
#include "../include/system.h"

/*---------------Double the size of an Entity list -----------------------------------------------*/

void entity_list_size_double_position(ComponentPosition** entity_list, size_t *list_size){
	//test the reallocation
	ComponentPosition *temp = realloc(*entity_list, sizeof **entity_list * (*list_size * 2));
	if (temp == NULL) {
		perror("Failure to reallocate entity_list_position");
		exit(EXIT_FAILURE);
	}	
	*entity_list = temp;	

	for(size_t i = *list_size; i < (*list_size * 2 ); ++i ){
		(*entity_list)[i].id = 0;
	}
	*list_size = *list_size * 2;
}

void entity_list_size_double_draw(ComponentDraw** entity_list, size_t *list_size){
	//test the reallocation
	ComponentDraw* temp = realloc(*entity_list, sizeof (**entity_list) * (*list_size * 2));
	if (temp == NULL) {
		perror("Failure to reallocate entity_list_draw");
		exit(EXIT_FAILURE);
	}	
	*entity_list = temp;	

	for(size_t i = *list_size; i < (*list_size * 2 ); ++i ){
		(*entity_list)[i].id = 0;
	}
	*list_size = *list_size * 2;
}

void entity_list_size_double_stats(ComponentStats** entity_list, size_t *list_size){
	//test the reallocation
	ComponentStats*temp = realloc(*entity_list, sizeof **entity_list * (*list_size * 2));
	if (temp == NULL) {
		perror("Failure to reallocate entity_list_stats");
		exit(EXIT_FAILURE);
	}	
	*entity_list = temp;	

	for(size_t i = *list_size; i < (*list_size * 2 ); ++i ){
		(*entity_list)[i].id = 0;
	}
	*list_size = *list_size * 2;
}

void entity_list_size_double_menu_option(ComponentMenuOption** entity_list, size_t *list_size){
	//test the reallocation
	ComponentMenuOption *temp = realloc(*entity_list, sizeof **entity_list * (*list_size * 2));
	if (temp == NULL) {
		perror("Failure to reallocate entity_list_stats");
		exit(EXIT_FAILURE);
	}	
	*entity_list = temp;	

	for(size_t i = *list_size; i < (*list_size * 2 ); ++i ){
		(*entity_list)[i].id = 0;
	}
	*list_size = *list_size * 2;
}




/*---------------Add Component to entity list-----------------------------------------------------*/

void entity_add_component_position(ComponentPosition **entity_list,size_t *list_size, unsigned int id, unsigned int x, unsigned int y){
	for(size_t i = 0; i < *list_size; ++i){
		if (i == *list_size-1 && (*entity_list)[i].id != 0){
			entity_list_size_double_position(entity_list,list_size);
		}
		else if ((*entity_list)[i].id == 0){
			(*entity_list)[i].id = id;	
			(*entity_list)[i].x = x;
			(*entity_list)[i].y = y;
			break;
		}
	}
}

void entity_add_component_draw(ComponentDraw **entity_list, size_t *list_size, unsigned int id, unsigned int color, char symbol){
	for(size_t i = 0; i < *list_size; ++i){
		if (i == *list_size-1 && (*entity_list)[i].id != 0){
			entity_list_size_double_draw(entity_list,list_size);
		}
		else if ((*entity_list)[i].id == 0){
			(*entity_list)[i].id = id;	
			(*entity_list)[i].color = color;
			(*entity_list)[i].symbol = symbol;
			break;
		}
	}
}

void entity_add_component_stats(ComponentStats **entity_list, size_t *list_size, unsigned int id, unsigned int hp, unsigned int str, unsigned int per, unsigned int agi){
	for(size_t i = 0; i < *list_size; ++i){
		if (i == *list_size-1 && (*entity_list)[i].id != 0){
			entity_list_size_double_stats(entity_list,list_size);
		}
		else if ((*entity_list)[i].id == 0){
			(*entity_list)[i].id = id;	
			(*entity_list)[i].hp = hp;
			(*entity_list)[i].strength = str;
			(*entity_list)[i].perception = per;
			(*entity_list)[i].agility = agi;
			break;
		}
	}
}

void entity_add_component_menu_option(ComponentMenuOption **entity_list, size_t *list_size, unsigned int id, char name[32], unsigned int game_state, unsigned int highlighted){

	for(size_t i = 0; i < *list_size; ++i){
		if (i == *list_size-1 && (*entity_list)[i].id != 0){
			entity_list_size_double_menu_option(entity_list,list_size);
		}
		else if ((*entity_list)[i].id == 0){
			(*entity_list)[i].id = id;
			strcpy((*entity_list)[i].name, name ); /* check if this is right! */
			(*entity_list)[i].game_state = game_state;	
			(*entity_list)[i].highlighted = highlighted;	
			break;
		}
	}
}
