/* ui.c
 * by burlapjack 2021
 * user interface configurations
 */

#include <ncurses.h>
#include <stdarg.h>
#include "../include/component.h"
#include "../include/ui.h"


const char UI_TITLE[12][61] = {
	{'.','.','.','.','M','M','M','M','.','.','M','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','M','M','.','.','.','.','.','.'},
	{'.','.','M','M','M','.','.','M','M','M','M','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','M','M','M','.','.','.','.','.','.'},
	{'.','M','M','.','.','.','.','.','.','M','M','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','M','M','.','.','.','.','.','.'},
	{'.','M','.','.','.','.','.','.','.','.','M','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','M','M','.','.','.','.','.','.'},
	{'M','M','.','.','.','.','.','.','.','.','.','.','.','.','M','M','.','M','M','.','M','M','M','.','.','M','M','M','.','.','.','M','M','.','M','M','M','.','.','M','M','M','.','.','.','.','M','M','M','M','.','.','.','M','M','.','M','M','M','.','.'},
	{'M','M','.','.','.','.','.','.','.','.','.','.','.','M','M','M','M','.','M','.','.','M','M','.','.','.','M','M','.','.','M','M','M','M','.','.','M','M','M','.','.','M','M','.','.','M','M','.','.','M','M','.','.','M','M','M','.','.','M','M','.'},
	{'M','M','.','.','.','.','.','M','M','M','M','M','.','.','M','M','.','.','.','.','.','M','M','.','.','.','M','M','.','.','.','M','M','.','.','.','M','M','.','.','.','M','M','.','.','M','M','.','.','M','M','.','.','M','M','.','.','.','M','M','.'},
	{'M','M','.','.','.','.','.','.','.','M','M','.','.','.','M','M','.','.','.','.','.','M','M','.','.','.','M','M','.','.','.','M','M','.','.','.','M','M','.','.','.','M','M','.','.','.','.','.','M','M','M','.','.','M','M','.','.','.','M','M','.'},
	{'M','M','M','.','.','.','.','.','.','M','M','.','.','.','M','M','.','.','.','.','.','M','M','.','.','.','M','M','.','.','.','M','M','.','.','.','M','M','.','.','.','M','M','.','.','.','M','M','.','M','M','.','.','M','M','.','.','.','M','M','.'},
	{'.','M','M','.','.','.','.','.','.','M','M','.','.','.','M','M','.','.','.','.','.','M','M','.','.','.','M','M','.','.','.','M','M','.','.','.','M','M','.','.','.','M','M','.','.','M','M','.','.','M','M','.','.','M','M','.','.','.','M','M','.'},
	{'.','.','M','M','M','.','.','.','.','M','M','.','.','.','M','M','.','.','.','.','.','M','M','.','.','M','M','M','M','.','.','M','M','.','.','.','M','M','.','.','.','M','M','.','.','M','M','.','.','M','M','.','.','M','M','.','.','.','M','M','.'},
	{'.','.','.','.','M','M','M','M','M','M','.','.','.','M','M','M','M','.','.','.','.','.','M','M','M','.','M','M','.','.','M','M','M','M','.','M','M','M','M','.','M','M','M','M','.','M','M','M','M','M','M','.','M','M','M','M','.','M','M','M','M'}
};


UiMenu ui_menu_create_title(unsigned int x, unsigned int y){

	UiMenu m;	
	m.x = x;
	m.y = y;
	m.options_length = 2;
	m.highlighted = 0;
	return m;
}

UiMenu ui_menu_create_char_creation(unsigned int x, unsigned int y){
	UiMenu m;
	m.x = x;
	m.y = y;
	m.options_length = 10;
	m.highlighted = 0;
	return m;
}


void ui_menu_draw(WINDOW *w, UiMenu *m, int *input, unsigned int *game_loop_run, unsigned int *game_state){


	if(*game_state == 0){
	/* Title Screen Graphic */
		wattron(w,A_ALTCHARSET); 
		for(int i = 0; i < 12; ++i){
			for(int j = 0; j < 61; ++j){
				if(UI_TITLE[i][j] == 'M'){
					wattron(w,A_REVERSE); 
					mvwaddch(w,m->y+i,m->x+j,' ');
					wattroff(w,A_REVERSE); 
				}	
				else if(UI_TITLE[i][j] == 'm'){
					wattron(w,A_REVERSE); 
					mvwaddch(w,m->y+i,m->x+j,ACS_CKBOARD);
					wattroff(w,A_REVERSE); 
				}
				else if(UI_TITLE[i][j] == 'n'){
					mvwaddch(w,m->y+i,m->x+j,ACS_CKBOARD);
				}
			}
		}
		wattroff(w,A_ALTCHARSET); 

		/* Draw Title Screen Menu */
		if (m->highlighted == 0){
			wattron(w, A_REVERSE);
			mvwprintw(w, m->y+14, m->x+24, "Start New Game"); 
			wattroff(w, A_REVERSE);
			mvwprintw(w, m->y+15, m->x+29, "Exit");
		} 
		else {
			mvwprintw(w, m->y+14, m->x+24, "Start New Game"); 
			wattron(w, A_REVERSE);
			mvwprintw(w, m->y+15, m->x+29, "Exit");
			wattroff(w, A_REVERSE);
		}
		mvwprintw(w, m->y+20, m->x+7, "Use arrow keys to navigate and spacebar to select"); 
	}
	/* Character creation Screen */
	else if(*game_state == 1){
		mvwprintw(w, m->y, m->x+1, "Create your character.");
		mvwprintw(w, m->y+3, m->x+1, "What is your name?");
		mvwprintw(w, m->y+4, m->x+1, "Choose your race.");
		mvwprintw(w, m->y+5, m->x+1, "Choose your sex.");
		mvwprintw(w, m->y+6, m->x+1, "Choose your class.");
	}

	
	/* menu logic */

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
