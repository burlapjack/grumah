# Grumah

Grumah is a text\-based rogue\-like engine written in C
for the Linux terminal.
## Features

-This engine utilizes a simple ECS (Entity Component System) 
approach that is popular in many other game engines. 

-Careful memory management  is handled automatically, allowing 
users to focus more on content rather than construction. 

-All type and function names are extra descriptive for 
confusion\-free, human\-readable code. 


## Prerequisites

-**Ncurses** This build was tested using Ncurses 6.0. 

## Getting Started

Grumah stores all *Entities*, or game objects, as nothing more than
lists of *Components*.  For each component added to a list,  there 
is a corresponding entity id.

For example,  the player character might
have a component for their x and y position on the map, their character 
stats, and their sprite to draw on the map.  So,  let's start by 
creating an entity counter, and some pointers that will store all of the 
necessary components:

```
unsigned int next_entity = 1;

ComponentPosition *position\_list;
ComponentStats *stats_list;
ComponentDraw *draw_list;

```

ComponentPosition, ComponentStats, and ComponentDraw are all component
types that you'll be using a lot in your games.  

Now that you have 
created your component lists,  allocate some memory space for them:

```

size_t size_cp = 20;
size_t size_cd = 20;
size_t size_cs = 20;

position_list = malloc(sizeof (*position_list) * size_cp ));
draw_list = malloc (sizeof (*draw _list )  * size_cd ));
stats_list = malloc (sizeof (*stats _list ) * size_cs));

```

Here, 20 slots for each component list has been allocated.  This means
that 20 different entities can be created using these 3 component types.

Now let's give the player entity some components: 

```

entity_add_component_position(**position_list, *size_cp, next_id, 10, 10);
entity_add_component_draw(**draw_list, *size_draw, next_id, 1, '@');
entity_add_component_stats(**stats_list, *size_draw, next_id, 100, 50, 50, 50);

```




