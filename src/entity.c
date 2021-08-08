//entity.c
//Functions that manipulated entity lists
//by burlapjack 2021

#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include "../include/component.h"
#include "../include/entity.h"
#include "../include/system.h"



void entity_add_player(unsigned int id, int x, int y, ComponentPosition **cp, size_t *cp_list_size,ComponentDraw **cd,size_t *cd_list_size, ComponentStats **cs,size_t *cs_list_size){
	component_add_position( cp, cp_list_size, id, x, y); 		
	component_add_draw( cd, cd_list_size, id, 1, '@');
	component_add_stats(cs, cs_list_size, id, 5, 5, 5, 5);
}
	
void entity_add_title_menu(unsigned int *id, ComponentMenuOption **cmo, size_t *cmo_list_size, ComponentPosition **cp, size_t *cp_list_size){
	component_add_menu_option(cmo, cmo_list_size,*id,"Start New Game",1,1);
	component_add_position(cp, cp_list_size, *id, 33, 16);
	*id = *id + 1;
	component_add_menu_option(cmo, cmo_list_size,*id,"Exit Game",1,0);
	component_add_position(cp, cp_list_size, *id, 35, 17);
}








/*---------------Initialize Entity Lists -----------------------------------------------------*/

void entity_list_init_all(size_t list_size, ComponentPosition **cp, ComponentDraw **cd, ComponentStats **cs, ComponentMenuOption **co){

	*cp = malloc(sizeof (*cp) * list_size);	
	*cd = malloc(sizeof (*cd) * list_size);	
	*cs = malloc(sizeof (*cs) * list_size);	
	*co = malloc(sizeof (*co) * list_size);	
}


/*-------------- Free all Entity Lists -----------------------------------------------------------*/

void entity_list_free_all(ComponentPosition *cp, ComponentDraw *cd, ComponentStats *cs, ComponentMenuOption *co){

	free(cp);
	free(cd);
	free(cs);
	free(co);
}

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
			(*entity_list)[i].parent_id = game_state;	
			(*entity_list)[i].highlighted = highlighted;	
			break;
		}
	}
}
