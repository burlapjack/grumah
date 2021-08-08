//entity.h
//by burlapjack 2021


#ifndef ENTITY_H
#define ENTITY_H


void entity_add_player(unsigned int id, int x, int y, ComponentPosition **cp, size_t *cp_list_size,ComponentDraw **cd,size_t *cd_list_size, ComponentStats **cs,size_t *cs_list_size);
	
void entity_add_title_menu(unsigned int *id, ComponentMenuOption **cmo, size_t *cmo_list_size, ComponentPosition **cp, size_t *cp_list_size);


#endif /*ENTITY_H*/
