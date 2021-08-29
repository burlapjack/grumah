//component.c
//Functions that manipulated entity lists
//by burlapjack 2021

#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include "../include/component.h"
#include "../include/system.h"


/*---------------Initialize Component Lists -----------------------------------------------------*/

ComponentDraw* component_init_draw(ComponentDraw **c, unsigned int size_list){
	
	*c = malloc(sizeof (*c) * size_list);
	for( int i = 0; i < size_list; i++) (*c)->id = 0;
	return *c;
}

ComponentMenuOption* component_init_menu_option(ComponentMenuOption **c, unsigned int size_list){
	*c = malloc(sizeof (*c) * size_list);
	for( int i = 0; i < size_list; i++) (*c)->id = 0;
	return *c;
}

ComponentPosition* component_init_position(ComponentPosition **c, unsigned int size_list){
	*c = malloc(sizeof (*c) * size_list);
	for( int i = 0; i < size_list; i++) (*c)->id = 0;
	return *c;	
}

ComponentSize* component_init_size(ComponentSize **c, unsigned int size_list){
	*c = malloc(sizeof (*c) * size_list);
	for( int i = 0; i < size_list; i++) (*c)->id = 0;
	return *c;
}

ComponentStats* component_init_stats(ComponentStats **c, unsigned int size_list){
	*c = malloc(sizeof (*c) * size_list);
	for( int i = 0; i < size_list; i++) (*c)->id = 0;
	return *c;
}

ComponentTrigger* component_init_trigger(ComponentTrigger **c, unsigned int size_list){
	*c = malloc(sizeof (*c) * size_list);
	for( int i = 0; i < size_list; i++) (*c)->id = 0;
	return *c;
}

/*----------------Initialize a component collection-----------------------------------------------*/
void component_list_init_all(unsigned int list_size, ComponentPosition **cp, ComponentDraw **cd, ComponentStats **cs, ComponentMenuOption **co){
	*cp = malloc(sizeof (*cp) * list_size);	
	*cd = malloc(sizeof (*cd) * list_size);	
	*cs = malloc(sizeof (*cs) * list_size);	
	*co = malloc(sizeof (*co) * list_size);	
}

// Init all component lists within a Component instance
Component* component_init(Component *c, unsigned int size_lists){
	c->draw = malloc( sizeof (*(c->draw)) * size_lists); 
	c->size_draw = size_lists;
	c->menu_option = malloc( sizeof (*(c->menu_option)) * size_lists);
	c->size_menu_option = size_lists;
	c->position = malloc( sizeof (*(c->position)) * size_lists);
	c->size_position = size_lists;
	c->stats = malloc( sizeof (*(c->stats)) * size_lists);
	c->size_stats = size_lists;
	c->trigger = malloc( sizeof (*(c->trigger)) * size_lists);
	c->size_trigger = size_lists;

	for( unsigned int i = 0; i < size_lists; i++){
		c->draw[i].id = 0;
		c->menu_option[i].id = 0;
		c->position[i].id = 0;
		c->stats[i].id = 0;
		c->trigger[i].id = 0;
	}

	return c;	
}

/*-------------- Free all Component Lists -----------------------------------------------------------*/

void component_list_free_all(ComponentPosition *cp, ComponentDraw *cd, ComponentStats *cs, ComponentMenuOption *co){
	free(cp);
	free(cd);
	free(cs);
	free(co);
}

void component_free_all(Component *c){
	free(c->draw);
	free(c->menu_option);
	free(c->position);
	free(c->stats);
	free(c->trigger);
}

/*---------------Double the size of an Component list -----------------------------------------------*/

void component_list_size_double_position(ComponentPosition** component_list, unsigned int *list_size){
	//test the reallocation
	ComponentPosition *temp = realloc(*component_list, sizeof **component_list * (*list_size * 2));
	if (temp == NULL) {
		perror("Failure to reallocate component_list_position");
		exit(EXIT_FAILURE);
	}	
	*component_list = temp;	

	for(unsigned int i = *list_size; i < (*list_size * 2 ); ++i ){
		(*component_list)[i].id = 0;
	}
	*list_size = *list_size * 2;
}

void component_list_size_double_draw(ComponentDraw** component_list, unsigned int *list_size){
	//test the reallocation
	ComponentDraw* temp = realloc(*component_list, sizeof (**component_list) * (*list_size * 2));
	if (temp == NULL) {
		perror("Failure to reallocate component_list_draw");
		exit(EXIT_FAILURE);
	}	
	*component_list = temp;	

	for(unsigned int i = *list_size; i < (*list_size * 2 ); ++i ){
		(*component_list)[i].id = 0;
	}
	*list_size = *list_size * 2;
}

void component_list_size_double_stats(ComponentStats** component_list, unsigned int *list_size){
	//test the reallocation
	ComponentStats*temp = realloc(*component_list, sizeof **component_list * (*list_size * 2));
	if (temp == NULL) {
		perror("Failure to reallocate component_list_stats");
		exit(EXIT_FAILURE);
	}	
	*component_list = temp;	

	for(unsigned int i = *list_size; i < (*list_size * 2 ); ++i ){
		(*component_list)[i].id = 0;
	}
	*list_size = *list_size * 2;
}

void component_list_size_double_menu_option(ComponentMenuOption** component_list, unsigned int *list_size){
	//test the reallocation
	ComponentMenuOption *temp = realloc(*component_list, sizeof **component_list * (*list_size * 2));
	if (temp == NULL) {
		perror("Failure to reallocate component_menu_option");
		exit(EXIT_FAILURE);
	}	
	*component_list = temp;	

	for(unsigned int i = *list_size; i < (*list_size * 2 ); ++i ){
		(*component_list)[i].id = 0;
	}
	*list_size = *list_size * 2;
}


void component_list_size_double_trigger(ComponentTrigger** component_list, unsigned int *list_size){
	//test the reallocation
	ComponentTrigger *temp = realloc(*component_list, sizeof **component_list * (*list_size * 2));
	if (temp == NULL) {
		perror("Failure to reallocate component_trigger");
		exit(EXIT_FAILURE);
	}	
	*component_list = temp;	

	for(unsigned int i = *list_size; i < (*list_size * 2 ); ++i ){
		(*component_list)[i].id = 0;
	}
	*list_size = *list_size * 2;
}

//EXPERIMENTAL

void component_list_double_input(Component *c){
	//test the reallocation
	ComponentInput *temp = realloc(c->input, sizeof (ComponentInput) * (c->size_input* 2));
	if (temp == NULL) {
		perror("Failure to reallocate component_input");
		exit(EXIT_FAILURE);
	}	
	c->input= temp;	

	for(unsigned int i = c->size_input; i < (c->size_input * 2 ); ++i ){
		c->input[i].id = 0;
	}
	c->size_input = c->size_input * 2;

}

void component_list_double_position(Component *c){
	//test the reallocation
	ComponentPosition *temp = realloc(c->position, sizeof (ComponentPosition) * (c->size_position* 2));
	if (temp == NULL) {
		perror("Failure to reallocate component_position");
		exit(EXIT_FAILURE);
	}	
	c->position = temp;	

	for(unsigned int i = c->size_position; i < (c->size_position * 2 ); ++i ){
		c->position[i].id = 0;
	}
	c->size_position = c->size_position * 2;
}


void component_list_double_draw(Component *c){
	//test the reallocation
	ComponentDraw *temp = realloc(c->draw, sizeof (ComponentDraw) * (c->size_draw* 2));
	if (temp == NULL) {
		perror("Failure to reallocate component_draw");
		exit(EXIT_FAILURE);
	}	
	c->draw = temp;	

	for(unsigned int i = c->size_draw; i < (c->size_draw * 2 ); ++i ){
		c->draw[i].id = 0;
	}
	c->size_draw= c->size_draw * 2;
}

void component_list_double_size(Component *c){
	//test the reallocation
	ComponentSize *temp = realloc(c->size, sizeof (ComponentSize) * (c->size_size* 2));
	if (temp == NULL) {
		perror("Failure to reallocate component_size");
		exit(EXIT_FAILURE);
	}	
	c->size = temp;	

	for(unsigned int i = c->size_size; i < (c->size_size * 2 ); ++i ){
		c->size[i].id = 0;
	}
	c->size_size = c->size_size * 2;
}

void component_list_double_stats(Component *c){
	//test the reallocation
	ComponentStats *temp = realloc(c->stats, sizeof (ComponentStats) * (c->size_stats* 2));
	if (temp == NULL) {
		perror("Failure to reallocate component_stats");
		exit(EXIT_FAILURE);
	}	
	c->stats = temp;	

	for(unsigned int i = c->size_stats; i < (c->size_stats * 2 ); ++i ){
		c->stats[i].id = 0;
	}
	c->size_stats = c->size_stats * 2;
}



void component_list_double_menu_option(Component *c){
	//test the reallocation
	ComponentMenuOption *temp = realloc(c->menu_option, sizeof (ComponentMenuOption) * (c->size_menu_option * 2));
	if (temp == NULL) {
		perror("Failure to reallocate component_menu_option");
		exit(EXIT_FAILURE);
	}	
	c->menu_option = temp;	

	for(unsigned int i = c->size_menu_option; i < (c->size_menu_option* 2 ); ++i ){
		c->menu_option[i].id = 0;
	}
	c->size_menu_option = c->size_menu_option * 2;
}



void component_list_double_trigger(Component *c){
	//test the reallocation
	ComponentTrigger *temp = realloc(c->trigger, sizeof (ComponentTrigger) * (c->size_trigger * 2));
	if (temp == NULL) {
		perror("Failure to reallocate component_trigger");
		exit(EXIT_FAILURE);
	}	
	c->trigger = temp;	

	for(unsigned int i = c->size_trigger; i < (c->size_trigger * 2 ); ++i ){
		c->trigger[i].id = 0;
	}
	c->size_trigger = c->size_trigger * 2;
}

/*---------------Add Component to entity list-----------------------------------------------------*/


void component_list_add_draw(ComponentDraw **component_list, unsigned int *list_size, unsigned int id, int color, char symbol){
	for(unsigned int i = 0; i < *list_size; ++i){
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

void component_list_add_position(ComponentPosition **component_list,unsigned int *list_size, unsigned int id, int x, int y){
	for(unsigned int i = 0; i < *list_size; ++i){
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

void component_list_add_stats(ComponentStats **component_list, unsigned int *list_size, unsigned int id, unsigned int hp, unsigned int str, unsigned int per, unsigned int agi){
	for(unsigned int i = 0; i < *list_size; ++i){
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

void component_list_add_menu_option(ComponentMenuOption **component_list, unsigned int *list_size, unsigned int id, char name[32], unsigned int game_state, unsigned int highlighted){
	for(unsigned int i = 0; i < *list_size; ++i){
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

void component_list_add_trigger(ComponentTrigger**component_list, unsigned int *list_size, unsigned int id, unsigned int game_state){
	for(unsigned int i = 0; i < *list_size; ++i){
		if (i == *list_size-1 && (*component_list)[i].id != 0){
			component_list_size_double_trigger(component_list,list_size);
		}
		else if ((*component_list)[i].id == 0){
			(*component_list)[i].id = id;
			(*component_list)[i].game_state = game_state;
			break;
		}
	}
}


//EXPERIMENTAL

void component_add_input(Component *c, unsigned int id) {
	for(int i = 0; i < c->size_draw; ++i){
		if (i == c->size_draw-1 && c->draw[i].id != 0){
			component_list_double_draw(c);
		}
		else if (c->draw[i].id == 0){
			c->input[i].key_pressed = 0;
			break;
		}
	}
}

void component_add_draw(Component *c, unsigned int id, int color, char symbol) {
	for(int i = 0; i < c->size_draw; ++i){
		if (i == c->size_draw-1 && c->draw[i].id != 0){
			component_list_double_draw(c);
		}
		else if (c->draw[i].id == 0){
			c->draw[i].id = id;
			c->draw[i].color = color;
			c->draw[i].symbol = symbol;
			break;
		}
	}
}

void component_add_position(Component *c, unsigned int id, int x, int y) {
	for(int i = 0; i < c->size_position; ++i){
		if (i == c->size_position-1 && c->position[i].id != 0){
			component_list_double_position(c);
		}
		else if (c->position[i].id == 0){
			c->position[i].id = id;
			c->position[i].x = x;
			c->position[i].y = y;
			break;
		}
	}
}

void component_add_menu_option(Component *c, unsigned int id, char name[32], unsigned int parent_id, unsigned int highlighted) {
	for(int i = 0; i < (c->size_menu_option); ++i){
		if (i == c->size_menu_option-1 && c->menu_option[i].id != 0){
			component_list_double_menu_option(c);
		}
		else if (c->menu_option[i].id == 0){
			c->menu_option[i].id = id;
			strcpy(c->menu_option[i].name,name); /*check if this is right! */
			c->menu_option[i].parent_id = parent_id;
			c->menu_option[i].highlighted = highlighted;
			break;
		}
	}
}

void component_add_stats(Component *c, unsigned int id, unsigned int hp, unsigned int str, unsigned int per, unsigned int agi) {
	for(int i = 0; i < c->size_stats; ++i){
		if (i == c->size_stats-1 && c->stats[i].id != 0){
			component_list_double_stats(c);
		}
		else if (c->stats[i].id == 0){
			c->stats[i].id = id;
			c->stats[i].hp = hp;
			c->stats[i].strength = str;
			c->stats[i].perception = per;
			c->stats[i].agility = agi;
			break;
		}
	}
}

void component_add_trigger(Component *c, unsigned int id, unsigned int game_state) {
	for(int i = 0; i < c->size_trigger; ++i){
		if (i == c->size_trigger-1 && c->trigger[i].id != 0){
			component_list_double_trigger(c);
		}
		else if (c->trigger[i].id == 0){
			c->trigger[i].id = id;
			c->trigger[i].game_state = game_state;
			break;
		}
	}
}

/*---------------Query Component Lists -----------------------------------------------------------*/

// Find the total of a certain component
unsigned int component_count_draw(Component *c){
	unsigned int total=0;
	for(int i = 0; i < (c->size_draw); i++){
		if(c->draw[i].id != 0) total++;
	}
	return total;
}

unsigned int component_count_position(Component *c){
	unsigned int total=0;
	for(int i = 0; i < (c->size_position); i++){
		if(c->position[i].id != 0) total++;
	}
	return total;
}

unsigned int component_count_menu_option(Component *c){
	unsigned int total=0;
	for(int i = 0; i < (c->size_menu_option); i++){
		if(c->menu_option[i].id != 0) total++;
	}
	return total;
}

unsigned int component_count_stats(Component *c){
	unsigned int total=0;
	for(int i = 0; i < (c->size_stats); i++){
		if(c->stats[i].id != 0) total++;
	}
	return total;
}

unsigned int component_count_trigger(Component *c){
	unsigned int total=0;
	for(int i = 0; i < (c->size_trigger); i++){
		if(c->trigger[i].id != 0) total++;
	}
	return total;
}

unsigned int component_count_all(Component *c){
	unsigned int total = 0;
	total = component_count_draw(c) + component_count_position(c) + component_count_menu_option(c) + total + component_count_stats(c) + total + component_count_trigger(c);
	return total;	
}

unsigned int component_count_invisible(Component *c){
	unsigned int total = 0;
	for(int i = 0; i < (c->size_position); i++){
		if(c->position[i].id != 0){
			for(int j = 0; j < (c->size_draw); j++){
				if(c->position[i].id == c->draw[j].id) break;
				if(j == c->size_draw-1) total++;
			}
		}	
	}
	return total;
}
