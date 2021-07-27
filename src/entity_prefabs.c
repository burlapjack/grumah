/* entity_prefabs.c
 * by burlapjack 2021
 * These functions help automate the 
 * creation of specific entities 
 */

#include <stdlib.h>
#include "../include/component.h"
#include "../include/entity.h"


void entity_prefab_create_player(unsigned int id, int x, int y, ComponentPosition **cp, size_t *cp_list_size,ComponentDraw **cd,size_t *cd_list_size, ComponentStats **cs,size_t *cs_list_size){
	entity_add_component_position( cp, cp_list_size, id, x, y); 		
	entity_add_component_draw( cd, cd_list_size, id, 1, '@');
	entity_add_component_stats(cs, cs_list_size, id, 5, 5, 5, 5);
}


