//component.c
//Functions that manipulated entity lists
//by burlapjack 2021

#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include "../include/component.h"
#include "../include/system.h"
/*
 * All component types are structs that include an id 
 * and some related variables:
 *
 * typedef struct{
 *		int id;
 *		int x;
 *		int y;
 * }ComponentPosition;
 *
 * Components then have to be add to arrays (lists). 
 * Optionally, the programmer can choose to initialize 
 * a container of type 'Component' that sets up all 
 * component lists automatically.
 *
 * Component *c;
 * component_init(c, size_lists);
 *
 */

/*---------------Initialize Component Lists -----------------------------------------------------*/

// Init all component lists within a Component instance
void component_init(Component *c, size_t size_lists){
	c->draw = malloc( sizeof (*(c->draw)) * size_lists); 
	c->menu_option = malloc( sizeof (*(c->menu_option)) * size_lists);
	c->position = malloc( sizeof (*(c->position)) * size_lists);
	c->size = malloc( sizeof (*(c->size)) * size_lists);
	c->stats = malloc( sizeof (*(c->stats)) * size_lists);
	c->trigger = malloc( sizeof (*(c->trigger)) * size_lists);

	c->size_draw = size_lists;
	c->size_menu_option = size_lists;
	c->size_position = size_lists;
	c->size_size = size_lists;
	c->size_stats = size_lists;
	c->size_trigger = size_lists;

	for( size_t i = 0; i < size_lists; i++){
		c->draw[i].id = 0;
		c->menu_option[i].id = 0;
		c->position[i].id = 0;
		c->size[i].id = 0;
		c->stats[i].id = 0;
		c->trigger[i].id = 0;
	}
}

/*-------------- Delete Component list data (without deallocation) ----------------------------------*/
void component_delete_all_draw(Component *c){
	for(size_t i = 0; i < (c->size_draw); i++){
		c->draw[i].id = 0;
		c->draw[i].symbol = ' ';
		c->draw[i].layer = 0;
	}	
}

void component_delete_all_input(Component *c){
	for(size_t i = 0; i < (c->size_draw); i++){
		c->input[i].id = 0;
		c->input[i].key_pressed = 0; //This might need to change
	}
}

void component_delete_all_menu_option(Component *c){
	for(size_t i = 0; i < (c->size_menu_option); i++){
		c->menu_option[i].id = 0;
		c->menu_option[i].parent_id = 0;
		memset(c->menu_option[i].name, ' ', 32);
		c->menu_option[i].highlighted = 0;
	}	
}

void component_delete_all_position(Component *c){
	for(size_t i = 0; i < (c->size_position); i++){
		c->position[i].id = 0;
		c->position[i].x =  0;
		c->position[i].y =  0;
	}
}

void component_delete_all_size(Component *c){
	for(size_t i = 0; i < (c->size_size); i++){
		c->size[i].id = 0;
		c->size[i].width = 0;	
		c->size[i].height = 0;	
	}
}


void component_delete_all_stats(Component *c){
	for(size_t i = 0; i < (c->size_stats); i++){
		c->stats[i].id = 0;
		c->stats[i].hp = 0;
		c->stats[i].strength = 0;
		c->stats[i].perception = 0;
		c->stats[i].agility = 0;
	}
}

void component_delete_all_trigger(Component *c){
	for(size_t i = 0; i < (c->size_trigger); i++){
		c->trigger[i].id = 0;
		c->trigger[i].game_state = 0;

	}
}

void component_delete_all(Component *c){
	component_delete_all_draw(c);	
	component_delete_all_menu_option(c);
	component_delete_all_position(c);	
	component_delete_all_size(c);	
	component_delete_all_stats(c);	
	component_delete_all_trigger(c);	
}

/*-------------- Free all Component Lists -----------------------------------------------------------*/

void component_free_all(Component *c){
	free(c->draw);
	c->draw = NULL;
	//free(c->input);
	//c->input = NULL;
	free(c->menu_option);
	c->menu_option = NULL;
	free(c->position);
	c->position = NULL;
	free(c->size);
	c->size = NULL;
	free(c->stats);
	c->stats = NULL;
	free(c->trigger);
	c->trigger = NULL;
	free(c);
}

/*---------------Double the size of an Component list -----------------------------------------------*/

void component_list_double_input(Component *c){
	//test the reallocation
	ComponentInput *temp = realloc(c->input, sizeof (ComponentInput) * (c->size_input* 2));
	if (temp == NULL) {
		perror("Failure to reallocate component_input");
		exit(EXIT_FAILURE);
	}	
	c->input= temp;	
	for(size_t i = c->size_input; i < (c->size_input * 2 ); ++i ){
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
	for(size_t i = c->size_position; i < (c->size_position * 2 ); ++i ){
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
	for(size_t i = c->size_draw; i < (c->size_draw * 2 ); ++i ){
		c->draw[i].id = 0;
	}
	c->size_draw = c->size_draw * 2;
}

void component_list_double_size(Component *c){
	//test the reallocation
	ComponentSize *temp = realloc(c->size, sizeof (ComponentSize) * (c->size_size* 2));
	if (temp == NULL) {
		perror("Failure to reallocate component_size");
		exit(EXIT_FAILURE);
	}	
	c->size = temp;	
	for(size_t i = c->size_size; i < (c->size_size * 2 ); ++i ){
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
	for(size_t i = c->size_stats; i < (c->size_stats * 2 ); ++i ){
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
	for(size_t i = c->size_menu_option; i < (c->size_menu_option* 2 ); ++i ){
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

	for(size_t i = c->size_trigger; i < (c->size_trigger * 2 ); ++i ){
		c->trigger[i].id = 0;
	}
	c->size_trigger = c->size_trigger * 2;
}

/*-------------- Add Component to entity list using a Component container struct -----------------*/

void component_add_input(Component *c, int id) {
	for(size_t i = 0; i < c->size_draw; ++i){
		if (i == c->size_draw-1 && c->draw[i].id != 0){
			component_list_double_draw(c);
		}
		else if (c->draw[i].id == 0){
			c->input[i].key_pressed = 0;
			break;
		}
	}
}

void component_add_draw(Component *c, int id, int layer, int color, char symbol) {
	for(size_t i = 0; i < c->size_draw; ++i){
		if (i == (c->size_draw - 1) && c->draw[i].id != 0){
			component_list_double_draw(c);
		}
		else if (c->draw[i].id == 0){
			c->draw[i].id = id;
			c->draw[i].color = color;
			c->draw[i].symbol = symbol;
			c->draw[i].layer = layer;
			break;
		}
	}
}

void component_add_position(Component *c, int id, int x, int y) {
	for(size_t i = 0; i < (c->size_position); ++i){
		if (i == (c->size_position-1) && c->position[i].id != 0){
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

void component_add_menu_option(Component *c, int id, char name[32], int parent_id, int highlighted) {
	for(size_t i = 0; i < (c->size_menu_option); ++i){
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

void component_add_size(Component *c, int id, int width, int height) {
	for(size_t i = 0; i < c->size_size; ++i){
		if (i == c->size_size-1 && c->size[i].id != 0){
			component_list_double_size(c);
		}
		else if (c->size[i].id == 0){
			c->size[i].id = id;
			break;
		}
	}
}

void component_add_stats(Component *c, int id, int hp, int str, int per, int agi) {
	for(size_t i = 0; i < c->size_stats; ++i){
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

void component_add_trigger(Component *c, int id, int game_state) {
	for(size_t i = 0; i < c->size_trigger; ++i){
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
int component_count_draw(Component *c){
	int total=0;
	for(size_t i = 0; i < (c->size_draw); i++){
		if(c->draw[i].id != 0) total++;
	}
	return total;
}

int component_count_position(Component *c){
	int total=0;
	for(size_t i = 0; i < (c->size_position); i++){
		if(c->position[i].id != 0) total++;
	}
	return total;
}

int component_count_menu_option(Component *c){
	int total=0;
	for(size_t i = 0; i < (c->size_menu_option); i++){
		if(c->menu_option[i].id != 0) total++;
	}
	return total;
}

int component_count_size(Component *c){
	int total=0;
	for(size_t i = 0; i < (c->size_size); i++){
		if(c->size[i].id != 0) total++;
	}
	return total;
}

int component_count_stats(Component *c){
	int total=0;
	for(size_t i = 0; i < (c->size_stats); i++){
		if(c->stats[i].id != 0) total++;
	}
	return total;
}

int component_count_trigger(Component *c){
	int total=0;
	for(size_t i = 0; i < (c->size_trigger); i++){
		if(c->trigger[i].id != 0) total++;
	}
	return total;
}

int component_count_all(Component *c){
	int total = 0;
	total = component_count_draw(c) + component_count_position(c) + component_count_menu_option(c) + total + component_count_stats(c) + total + component_count_trigger(c);
	return total;	
}

int component_count_invisible(Component *c){
	int total = 0;
	for(size_t i = 0; i < (c->size_position); i++){
		if(c->position[i].id != 0){
			for(int j = 0; j < (c->size_draw); j++){
				if(c->position[i].id == c->draw[j].id) break;
				if(j == c->size_draw-1) total++;
			}
		}	
	}
	return total;
}

/*-------------- Set Component Draw Layer --------------------------------------------------------*/

void component_set_draw_layer(Component *c, int component_id, int draw_layer){
	for(size_t i = 0; i < (c->size_draw); i++){
		if(c->draw[i].id == component_id){
			c->draw[i].layer = draw_layer;	
		}
	}
}
