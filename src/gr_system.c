/* system.c * by burlapjack 2021
 *
 * System functions run continuously,
 * taking in entity components.
 * These systems require the use of
 * the Ncurses library.
 */

#include <stdlib.h>
#include <ncurses.h>
#include "../include/gr_map.h"
#include "../include/gr_component.h"
#include "../include/gr_input.h"

/*------------------------------ Draw the map walls and rooms ------------------------------------*/
extern void gr_system_draw_map(WINDOW *w, MapData *m, Component *c){
	/*-- Will need to be edited later to accomodate colors --*/
//	for(int i = 0; i < m->map_height; i++){
//		for(int j = 0; j < m->map_width; j++){
//			mvwprintw( w, i + m->map_y_offset, j + m->map_x_offset, "%c", m->map[i * m->map_width + j] );
//		}
//	}

	for(int i = 0; i < c->size_draw; i++){
		if(c->draw[i].layer == 0 && c->draw[i].visibility > 0){
			mvwprintw(w, c->draw[i].y + m->map_y_offset, c->draw[i].x + m->map_x_offset,"%c", c->draw[i].symbol);
			/*for(int j = 0; j < c->size_position; j++){
				if(c->position[j].id == c->draw[i].id){
					mvwprintw(w, c->position[j].y + m->map_y_offset, c->position[j].x + m->map_x_offset,"%c", c->draw[i].symbol);
					break;
				}
			}*/
		}
	}
}

/*------------------------------ Draw components by layer ----------------------------------------*/
extern void gr_system_draw_layer(WINDOW *w,Component *c, int draw_layer, int x_offset, int y_offset){
	for(int i = 0; i < (c->size_draw); i++){
		if (c->draw[i].layer == draw_layer){
			mvwprintw(w,c->draw[i].y + y_offset, c->draw[i].x + x_offset,"%c",c->draw[i].symbol);
			/*for(size_t j = 0; j < c->size_position; j++){
				if ( c->position[j].id == c->draw[i].id){
					mvwprintw(w,c->position[j].y + y_offset, c->position[j].x + x_offset,"%c",c->draw[i].symbol);

				}
			}*/
		}
	}
}

extern void gr_system_input(Component *c, MapData *m, InputData *in, int key_pressed){
	for(int i = 0; i < c->size_input; i++){
		if(key_pressed == in->up || key_pressed == in->down || key_pressed == in->left || key_pressed == in->right ||
		key_pressed == in->up_right || key_pressed == in->up_left || key_pressed == in->down_right || key_pressed == in->down_left){   /* detect movement. */
			for(int j = 0; j < c->size_draw; j++){
				if(c->draw[j].id == c->input[i].id){
					c->input[i].requested == key_pressed;	
				}					
			}
		}
	}	
}

