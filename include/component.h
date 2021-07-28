// component.h
// declares component types
// by burlapjack 2021

#ifndef COMPONENT_H
#define COMPONENT_H

typedef struct{
	unsigned int id;
	unsigned int x,y;
}ComponentPosition;

typedef struct{
	unsigned int id;
	char symbol;
	unsigned int color;
}ComponentDraw;

typedef struct{
	unsigned int id;
	unsigned int hp;
	unsigned int strength;
	unsigned int perception;
	unsigned int agility;
}ComponentStats;

typedef struct {
	unsigned int id;
	unsigned int key_pushed;
}ComponentInput;

typedef struct{
	unsigned int id;
	unsigned int x,y;
	unsigned int width, height;
	char *options[20];
	unsigned int options_length; 
	unsigned int highlighted;
} ComponentMenu;


#endif /*COMPONENT_H*/
