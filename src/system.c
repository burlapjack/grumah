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


void system_menu(WINDOW *w, ComponentMenuOption *menu_list, size_t menu_list_length, ComponentPosition *position_list, size_t position_list_length, unsigned int *game_state){
	unsigned int x, y;
	unsigned int target_id;
	for(int i = 0; i < menu_list_length; ++i){
		
		if( menu_list[i].game_state == *game_state){
			target_id = menu_list[i].game_state;
		}	
	}
}	




