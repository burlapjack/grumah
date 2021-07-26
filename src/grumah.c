// grumah.c
// by burlapjack 2021


#include <stdlib.h>
#include <ncurses.h>
#include <stdint.h>
#include "../include/component.h"
#include "../include/entity.h"

int main(){

	/* initialize ncurses */
	
	WINDOW *w;
	unsigned int startx, starty, width, height;
	initscr();
	cbreak();
	noecho();
	height = 25;
	width = 70;

	/* Window centering calculation */
	if(LINES < height) starty = 0; else starty = (LINES - height) / 2;  
	if(COLS <  width) startx = 0; else startx = (COLS - width) / 2; 


	w = newwin(height,width,starty,startx);
	box(w, 0, 0);	
	keypad(w,TRUE);
	curs_set(0);


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




	wrefresh(w);	
	for(size_t i = 0; i < 10; ++i){
		entity_add_component_position(&entity_list_position,&entity_list_size_position, next_entity_id,i,10);	
		next_entity_id += 1;
	}

	//entity_list_size_double_position(&entity_list_position,&entity_list_size_position);

	for (size_t j = 0; j < entity_list_size_position; ++j) {
		mvwprintw(w, j+2,5,"  id: %2u   x: %2u  y: %2u", entity_list_position[j].id, entity_list_position[j].x, entity_list_position[j].y);
	}
	
	wrefresh(w);	
	

	wgetch(w);
	
	//free all dynamically allocated memory
	free(entity_list_position);
	free(entity_list_draw);
	free(entity_list_stats);
	delwin(w);
	endwin();

	return 0;
}



