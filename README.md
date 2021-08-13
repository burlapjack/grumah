# Grumah

Grumah is a text\-based rogue\-like engine written in C
for the Linux terminal.
## Features

- This engine utilizes a simple ECS (Entity Component System) 
approach that is popular in many other game engines. 

- Careful memory management  is handled automatically, allowing 
users to focus more on content rather than construction. 

- All type and function names are extra descriptive for 
confusion\-free, human\-readable code. 


## Prerequisites

- **Ncurses** This build was tested using Ncurses 6.0. 

## Getting Started

Grumah defines an *Entity* (aka game object), as nothing more than
an id number.  A *Component* is merely an attribute with an
entity id number assigned to it.  A *System* is a function that 
continually passes in components during runtime; they manipulate 
component values as required.

To start, you will want to set up an entity id counter, the component 
pointers and their respective sizes:

```
#include "grumah.h"

/*----- entity id counter -----*/
unsigned int next_entity = 1;

/*----- component lists -----*/
ComponentPosition *pos;
ComponentDraw *drw;
ComponentStats *sts;
ComponentMenuOption *mno;

/*------ Component list sizes ----*/
unsigned int n_pos = 20;
unsigned int n_drw = 20;
unsigned int n_sts = 20;
unsigned int n_mno = 20;

/*-------Initialize lists --------*/
void component_list_init_all(20, **pos, **drw, **sts, **cmo);

```
Here, 20 empty slots for each component list has been allocated.  This means
that 20 different components can be created using these 3 component types.

Now,  let's add a player entity:
 
```
entity_add_player(next_id, x, y, **pos, *n_pos, **drw, *n_drw, **sts, *n_sts);

```

You can use the entity\_list\_free\_all function to deallocate all of that 
memory when the program ends:

```
entity_list_free_all(*pos, *drw, *sts, *mno);

```
