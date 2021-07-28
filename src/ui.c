/* ui.c
 * by burlapjack 2021
 * user interface configurations
 */

#include <ncurses.h>
#include "../include/component.h"
#include "../include/ui.h"

char *ui_menu_main[] = {"New Game", "Exit"};
char *ui_menu_character_create[] = {"Name","Class","Race"};



void ui_menu_main_draw(WINDOW *w, int key_pressed, char *option_list, unsigned int *option_highlighted){

	switch(key_pressed){
		case KEY_UP:
		case KEY_DOWN:
			if (*option_highlighted == 0) *option_highlighted = 1;
			else if (*option_highlighted == 1) *option_highlighted = 0;
			break;
		case KEY_ENTER:
			if(*option_highlighted == 0){
				
			}
			else if( *option_highlighted == 1){

			}
	}
	
};




