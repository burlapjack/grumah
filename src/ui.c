/* ui.c
 * by burlapjack 2021
 * user interface configurations
 */

#include <ncurses.h>
#include <stdarg.h>
#include "../include/component.h"
#include "../include/ui.h"


const char UI_TITLE[12][61] = {
	{'b','b','b','b','a','a','a','a','b','b','a','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','a','a','b','b','b','b','b','b'},
	{'b','b','a','a','b','b','b','b','a','a','a','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','a','a','a','b','b','b','b','b','b'},
	{'b','a','a','b','b','b','b','b','b','a','a','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','a','a','b','b','b','b','b','b'},
	{'b','a','b','b','b','b','b','b','b','b','a','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','a','a','b','b','b','b','b','b'},
	{'a','a','b','b','b','b','b','b','b','b','b','b','b','b','a','a','b','a','a','b','a','a','a','b','b','a','a','a','b','b','b','a','a','b','a','a','a','b','b','a','a','a','b','b','b','b','a','a','a','a','b','b','b','a','a','b','a','a','a','b','b'},
	{'a','a','b','b','b','b','b','a','a','a','a','a','b','a','a','a','a','b','a','b','b','a','a','b','b','b','a','a','b','b','a','a','a','a','b','b','a','a','a','b','b','a','a','b','b','a','a','b','b','a','a','b','b','a','a','a','b','b','a','a','b'},
	{'a','a','b','b','b','b','b','b','b','a','a','b','b','b','a','a','b','b','b','b','b','a','a','b','b','b','a','a','b','b','b','a','a','b','b','b','a','a','b','b','b','a','a','b','b','a','a','b','b','a','a','b','b','a','a','b','b','b','a','a','b'},
	{'a','a','b','b','b','b','b','b','b','a','a','b','b','b','a','a','b','b','b','b','b','a','a','b','b','b','a','a','b','b','b','a','a','b','b','b','a','a','b','b','b','a','a','b','b','b','b','b','a','a','a','b','b','a','a','b','b','b','a','a','b'},
	{'a','a','a','b','b','b','b','b','b','a','a','b','b','b','a','a','b','b','b','b','b','a','a','b','b','b','a','a','b','b','b','a','a','b','b','b','a','a','b','b','b','a','a','b','b','b','a','a','b','a','a','b','b','a','a','b','b','b','a','a','b'},
	{'b','a','a','b','b','b','b','b','b','a','a','b','b','b','a','a','b','b','b','b','b','a','a','b','b','b','a','a','b','b','b','a','a','b','b','b','a','a','b','b','b','a','a','b','b','a','a','b','b','a','a','b','b','a','a','b','b','b','a','a','b'},
	{'b','b','a','a','a','b','b','b','b','a','a','b','b','b','a','a','b','b','b','b','b','a','a','b','b','a','a','a','a','b','b','a','a','b','b','b','a','a','b','b','b','a','a','b','b','a','a','b','b','a','a','b','b','a','a','b','b','b','a','a','b'},
	{'b','b','b','b','a','a','a','a','a','a','b','b','b','a','a','a','a','b','b','b','b','b','a','a','a','b','a','a','b','b','a','a','a','a','b','a','a','a','a','b','a','a','a','a','b','a','a','a','a','a','a','b','a','a','a','a','b','a','a','a','a'}
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

void ui_menu_draw_title(WINDOW *w, UiMenu *m, int *input, int *game_loop_run){

	/* menu logic */
	switch(*input){
		case KEY_DOWN:
			if (m->highlighted == 0) {
				m->highlighted = 1;
				//wrefresh(w);
			}
			break;

		case KEY_UP:
			if (m->highlighted == 1){
			   	m->highlighted = 0;
				//wrefresh(w);
			}
			break;	

		case ' ':
			if (m->highlighted == 1){
				*game_loop_run = 0;	
			}
			break;
	}
	/* Draw the menu */

	wattron(w,A_BOLD); 
	wattron(w,A_ALTCHARSET); 
	for(int i = 0; i < 12; ++i){
		for(int j = 0; j < 61; ++j){
			if(UI_TITLE[i][j] == 1){
				mvwaddch(w,m->y+i,m->x+j,ACS_CKBOARD);
			}	
		}
	}

	wattroff(w,A_ALTCHARSET); 
	wattroff(w,A_BOLD); 

/*
	wattron(w,A_BOLD); 
	mvwprintw(w,   m->y, m->x,  "    ####  #                                          ##");
	mvwprintw(w,   m->y+1, m->x,"  ##    ###                                         ###");
	mvwprintw(w,   m->y+2, m->x," ##      ##                                          ##");
	mvwprintw(w,   m->y+3, m->x," #        #                                          ##");  
	mvwprintw(w,   m->y+4, m->x,"##            ## ## ###  ###   ## ###  ###    ####   ## ###");
	mvwprintw(w,   m->y+5, m->x,"##     ##### #### #  ##   ##  ####  ###  ##  ##  ##  ###  ##");
	mvwprintw(w,   m->y+6, m->x,"##       ##   ##     ##   ##   ##   ##   ##  ##  ##  ##   ##");
	mvwprintw(w,   m->y+7, m->x,"##       ##   ##     ##   ##   ##   ##   ##     ###  ##   ##");
	mvwprintw(w,   m->y+8, m->x,"###      ##   ##     ##   ##   ##   ##   ##   ## ##  ##   ##");
	mvwprintw(w,   m->y+9, m->x," ##      ##   ##     ##   ##   ##   ##   ##  ##  ##  ##   ##");
	mvwprintw(w,  m->y+10, m->x,"  ###    ##   ##     ##  ####  ##   ##   ##  ##  ##  ##   ##");
	mvwprintw(w,  m->y+11, m->x,"    ######   ####     ### ##  #### #### #### ###### #### ####");
	wrefresh(w);
	wattroff(w,A_BOLD); 
*/
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
	mvwprintw(w, m->y+20, m->x+12, "Use arrow keys and spacebar to select"); 
	wrefresh(w);
}




void ui_draw_menu_character_creation(WINDOW *w, UiMenu *m, int *input, int *game_loop_run){

	mvwprintw(w, m->y, m->x+1, "Create your character.");
	mvwprintw(w, m->y+3, m->x+1, "What is your name?");
	mvwprintw(w, m->y+4, m->x+1, "Choose your race.");
	mvwprintw(w, m->y+5, m->x+1, "Choose your sex.");
	mvwprintw(w, m->y+6, m->x+1, "Choose your class.");
	wrefresh(w);

}
