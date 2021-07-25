// grumah.c
// by burlapjack 2021


#include <stdlib.h>
#include <ncurses.h>
#include <stdint.h>
#include "../include/component.h"
#include "../include/entity.h"


int main(){

	//initialize ncurses
	
	cbreak();
	keypad(stdscr,TRUE);
	curs_set(0);
	initscr();


	//Initialize Entities (arrays of component objects)
	ComponentPosition* entity_list_position;
	ComponentDraw* entity_list_draw;
	ComponentStats* entity_list_stats;

	size_t entity_list_size_init = 5;	
	size_t entity_list_size_position = entity_list_size_init;
	size_t entity_list_size_draw = entity_list_size_init;
	size_t entity_list_size_stats = entity_list_size_init;

	unsigned int next_entity_id = 1;
		
	entity_list_position = malloc(sizeof (*entity_list_position) * entity_list_size_position);	
	entity_list_draw = malloc(sizeof (*entity_list_draw) * entity_list_size_draw);	
	entity_list_stats = malloc(sizeof (*entity_list_stats) * entity_list_size_stats);	




	wrefresh(stdscr);	
	for(size_t i = 0; i < 10; ++i){
		entity_add_component_position(&entity_list_position,&entity_list_size_position, next_entity_id,i,10);	
		next_entity_id += 1;
	}

	entity_list_size_double_position(&entity_list_position,&entity_list_size_position);

	for (size_t j = 0; j < entity_list_size_position; ++j) {
		printw("  id: %2u   x: %2u  y: %2u\n", entity_list_position[j].id, entity_list_position[j].x, entity_list_position[j].y);
		wrefresh(stdscr);	
	}
	
	getch();

	//free all dynamically allocated memory
	free(entity_list_position);
	free(entity_list_draw);
	free(entity_list_stats);

	endwin();
	return 0;
}



