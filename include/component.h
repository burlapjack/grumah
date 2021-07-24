// component.h
// declares component types
// by burlapjack 2021

#ifndef COMPONENT_H
#define COMPONENT_H

typedef struct{
	int id;
	int x,y;
}ComponentPosition;

typedef struct{
	int id;
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

typedef struct{
	int id;
	char name[25];
	char description[100];
	int value;
	int weight;
}ComponentItem;

#endif /*COMPONENT_H*/
