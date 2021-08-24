/*system.h
 * by burlapjack 2021
 *
 */


#ifndef SYSTEM_H
#define SYSTEM_H

void system_input(WINDOW *win);

void system_menu(WINDOW *w, Component *c, unsigned int *menu_visible, int input);

void system_map_draw(WINDOW *w, char *map, unsigned int map_width, unsigned int map_height);

#endif /*SYSTEM_H*/
