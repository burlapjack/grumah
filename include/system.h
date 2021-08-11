/*system.h
 * by burlapjack 2021
 *
 */


#ifndef SYSTEM_H
#define SYSTEM_H

void system_input(WINDOW *win);

void system_menu(WINDOW *w, ComponentMenuOption *menu_list, unsigned int menu_list_length, ComponentPosition *position_list, unsigned int position_list_length, int input, unsigned int *game_state);

#endif /*SYSTEM_H*/
