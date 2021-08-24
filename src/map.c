/* map_generate.c * by burlapjack 2021
 * procedural map generation
 */


void map_generate_init(char *map[], unsigned int map_width, unsigned int map_height){
	for (unsigned int i = 0; i < map_height; i++){
		for (unsigned int j = 0; j < map_width; j++){
			map[i][j] = '#';
		}
	}
}


/*---------------------- Simple Room Placement Map Gen Algorythm ------------------------------*/
void map_generate_srp(char *map[], unsigned int map_width, unsigned int map_height){
	/*------------ Initialize map ---------------------------*/
	map_generate_init(map, map_width, map_height);	

}
