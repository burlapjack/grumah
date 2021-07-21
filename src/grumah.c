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


	Entity ent;
	//Initialize Components
	
	wrefresh(stdscr);	
	entity_list_expand_draw(ent.list_draw,0,10);

	for(int i=0; i < 9; ++i){
		printw("\n draw id: %d\n",ent.list_draw[i]);
	}

	wrefresh(stdscr);	
	

	getch();


	endwin();
	return 0;
}



