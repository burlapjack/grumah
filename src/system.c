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
	unsigned int target_id;
	/* search menu entities for matching game_state */
	for(int i = 0; i < menu_list_length; ++i){
		if( menu_list[i].game_state == *game_state){
			target_id = menu_list[i].game_state;
			/* once a match is found, look for corresponding position */
			for(int j = 0; j < position_list_length; ++j){
				if(position_list[j].id == target_id){
					mvwprintw(w,position_list[j].y,position_list[j].x,"Menu Option 1");
					mvwprintw(w, 5,5, "%u",position_list[j].y);
					wrefresh(w);
				}
			}
		}	
	}
}	




