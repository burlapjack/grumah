/* ui.c
 * by burlapjack 2021
 * user interface configurations
 */

#include <ncurses.h>
#include <stdarg.h>
#include "../include/component.h"
#include "../include/ui.h"

void ui_start_menu_draw(WINDOW *w, UiMenu *m, int input){

	switch(input){
		case KEY_LEFT:
		case KEY_RIGHT:
			if (m->highlighted == 0) m->highlighted = 1;
			else if (m->highlighted == 1) m->highlighted = 0;
			break;	
	}
	if (m->highlighted == 0){
		attron(A_REVERSE);
		mvwprintw(w, m->x, m->y, "Start New Game"); 
		attroff(A_REVERSE);
		mvwprintw(w, m->x, m->y+1, "Exit");
	} 
	else {
		mvwprintw(w, m->x, m->y, "Start New Game"); 
		attron(A_REVERSE);
		mvwprintw(w, m->x, m->y+1, "Exit");
		attroff(A_REVERSE);
	}

}






