//entity.c
//Functions that manipulate entity lists
//by burlapjack 2021

#include <stdlib.h>
#include "../include/gr_component.h"
#include "../include/gr_map.h"
#include "../include/gr_entity.h"

int gr_entity_add_actor(Component *c, MapData * m, int x, int y, char symbol){
	gr_component_add_position(c, x, y);
	gr_component_add_draw(c, 1, 1, symbol);
	gr_component_add_attributes(c, 0, 0, 0);
	c->next_id++;
	return c->next_id;
}

int gr_entity_add_player(Component *c, int x, int y){
	gr_component_add_position(c, x, y);
	gr_component_add_draw(c, 1, 1,'@');
	gr_component_add_attributes(c, 0, 0, 0 );
	c->next_id++;
	return c->next_id;
}

void gr_entity_set_location(Component *c, int id, int x, int y){
	for(int i = 0; i < c->size_position; i++){
		if(c->position[i].id == id){
			c->position[i].x = x;
			c->position[i].y = y;
			break;
		}
	}
}
