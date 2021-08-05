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


void system_menu(WINDOW *w, ComponentMenuOption *menu_list, size_t menu_list_length, ComponentPosition *position_list, size_t position_list_length, int input, unsigned int *game_state){

	if(input == KEY_UP || input == KEY_DOWN){

		unsigned int deselected;
		unsigned int down_selected = 99;
		unsigned int up_selected = 99;
		/* search for menu option to unhighlight */
		for (size_t i = 0; i < menu_list_length; i++){
			if(menu_list[i].game_state == *game_state && menu_list[i].id != 0){
				if(menu_list[i].highlighted == 1){
					deselected = i;
					break;
				}
			}	
		}

		/* search for new highlighted menu option */
		for (int j = menu_list_length; j > -1;  j--){
			if(menu_list[j].game_state == *game_state && menu_list[j].id != 0){
				if(j > deselected) down_selected = j;
				if(j < deselected) up_selected = j;	
			}	
		}
		
		if(input == KEY_UP){
			if(up_selected != 99){
			   	menu_list[up_selected].highlighted = 1;
				menu_list[deselected].highlighted = 0;
			}
			//else menu_list[down_selected].highlighted = 1;
		}
		else if(input == KEY_DOWN){
			if(down_selected != 99) {
				menu_list[down_selected].highlighted = 1;
				menu_list[deselected].highlighted = 0;
			}
			//else menu_list[up_selected].highlighted = 1;
		}
	}

	unsigned int target_id;
	/* search menu entities for matching game_state */
	for(size_t k = 0; k < menu_list_length; k++){
		if( menu_list[k].game_state == *game_state){
			target_id = menu_list[k].id;

			/* once a match is found, look for corresponding position */
			for(size_t jj = 0; jj < position_list_length; jj++){
				if(position_list[jj].id == target_id){
					if(menu_list[k].highlighted == 1) wattron(w,A_REVERSE);
					mvwprintw(w,position_list[jj].y,position_list[jj].x,"%s", menu_list[k].name);
				//	wrefresh(w);
					wattroff(w,A_REVERSE);
				}
			}
		}	
	}
}	




