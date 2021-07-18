// component.h
// by burlapjack 2021

#ifndef COMPONENT_H
#define COMPONENT_H


typedef struct{
	int id;
	int x,y;
}ComponentPosition;

typedef struct{
	int id;
	int xoffset, yoffset;
	char symbol;
	int color;
}ComponentDraw;

typedef struct{
	int id;
	int hp;
	int strength;
	int perception;
	int agility;
}ComponentStats;



#endif /*COMPONENT_H*/
