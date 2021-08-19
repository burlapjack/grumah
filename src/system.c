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



//void system_menu(WINDOW *w, ComponentMenuOption *menu_list, unsigned int menu_list_length, ComponentPosition *position_list, unsigned int position_list_length, int input, unsigned int *game_state);

void system_menu(WINDOW *w, Component *c, unsigned int *game_state, int input){

	if(input == KEY_UP || input == KEY_DOWN){

		unsigned int deselected;
		unsigned int down_selected = 99;
		unsigned int up_selected = 99;

		/* search for menu option to unhighlight */
		for (int i = 0; i < (c->size_menu_option); i++){
			if(c->menu_option[i].parent_id == *game_state && c->menu_option[i].id != 0){
				if(c->menu_option[i].highlighted == 1){
					deselected = i;
					break;
				}
			}	
		}

		/* search for menu options that are adjacent to the 
		 * currently highlighted  menu option */
		for (int j = c->size_menu_option; j > -1;  j--){
			if(c->menu_option[j].parent_id == *game_state && c->menu_option[j].id != 0){
				if(j > deselected && j < c->size_menu_option) down_selected = j;
				if(j < deselected  ) up_selected = j;	
			}	
		}
		
		if(input == KEY_UP){
			if(up_selected != 99){
			   	c->menu_option[up_selected].highlighted = 1;
				c->menu_option[deselected].highlighted = 0;
			}
			//else menu_list[down_selected].highlighted = 1;
		}
		else if(input == KEY_DOWN){
			if(down_selected != 99) {
				c->menu_option[down_selected].highlighted = 1;
				c->menu_option[deselected].highlighted = 0;
			}
			//else menu_list[up_selected].highlighted = 1;
		}
	}

	unsigned int target_id;
	/* search menu entities for matching game_state */
	for(int k = 0; k < c->size_menu_option; k++){
		if( c->menu_option[k].parent_id == *game_state){
			target_id = c->menu_option[k].id;

			/* once a match is found, look for corresponding position */
			for(int jj = 0; jj < (c->size_position); jj++){
				if(c->position[jj].id == target_id){
					if(c->menu_option[k].highlighted == 1) wattron(w,A_REVERSE);
					mvwprintw(w,c->position[jj].y,c->position[jj].x,"%s", c->menu_option[k].name);
				//	wrefresh(w);
					wattroff(w,A_REVERSE);
				}
			}
		}	
	}
}	




