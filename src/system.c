/* system.c * by burlapjack 2021
 *
 * System functions run continuously,
 * taking in entity components.
 * These systems require the use of
 * the Ncurses library.
 */

#include <stdlib.h>
#include <ncurses.h>
#include "../include/map.h"
#include "../include/component.h"


void system_input(WINDOW *win){

	int ch = wgetch(win);
	switch(ch)
	{
		case KEY_UP:
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

/*------------------------------ Draw the map walls and rooms ------------------------------------*/
void system_draw_map(WINDOW *w, MapData *m, Component *c){
	/*-- Will need to be edited later to accomodate colors --*/
//	for(int i = 0; i < m->map_height; i++){
//		for(int j = 0; j < m->map_width; j++){
//			mvwprintw( w, i + m->map_y_offset, j + m->map_x_offset, "%c", m->map[i * m->map_width + j] );
//		}
//	}

	for(int i = 0; i < c->size_draw; i++){
		if(c->draw[i].layer == 0 && c->draw[i].visibility > 0){
			for(int j = 0; j < c->size_position; j++){
				if(c->position[j].id == c->draw[i].id){
					mvwprintw(w, c->position[j].y + m->map_y_offset, c->position[j].x + m->map_x_offset,"%c", c->draw[i].symbol);
					break;
				}
			}
		}
	}
}

/*------------------------------ Draw components by layer ----------------------------------------*/
void system_draw_layer(WINDOW *w,Component *c, int draw_layer, int x_offset, int y_offset){
	for(size_t i = 0; i < (c->size_draw); i++){
		if (c->draw[i].layer == draw_layer){
			for(size_t j = 0; j < c->size_position; j++){
				if ( c->position[j].id == c->draw[i].id){
					mvwprintw(w,c->position[j].y + y_offset, c->position[j].x + x_offset,"%c",c->draw[i].symbol);

				}
			}
		}
	}
}



