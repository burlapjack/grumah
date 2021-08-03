/* ui.c
 * by burlapjack 2021
 * user interface configurations
 */ 
#include <ncurses.h>
#include <string.h>
#include "../include/component.h"
#include "../include/ui.h"


UiMenu ui_menu_create_title(unsigned int x, unsigned int y){

	UiMenu m;	
	m.x = x;
	m.y = y;
	m.options_length = 2;
	m.highlighted = 0;
	strcpy(m.options[0].name,"New Game");
	strcpy(m.options[1].name,"Exit");
	return m;
}


void ui_menu_draw(WINDOW *w, UiMenu *m, int *input, unsigned int *game_loop_run, unsigned int *game_state){


	/*-----------------DRAW MENU--------------------------------------------------*/
	for(size_t i = 0; i < m->options_length; i++){
		if(m->highlighted == i) {wattron(w, A_REVERSE);}	
		mvwprintw(w, m->options[i].y, m->options[i].x, m->options[i].name);
		wattroff(w, A_REVERSE);
	}

	
	/*------------------MENU INPUT----------------------------------------------------*/
	
	switch(*input){
		case KEY_DOWN:
			if (m->highlighted == m->options_length-1) 
				m->highlighted = 0; 
			else 
				m->highlighted ++;
			break;

		case KEY_UP:
			if (m->highlighted == 0)
			   	m->highlighted = m->options_length-1;
			else
				m->highlighted --;	
			break;	

		case ' ': /* Spacebar: making selection */
			
			/* Title Screen */
			if(*game_state == 0){
				if (m->highlighted == 0){
					*game_state = 1;
					wclear(w);
					wrefresh(w);
					refresh();
					box(w,0,0);
				}
				else if (m->highlighted == 1) *game_loop_run = 0;	

			}else if(*game_state == 1){
				*game_state = 0;			
				wclear(w);
				wrefresh(w);
				refresh();
				box(w,0,0);
			}
			break;

		}
		wrefresh(w);
}
