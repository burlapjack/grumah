//entity.c
//Functions that manipulate entity lists
//by burlapjack 2021

#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include "../include/component.h"
#include "../include/entity.h"
#include "../include/system.h"

void entity_add_player(unsigned int id, int x, int y, ComponentPosition **cp, unsigned int *cp_list_size, ComponentDraw **cd,unsigned int *cd_list_size, ComponentStats **cs,unsigned int *cs_list_size){
	component_list_add_position(cp, cp_list_size, id, x, y); 		
	component_list_add_draw(cd, cd_list_size, id, 1, '@');
	component_list_add_stats(cs, cs_list_size, id, 5, 5, 5, 5);
}
	
void entity_add_title_menu(unsigned int *id, ComponentMenuOption **cmo, unsigned int *cmo_list_size, ComponentPosition **cp, unsigned int *cp_list_size){
	component_list_add_menu_option(cmo, cmo_list_size,*id,"Start New Game",1,1);
	component_list_add_position(cp, cp_list_size, *id, 33, 16);
	*id = *id + 1;
	component_list_add_menu_option(cmo, cmo_list_size,*id,"Exit Game",1,0);
	component_list_add_position(cp, cp_list_size, *id, 35, 17);
}

//Experimental 

void entity_add_plyr(Component *c, unsigned int id, unsigned int x, unsigned int y){
	component_add_position(c, id, x, y);		
	component_add_draw(c, id, 1, '@');
	component_add_stats(c, id, 5, 5, 5, 5);
}

void entity_add_title_mnu(Component *c, unsigned int *id){
	component_add_menu_option(c, *id, "Start New Game", 1, 1);
	component_add_position(c, *id, 33, 16);
	*id = *id + 1;	
	component_add_menu_option(c, *id, "Exit Game", 1, 0);
	component_add_position(c, *id, 35, 17);
	
}
