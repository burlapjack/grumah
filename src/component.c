//entity.c
//Functions that manipulated entity lists
//by burlapjack 2021

#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include "../include/component.h"
#include "../include/system.h"


/*---------------Initialize Component Lists -----------------------------------------------------*/

void component_list_init_all(size_t list_size, ComponentPosition **cp, ComponentDraw **cd, ComponentStats **cs, ComponentMenuOption **co){

	*cp = malloc(sizeof (*cp) * list_size);	
	*cd = malloc(sizeof (*cd) * list_size);	
	*cs = malloc(sizeof (*cs) * list_size);	
	*co = malloc(sizeof (*co) * list_size);	
}


/*-------------- Free all Component Lists -----------------------------------------------------------*/

void component_list_free_all(ComponentPosition *cp, ComponentDraw *cd, ComponentStats *cs, ComponentMenuOption *co){

	free(cp);
	free(cd);
	free(cs);
	free(co);
}

/*---------------Double the size of an Component list -----------------------------------------------*/

void component_list_size_double_position(ComponentPosition** component_list, size_t *list_size){
	//test the reallocation
	ComponentPosition *temp = realloc(*component_list, sizeof **component_list * (*list_size * 2));
	if (temp == NULL) {
		perror("Failure to reallocate component_list_position");
		exit(EXIT_FAILURE);
	}	
	*component_list = temp;	

	for(size_t i = *list_size; i < (*list_size * 2 ); ++i ){
		(*component_list)[i].id = 0;
	}
	*list_size = *list_size * 2;
}

void component_list_size_double_draw(ComponentDraw** component_list, size_t *list_size){
	//test the reallocation
	ComponentDraw* temp = realloc(*component_list, sizeof (**component_list) * (*list_size * 2));
	if (temp == NULL) {
		perror("Failure to reallocate component_list_draw");
		exit(EXIT_FAILURE);
	}	
	*component_list = temp;	

	for(size_t i = *list_size; i < (*list_size * 2 ); ++i ){
		(*component_list)[i].id = 0;
	}
	*list_size = *list_size * 2;
}

void component_list_size_double_stats(ComponentStats** component_list, size_t *list_size){
	//test the reallocation
	ComponentStats*temp = realloc(*component_list, sizeof **component_list * (*list_size * 2));
	if (temp == NULL) {
		perror("Failure to reallocate component_list_stats");
		exit(EXIT_FAILURE);
	}	
	*component_list = temp;	

	for(size_t i = *list_size; i < (*list_size * 2 ); ++i ){
		(*component_list)[i].id = 0;
	}
	*list_size = *list_size * 2;
}

void component_list_size_double_menu_option(ComponentMenuOption** component_list, size_t *list_size){
	//test the reallocation
	ComponentMenuOption *temp = realloc(*component_list, sizeof **component_list * (*list_size * 2));
	if (temp == NULL) {
		perror("Failure to reallocate component_list_stats");
		exit(EXIT_FAILURE);
	}	
	*component_list = temp;	

	for(size_t i = *list_size; i < (*list_size * 2 ); ++i ){
		(*component_list)[i].id = 0;
	}
	*list_size = *list_size * 2;
}




/*---------------Add Component to entity list-----------------------------------------------------*/

void component_add_position(ComponentPosition **component_list,size_t *list_size, unsigned int id, unsigned int x, unsigned int y){
	for(size_t i = 0; i < *list_size; ++i){
		if (i == *list_size-1 && (*component_list)[i].id != 0){
			component_list_size_double_position(component_list,list_size);
		}
		else if ((*component_list)[i].id == 0){
			(*component_list)[i].id = id;	
			(*component_list)[i].x = x;
			(*component_list)[i].y = y;
			break;
		}
	}
}

void component_add_draw(ComponentDraw **component_list, size_t *list_size, unsigned int id, unsigned int color, char symbol){
	for(size_t i = 0; i < *list_size; ++i){
		if (i == *list_size-1 && (*component_list)[i].id != 0){
			component_list_size_double_draw(component_list,list_size);
		}
		else if ((*component_list)[i].id == 0){
			(*component_list)[i].id = id;	
			(*component_list)[i].color = color;
			(*component_list)[i].symbol = symbol;
			break;
		}
	}
}

void component_add_stats(ComponentStats **component_list, size_t *list_size, unsigned int id, unsigned int hp, unsigned int str, unsigned int per, unsigned int agi){
	for(size_t i = 0; i < *list_size; ++i){
		if (i == *list_size-1 && (*component_list)[i].id != 0){
			component_list_size_double_stats(component_list,list_size);
		}
		else if ((*component_list)[i].id == 0){
			(*component_list)[i].id = id;	
			(*component_list)[i].hp = hp;
			(*component_list)[i].strength = str;
			(*component_list)[i].perception = per;
			(*component_list)[i].agility = agi;
			break;
		}
	}
}

void component_add_menu_option(ComponentMenuOption **component_list, size_t *list_size, unsigned int id, char name[32], unsigned int game_state, unsigned int highlighted){

	for(size_t i = 0; i < *list_size; ++i){
		if (i == *list_size-1 && (*component_list)[i].id != 0){
			component_list_size_double_menu_option(component_list,list_size);
		}
		else if ((*component_list)[i].id == 0){
			(*component_list)[i].id = id;
			strcpy((*component_list)[i].name, name ); /* check if this is right! */
			(*component_list)[i].parent_id = game_state;	
			(*component_list)[i].highlighted = highlighted;	
			break;
		}
	}
}
