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


	//Initialize Components
	ComponentPosition* entity_list_position;
	ComponentDraw* entity_list_draw;
	ComponentStats* entity_list_stats;
	
	size_t list_size_position = 20;
	size_t list_size_draw = 20;
	size_t list_size_stats = 20;

	unsigned int next_entity_id = 1;

	entity_list_position = malloc(sizeof (*entity_list_position) * list_size_position);	
	entity_list_draw = malloc(sizeof (*entity_list_draw) * list_size_draw);	
	entity_list_stats = malloc(sizeof (*entity_list_stats) * list_size_stats);	

	//Initialize Entities	
	for (int i = 0; i < 19; ++i) {
		entity_list_position[i].id = 0;
		entity_list_draw[i].id = 0;
		entity_list_stats[i].id = 0;
	}	

	wrefresh(stdscr);	

	for (int j = 0; j < 19; ++j) {
		printw(" id = %d\n", entity_list_position[j].id);
		wrefresh(stdscr);	
	}

	entity_add_component_position(entity_list_position,20, &next_entity_id,10,10);	


	getch();


	endwin();
	return 0;
}



