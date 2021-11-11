/*system.h
 * by burlapjack 2021
 *
 */

#include "../include/gr_map.h"

#ifndef SYSTEM_H
#define SYSTEM_H

extern void gr_system_menu(WINDOW *w, Component *c, int *menu_visible, int input);

extern void gr_system_draw_map(WINDOW *w, MapData *m, Component *c);

extern void gr_system_draw_layer(WINDOW *w,Component *c, int draw_layer, int x_offset, int y_offset);

#endif /*SYSTEM_H*/
