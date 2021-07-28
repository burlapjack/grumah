// grumah.c
// by burlapjack 2021


#include <stdlib.h>
#include <ncurses.h>
#include <stdint.h>
#include "../include/component.h"
#include "../include/entity.h"
#include "../include/system.h"

int main(){
	/* initialize ncurses */
	
	unsigned int startx, starty, width, height;
	initscr();
	WINDOW *win_main;
	cbreak();
	noecho();
	height = 24;
	width = 80;

	/* Window centering calculation */
	if(LINES < height) starty = 0; else starty = (LINES - height) / 2;  
	if(COLS <  width) startx = 0; else startx = (COLS - width) / 2; 


	win_main = newwin(height,width,starty,startx);
	box(win_main, 0, 0);	
	keypad(win_main,TRUE);
	curs_set(0);


	//Initialize Entities (arrays of component objects)
	ComponentPosition* entity_list_position;
	ComponentDraw* entity_list_draw;
	ComponentStats* entity_list_stats;
	ComponentMenu* entity_list_menu;

	size_t entity_list_size_init = 20;	
	size_t entity_list_size_position = entity_list_size_init;
	size_t entity_list_size_draw = entity_list_size_init;
	size_t entity_list_size_stats = entity_list_size_init;
	size_t entity_list_size_menu = entity_list_size_init;	

	unsigned int next_entity_id = 1;
		
	entity_list_position = malloc(sizeof (*entity_list_position) * entity_list_size_position);	
	entity_list_draw = malloc(sizeof (*entity_list_draw) * entity_list_size_draw);	
	entity_list_stats = malloc(sizeof (*entity_list_stats) * entity_list_size_stats);	
	entity_list_menu= malloc(sizeof (*entity_list_menu) * entity_list_size_menu);	



	system_input(win_main);


	//free all dynamically allocated memory
	free(entity_list_position);
	free(entity_list_draw);
	free(entity_list_stats);
	delwin(win_main);
	endwin();

	return 0;
}
