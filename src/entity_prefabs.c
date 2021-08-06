/* entity_prefabs.c
 * by burlapjack 2021
 * These functions help automate the 
 * creation of specific entities 
 */

#include <stdlib.h>
#include <string.h>
#include "../include/component.h"
#include "../include/entity.h"
#include "../include/entity_prefabs.h"


void entity_prefab_create_player(unsigned int id, int x, int y, ComponentPosition **cp, size_t *cp_list_size,ComponentDraw **cd,size_t *cd_list_size, ComponentStats **cs,size_t *cs_list_size){
	entity_add_component_position( cp, cp_list_size, id, x, y); 		
	entity_add_component_draw( cd, cd_list_size, id, 1, '@');
	entity_add_component_stats(cs, cs_list_size, id, 5, 5, 5, 5);
}
	
void entity_prefab_create_title_menu(unsigned int *id, ComponentMenuOption **cmo, size_t *cmo_list_size, ComponentPosition **cp, size_t *cp_list_size){
	entity_add_component_menu_option(cmo, cmo_list_size,*id,"Start New Game",1,1);
	entity_add_component_position(cp, cp_list_size, *id, 33, 16);
	*id = *id + 1;
	entity_add_component_menu_option(cmo, cmo_list_size,*id,"Exit Game",1,0);
	entity_add_component_position(cp, cp_list_size, *id, 35, 17);
}
