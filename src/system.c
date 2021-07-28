/* system.c
 * by burlapjack 2021
 *
 * System functions run continuously, 
 * taking in entity components.
 */

#include <stdlib.h>
#include <ncurses.h>
#include "../include/component.h"

void system_input(WINDOW *win){

	int ch = wgetch(win);
	switch(ch)
	{
		case KEY_UP:
			wprintw(win,"Up key has been pressed");
			break;
		case KEY_DOWN:
			break;
		case KEY_LEFT:
			break;
		case KEY_RIGHT:
			break;
		default:
			break;

	}
	wgetch(win);

}

void system_draw_menu(ComponentMenu* c){
	
}

	




