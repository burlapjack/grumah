// grumah.c
// by burlapjack 2021


#include <stdlib.h>
#include <ncurses.h>
#include <stdint.h>
#include <string.h>
#include "../include/component.h"
#include "../include/entity.h"
#include "../include/entity_prefabs.h"
#include "../include/system.h"
#include <locale.h>

int main(){
	/* initialize ncurses */

	setlocale(LC_ALL, "");
	unsigned int startx, starty, win_width, win_height;
	initscr();
	WINDOW *win_main;
	cbreak();
	
	noecho();
	win_height = 24;
	win_width = 80;

	/* Window centering calculation */
	if(LINES < win_height) starty = 0; else starty = (LINES - win_height) / 2;  
	if(COLS <  win_width) startx = 0; else startx = (COLS - win_width) / 2; 

	/* ncurses main_window */
	win_main = newwin(win_height,win_width,starty,startx);
	box(win_main, 0, 0);	
	keypad(win_main,TRUE);
	nodelay(win_main, TRUE);
	curs_set(0);


	/* Entities */
	unsigned int next_entity_id = 1;

	//Initialize Entity lists (arrays of component objects)
	ComponentPosition* entity_list_position;
//	ComponentDraw* entity_list_draw;
//	ComponentStats* entity_list_stats;
	ComponentMenuOption* entity_list_menu_option;
	
	size_t entity_list_size_init = 20;	

	size_t entity_list_size_position = entity_list_size_init;
//	size_t entity_list_size_draw = entity_list_size_init;
//	size_t entity_list_size_stats = entity_list_size_init;
	size_t entity_list_size_menu_option = entity_list_size_init;
		
	entity_list_position = malloc(sizeof (*entity_list_position) * entity_list_size_position);	
//	entity_list_draw = malloc(sizeof (*entity_list_draw) * entity_list_size_draw);	
//	entity_list_stats = malloc(sizeof (*entity_list_stats) * entity_list_size_stats);	
	entity_list_menu_option = malloc(sizeof (*entity_list_menu_option) * entity_list_size_menu_option);	
	
	entity_prefab_create_title_menu(&next_entity_id, &entity_list_menu_option, &entity_list_size_menu_option, &entity_list_position, &entity_list_size_position);

	/* game loop */
//	int ch;
	unsigned int game_loop_run = 1;		
	unsigned int game_state = 1;		

	while(game_loop_run == 1){
		//ch = wgetch(win_main);

		system_menu(win_main, entity_list_menu_option, entity_list_size_menu_option, entity_list_position, entity_list_size_position, &game_state);
		switch(game_state){
			case 0:
				break;
			case 1:
				break;
			case 2:
				break;
			default:
				break;
		}
		wrefresh(win_main);
	}


	//free all dynamically allocated memory
	free(entity_list_position);
//	free(entity_list_draw);
//	free(entity_list_stats);
	free(entity_list_menu_option);
	delwin(win_main);
	endwin();

	return EXIT_SUCCESS;
}
