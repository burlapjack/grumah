/*system.h
 * by burlapjack 2021
 *
 */

#include "../include/map.h"

#ifndef SYSTEM_H
#define SYSTEM_H

void system_input(WINDOW *win);

void system_menu(WINDOW *w, Component *c, int *menu_visible, int input);

void system_draw_map(WINDOW *w, MapData *m, int x_offset, int y_offset);

void system_draw_layer(WINDOW *w,Component *c, int draw_layer, int x_offset, int y_offset);

#endif /*SYSTEM_H*/
