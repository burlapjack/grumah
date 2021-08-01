// grumah.c
// by burlapjack 2021


#include <stdlib.h>
#include <ncurses.h>
#include <stdint.h>
#include "../include/component.h"
#include "../include/entity.h"
#include "../include/system.h"
#include "../include/ui.h"
#include <locale.h>

int main(){
	/* initialize ncurses */

	setlocale(LC_ALL, "");
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

	/* ncurses main_window */
	win_main = newwin(height,width,starty,startx);
	box(win_main, 0, 0);	
	keypad(win_main,TRUE);
	nodelay(win_main, TRUE);
	curs_set(0);


	/* Entities */
	unsigned int next_entity_id = 1;

	//Initialize Entity lists (arrays of component objects)
	ComponentPosition* entity_list_position;
	ComponentDraw* entity_list_draw;
	ComponentStats* entity_list_stats;
	
	size_t entity_list_size_init = 20;	
	size_t entity_list_size_position = entity_list_size_init;
	size_t entity_list_size_draw = entity_list_size_init;
	size_t entity_list_size_stats = entity_list_size_init;
		
	entity_list_position = malloc(sizeof (*entity_list_position) * entity_list_size_position);	
	entity_list_draw = malloc(sizeof (*entity_list_draw) * entity_list_size_draw);	
	entity_list_stats = malloc(sizeof (*entity_list_stats) * entity_list_size_stats);	
	

	/* Main menu/title screen initialization */
	UiMenu menu_start = ui_menu_create_title(9,2);

	/* Character Creation screen menu initialization */
	UiMenu menu_char_create = ui_menu_create_char_creation(3,3);
	
	/* game loop */

	int ch;
	unsigned int game_loop_run = 1;		
	unsigned int game_state = 0;		

	while(game_loop_run == 1){
		ch = wgetch(win_main);

		switch(game_state){
			case 0:
				ui_menu_draw(win_main, &menu_start, &ch, &game_loop_run, &game_state);
				break;
			case 1:
				ui_menu_draw(win_main, &menu_char_create, &ch, &game_loop_run, &game_state);
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
	free(entity_list_draw);
	free(entity_list_stats);
	delwin(win_main);
	endwin();

	return EXIT_SUCCESS;
}
