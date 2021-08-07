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

ComponentPosition *pos_list;
ComponentStats *stats_list;
ComponentDraw *draw_list;

```

ComponentPosition, ComponentStats, and ComponentDraw are all component
types that you'll be using a lot in your games.  

Now that you have 
created your component lists,  allocate some memory space for them:

```
/*-------- List Sizes --------*/
size_t n_pos = 20;
size_t n_drw = 20;
size_t n_sts = 20;

/*--- Init Component List ----*/
pos = malloc(sizeof (*pos) * n_pos);
drw = malloc (sizeof (*draw)  * n_drw);
sts = malloc (sizeof (*sts) * n_sts);

```

Here, 20 empty slots for each component list has been allocated.  This means
that 20 different entities can be created using these 3 component types.

Now let's give the player entity some components: 

```
unsigned int x = 10;
unsigned int y = 15;
entity_add_component_pos(**pos, *n_pos, next_id, x, y);
entity_add_component_draw(**drw, *n_drw, next_id, 1, '@');
entity_add_component_stats(**sts, *n_sts, next_id, 100, 50, 50, 50);

```
We now have a player character with a position, some stats,  and a sprite.

If you don't feel like adding every component one at a time,  there is a 
player prefab function that handles all of the work for you: 
 
```
entity_prefab_create_player(next_id, x, y, **pos, *n_pos, **drw, *n_drw, **sts, *n_sts);

```
There are several prefab functions like this one at your disposal.

If you want to make your life even easier,  you can use this 
function to initialize all of the lists for you:

```
entity_list_init_all(size_t list_size, ComponentPosition **cp, ComponentDraw **cd, ComponentStats **cs, ComponentMenuOption **co);

```
And to help you out even further,  use this function to deallocate
all of that memory when the program ends:

```
entity_list_free_all(ComponentPosition *cp, ComponentDraw *cd, ComponentStats *cs, ComponentMenuOption *co);

```
