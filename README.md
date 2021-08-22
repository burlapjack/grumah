# Grumah

Grumah is a text\-based rogue\-like engine written in C
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
game-loop such as system\_menu and system\_draw\_map. 

## Getting Started

To start, you will want to set up an entity id counter and a
Component object pointer.

```c
#include "grumah.h"

/*----- entity id counter --------------*/
unsigned int next_entity = 1;


/*----- Initialize a Component Object --*/
unsigned int num_components = 10;
Component *c = malloc(sizeof (*c));
c = component_init(c, num_components);

```
Component *c is a pointer to a struct that holds all the different kinds of
components that will be needed.  We will be using this pointer a lot.

Now,  let's add a player entity:
 
```c
/*------Add player entity at x=10, y=12 --*/
entity_add_plyr(c, next_entity, 10, 12);

```

You can use the component\_free\_all function to deallocate all of that 
memory when the program ends:

```c
void component_free_all(c);

```
