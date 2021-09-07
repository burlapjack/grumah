/*system.h
 * by burlapjack 2021
 *
 */


#ifndef SYSTEM_H
#define SYSTEM_H

void system_input(WINDOW *win);

void system_menu(WINDOW *w, Component *c, unsigned int *menu_visible, int input);

void system_draw_layer(WINDOW *w,Component *c, unsigned int draw_layer, int x_offset, int y_offset);

#endif /*SYSTEM_H*/
