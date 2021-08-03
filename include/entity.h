//entity.h
//by burlapjack 2021


#ifndef ENTITY_H
#define ENTITY_H

/*------------Entity List Manipulation -----*/
void entity_list_size_double_position(ComponentPosition** entity_list, size_t *list_size);
void entity_list_size_double_draw(ComponentDraw** entity_list, size_t *list_size);
void entity_list_size_double_stats(ComponentStats** entity_list, size_t *list_size);
void entity_list_size_double_menu_option(ComponentMenuOption** entity_list, size_t *list_size);

/*------------Component creation -----------*/
 
void entity_add_component_position(ComponentPosition **entity_list, size_t *list_size, unsigned int id, unsigned int x, unsigned int y);
void entity_add_component_draw(ComponentDraw **entity_list, size_t *list_size, unsigned int id, unsigned int color, char symbol);
void entity_add_component_stats(ComponentStats **entity_list, size_t *list_size, unsigned int id, unsigned int hp, unsigned int str, unsigned int per, unsigned int agi);
void entity_add_component_menu_option(ComponentMenuOption **entity_list, size_t *list_size, unsigned int id, char name[], unsigned int game_state, unsigned int child_menu_id, unsigned int highlighted);

#endif /*ENTITY_H*/
