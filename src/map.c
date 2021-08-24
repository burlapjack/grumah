/* map_generate.c * by burlapjack 2021
 * procedural map generation
 */

/*---------------------- Init a map that is all walls ------------------------------------------------------------------------*/
void map_generate_init(char *map[], int map_width, int map_height){
	for (unsigned int i = 0; i < map_height; i++){
		for (unsigned int j = 0; j < map_width; j++){
			map[i][j] = '#';
		}
	}
}

/*---------------------- Simple Room Placement Map Gen Algorythm -------------------------------------------------------------*/
void map_generate_srp(char *map[], int map_width, int map_height){
	/*------------ Initialize map ----------------------------*/
	map_generate_init(map, map_width, map_height);	
}
