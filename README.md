# Grumah

Text\-based rogue\-like engine written in C
for the Linux terminal.

## Features
[![License](https://img.shields.io/github/license/burlapjack/grumah)](https://github.com/burlapjack/grumah/blob/master/LICENSE)
![GitHub code size in bytes](https://img.shields.io/github/languages/code-size/burlapjack/grumah)

- This engine utilizes a simple ECS (Entity Component System) 
approach that is popular in many other game engines. 

- Careful memory management  is handled automatically, allowing 
users to focus more on content rather than construction. 

- All type and function names are extra descriptive for 
confusion\-free, human\-readable code. 


## Prerequisites

- **Ncurses:** This build was tested using Ncurses 6.0. 
## Short Summary
Grumah defines an *Entity* (aka game object), as nothing more than
an id number.  A *Component* is merely an attribute with an
entity id number assigned to it.  A *System* is a function that 
continually passes in components during runtime; they manipulate 
component values as required.

Within the Grumah libraries are the entity, component and system
modules.  The component module contains the definitions of each
component type such as ComponentPosition and ComponentDraw.  The
entity module contains helpful functions that create various common 
entities such as a default player entity or a menu entity.  Lastly,
the system module contains the functions that are run in the 
game-loop such as gr\_system\_menu and gr\_system\_draw\_map. 

## Getting Started

In your project directory that also contains the grumah directory, 
create a new main.c file that contains \#include for ncurses and 
grumah. Make sure to initialize ncurses so that you have a proper 
window to work with.  If you are using Linux, good chances are you 
have a recent version of ncurses installed already.

```c
/* main.c */

#include <ncurses.h>
#include "../include/grumah.h"

int main(int argc, char *argv[]){
	
	int win_width = 80;
	int win_height = 24;
	unsigned int game_running = 1;
	
	/*----- ncurses boilerplate-------------*/
	initscr();
	cbreak();
	keypad(stdscr, TRUE);					
	noecho();
	curs_set(0);
	WINDOW *win = newwin(win_height, win_width, 0, 0);	

	/*----- game loop ----------------------*/
	while(game_running == 1){
		//game code will here.
	}

	/*----- game over ----------------------*/
	/*----- free ncurses from memory -------*/
	delwin(win);
	endwin();
	return 0;
}
```
Next, you will want to set up an entity id counter and a 
Component object pointer inside your main function.

```c
/*----- entity id counter --------------*/
int next_entity = 1;

/*----- Initialize a Component Object --*/
int num_components = 10;
Component *c = malloc(sizeof (*c));
gr_component_init(c, num_components);

```
Component *c is a pointer to a struct that holds all the different kinds of
components that will be needed.  You will be using this pointer a lot.

You can use the component\_free\_all function to deallocate all of that 
memory when the program ends:

```c
gr_component_free_all(c);
```
