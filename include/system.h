/*system.h
 * by burlapjack 2021
 *
 */


#ifndef SYSTEM_H
#define SYSTEM_H

void system_input(WINDOW *win);

void system_menu(WINDOW *w, ComponentMenuOption *menu_list, size_t menu_list_length, ComponentPosition *position_list, size_t position_list_length, unsigned int *game_state);

#endif /*SYSTEM_H*/
