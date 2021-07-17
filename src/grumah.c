// grumah.c
// by burlapjack 2021


#include <stdlib.h>
#include <ncurses.h>

#define MAX_ENTITIES 100

#define COUNT_OF(x) ((sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x]))))


typedef struct component_position{
	int id;
	int x,y;
} component_position;

typedef struct component_draw{
	int id;
	int xoffset, yoffset;
	char symbol;
	int color;
} component_draw;

typedef struct component_stats{
	int id;
	int hp;
	int strength;
	int perception;
	int agility;
} component_stats;

typedef struct entities{
	component_position position[MAX_ENTITIES];
	component_draw draw[MAX_ENTITIES];
	component_stats stats[MAX_ENTITIES];
} entities;


void new_component_position(entities *e,int id, int x,int y){
	
	e->position[1].x = x;
	e->position[1].y = y;
		
}

void new_component_draw(entities *e, int id, int xoff, int yoff,int col,char sym){
	
	e->draw[1].xoffset = xoff;
	e->draw[1].yoffset = xoff;
	e->draw[1].color = col;
	e->draw[1].symbol = sym;
		
}

void new_component_stats(entities *e, int id, int hp, int str, int per, int agi){
	e->stats[1].id = id;
	e->stats[1].hp = hp;
	e->stats[1].strength = str;
	e->stats[1].perception = per;
	e->stats[1].agility = agi;
}

int main(){

	//initialize ncurses
	
	cbreak();
	keypad(stdscr,TRUE);
	curs_set(0);
	initscr();

	entities ents;
	new_component_position(&ents,1,3,5);
	new_component_draw(&ents,1,0,0,1,'@');
	new_component_stats(&ents,1,5,3,5,7);
	printw("\nentity 1 x= %d, y = %d\n",ents.position[1].x, ents.position[1].y);
	getch();


	endwin();
	return 0;
}
