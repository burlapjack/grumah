/* ui.c
 * by burlapjack 2021
 * user interface configurations
 */ 
#include <ncurses.h>
#include <stdarg.h>
#include <string.h>
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
	strcpy(m.options[0].name,"New Game");
	strcpy(m.options[1].name,"Exit");
	m.options[0].x = x + 24;
	m.options[0].y = y + 14;
	m.options[1].x = x+26;
	m.options[1].y = y+15;
	return m;
}

UiMenu ui_menu_create_char_creation(unsigned int x, unsigned int y){

	UiMenu m;
	m.x = x;
	m.y = y;
	m.highlighted = 0;
	m.options_length = 5;
	strcpy(m.options[0].name,"Create Your Character");
	strcpy(m.options[1].name,"What is your name?");
	strcpy(m.options[2].name,"Choose your race.");
	strcpy(m.options[3].name,"Choose your class.");
	strcpy(m.options[4].name,"Choose your sex.");

	m.options[0].x = x + 1;
	m.options[0].y = y;
	m.options[1].x = x + 1;
	m.options[1].y = y + 3;
	m.options[2].x = x + 1;
	m.options[2].y = y + 4;
	m.options[3].x = x + 1;
	m.options[3].y = y + 5;
	m.options[4].x = x + 1;
	m.options[4].y = y + 6;
	return m;
}


void ui_menu_draw(WINDOW *w, UiMenu *m, int *input, unsigned int *game_loop_run, unsigned int *game_state){

	/* --------------GAMESTATE 0: TITLE SCREEN--------------------------------------*/	
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
		mvwprintw(w, m->y+20, m->x+7, "Use arrow keys to navigate and spacebar to select"); 
	}


	for(size_t i = 0; i < m->options_length; i++){
		if(m->highlighted == i) {wattron(w, A_REVERSE);}	
		mvwprintw(w, m->options[i].y, m->options[i].x, m->options[i].name);
		wattroff(w, A_REVERSE);
	}

	
	/*------------------MENU LOGIC----------------------------------------------------*/

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
