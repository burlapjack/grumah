/* system.c * by burlapjack 2021
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

void system_menu(WINDOW *w, Component *c, unsigned int *menu_visible, int input){

	if(input == KEY_UP || input == KEY_DOWN){
		unsigned int highlighted;

		for (unsigned int i = 0; i < (c->size_menu_option); i++){
			if(c->menu_option[i].parent_id == *menu_visible && c->menu_option[i].id != 0 && c->menu_option[i].highlighted == 1){
					highlighted= i;
					break;
			}
		}
		unsigned int new_highlighted = highlighted;
		for (unsigned int i = 0; i < c->size_menu_option; i++){
			if(c->menu_option[i].parent_id == *menu_visible && c->menu_option[i].id != 0){
				if(input == KEY_UP && i < highlighted){
					new_highlighted = i;
					break;
				}
				else if(input == KEY_DOWN && i > highlighted){
					new_highlighted = i;
					break;
				}
			}
		}
		
		c->menu_option[highlighted].highlighted = 0;
		c->menu_option[new_highlighted].highlighted = 1;
		mvwprintw(w,12, 2,"menu option: %u", new_highlighted);
	}

	unsigned int target_id;
	/* search menu entities for matching menu_visible */
	for(int k = 0; k < c->size_menu_option; k++){
		if( c->menu_option[k].parent_id == *menu_visible){
			target_id = c->menu_option[k].id;

			/* once a match is found, look for corresponding position */
			for(int jj = 0; jj < (c->size_position); jj++){
				if(c->position[jj].id == target_id){
					if(c->menu_option[k].highlighted == 1) wattron(w,A_REVERSE);
					mvwprintw(w,c->position[jj].y,c->position[jj].x,"%s", c->menu_option[k].name);
					wattroff(w,A_REVERSE);
				}
			}
		}	
	}
}	

void system_map_draw(WINDOW *w, char map[32][32], int map_width, int map_height){
	for (int i = 0; i < map_height; i++){
		for(int j = 0; j < map_width; i++){
			mvwaddch(w, i, j, map[i][j] ); 

		}
	}
}

