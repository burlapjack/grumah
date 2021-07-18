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

	Entities ents;
	entity_add_position_component(&ents,1,3,5);
	entity_add_draw_component(&ents,1,0,0,1,'@');
	entity_add_stats_component(&ents,1,5,3,5,7);
	printw("\nentity 1 x= %d, y = %d\n",ents.position[1].x, ents.position[1].y);



	getch();


	endwin();
	return 0;
}
