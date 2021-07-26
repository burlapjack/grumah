// grumah.c
// by burlapjack 2021


#include <stdlib.h>
#include <ncurses.h>
#include <stdint.h>
#include "../include/component.h"
#include "../include/entity.h"

int main(){

	/* initialize ncurses */
	
	WINDOW *win_main;
	unsigned int startx, starty, width, height;
	initscr();
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

	size_t entity_list_size_init = 20;	
	size_t entity_list_size_position = entity_list_size_init;
	size_t entity_list_size_draw = entity_list_size_init;
	size_t entity_list_size_stats = entity_list_size_init;

	unsigned int next_entity_id = 1;
		
	entity_list_position = malloc(sizeof (*entity_list_position) * entity_list_size_position);	
	entity_list_draw = malloc(sizeof (*entity_list_draw) * entity_list_size_draw);	
	entity_list_stats = malloc(sizeof (*entity_list_stats) * entity_list_size_stats);	

	
	

	/* Playing around with various menu designs*/
	size_t i=0;
	unsigned int ch; 
	char list[5][7] = { "One", "Two", "Three", "Four", "Five" };
	char item[7];

	for (i = 0; i < 5; ++i){
		if (i == 0) 
			wattron(win_main, A_STANDOUT);
		else
			wattroff(win_main, A_STANDOUT);
		sprintf(item, "%-7s", list[i]);
		mvwprintw(win_main, i+1, 2, "%s", item);
	}

	wrefresh(win_main);	
	i = 0;
		

	while (( ch = wgetch(win_main)) != 'q'){
		sprintf(item, "%-7s", list[i]);
		mvwprintw(win_main, i+1, 2, "%s", item);

		switch(ch) {
			case KEY_UP:
				--i;
				i = (1<0) ? 4:i;
				break;
			case KEY_DOWN:
				++i;
				i = (i>4) ? 0:i;
				break;
		}
		wattron(win_main,A_STANDOUT);
		sprintf(item, "%-7s", list[i]);
		mvwprintw(win_main, i+1, 2, "%s", item);
		wattroff(win_main, A_STANDOUT);
	}
	
	//free all dynamically allocated memory
	free(entity_list_position);
	free(entity_list_draw);
	free(entity_list_stats);
	delwin(win_main);
	endwin();

	return 0;
}
