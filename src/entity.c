//entity.c
//Functions that manipulate entity lists
//by burlapjack 2021

#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include "../include/component.h"
#include "../include/entity.h"
#include "../include/system.h"

void entity_add_player(Component *c, unsigned int id, int x, int y){
	component_add_position(c, id, x, y);		
	component_add_draw(c, id, 1, 1,'@');
	component_add_stats(c, id, 5, 5, 5, 5);
}

void entity_add_title_menu(Component *c, unsigned int *id){
	component_add_menu_option(c, *id, "Start New Game", 1, 1);
	component_add_position(c, *id, 33, 16);
	*id = *id + 1;	
	component_add_menu_option(c, *id, "Exit Game", 1, 0);
	component_add_position(c, *id, 35, 17);
	
}

