/*system.h
 * by burlapjack 2021
 *
 */


#ifndef SYSTEM_H
#define SYSTEM_H

void system_input(WINDOW *win);

void system_menu(WINDOW *w, Component *c, unsigned int *menu_visible, int input);

void system_map_draw(WINDOW *w, char **map, int map_width, int map_height, int x_offset, int y_offset);

#endif /*SYSTEM_H*/
