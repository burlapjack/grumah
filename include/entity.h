//entity.h
//by burlapjack 2021


#ifndef ENTITY_H
#define ENTITY_H

void entity_add_player(unsigned int id, int x, int y, ComponentPosition **cp, unsigned int *cp_list_size,ComponentDraw **cd,unsigned int *cd_list_size, ComponentStats **cs,unsigned int *cs_list_size);
void entity_add_title_menu(unsigned int *id, ComponentMenuOption **cmo, unsigned int *cmo_list_size, ComponentPosition **cp, unsigned int *cp_list_size);


void entity_add_plyr(Component *c, unsigned int id, unsigned int x, unsigned int y);
void entity_add_title_mnu(Component *c, unsigned int *id);

#endif /*ENTITY_H*/
