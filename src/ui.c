/* ui.c
 * by burlapjack 2021
 * user interface configurations
 */

#include <ncurses.h>
#include "../include/component.h"
#include "../include/ui.h"

char *ui_menu_main[] = {"New Game", "Exit"};
char *ui_menu_character_create[] = {"Name","Class","Race"};

void ui_menu_main_draw(WINDOW *w,char *m){
	int ch = wgetch(w);
		
	switch(ch){
		case KEY_UP:
			break;
		case KEY_DOWN:
			break;
		default:
			break;
	}
	
};




