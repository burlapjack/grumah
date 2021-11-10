//entity.h
//by burlapjack 2021


#ifndef ENTITY_H
#define ENTITY_H
extern int gr_entity_add_actor(Component *c, MapData * m, int x, int y, char symbol);
extern int  gr_entity_add_player(Component *c, int x, int y);             /* Adds a new player entity.  Returns entity id number. */
//void gr_entity_set_location(Component *c, int id, int x, int y);   /* Sets new x and y coordinate given the entity id. */
#endif /*ENTITY_H*/
