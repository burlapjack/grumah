// grumah.c
// by burlapjack 2021


#include <stdlib.h>
#include <ncurses.h>
#include <stdint.h>
#include "../include/component.h"
#include "../include/entity.h"

#define COUNT_OF(x) ((sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x]))))



int main(){

	//initialize ncurses
	
	cbreak();
	keypad(stdscr,TRUE);
	curs_set(0);
	initscr();

	ComponentPosition *c_position;	
	ComponentDraw *c_draw;
	ComponentStats *c_stats;	


	c_position = malloc(sizeof (c_position) * 10);
	c_draw = malloc(sizeof (c_position) * 10);
	c_stats = malloc(sizeof (c_position) * 10);


	getch();


	endwin();
	return 0;
}
