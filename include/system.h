/*system.h
 * by burlapjack 2021
 *
 */


#ifndef SYSTEM_H
#define SYSTEM_H

void system_input(WINDOW *win);

void system_menu(WINDOW *w, Component *c, unsigned int *menu_visible, int input);

void system_draw(WINDOW *w,Component *c, unsigned int num_draw_layers, int x_offset, int y_offset);

#endif /*SYSTEM_H*/
