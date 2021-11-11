#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
//#include <unistd.h>
#include "../include/gr_input.h"


extern void gr_input_init(InputData *i){
	/* set default values */
	i->up          = 'k';
	i->down        = 'j';
	i->left        = 'h';
	i->right       = 'l';
	i->up_right    = 'u';
	i->up_left     = 'y';
	i->down_right  = 'n';
	i->down_left   = 'b';
	i->inventory   = 'i';
	i->select      = KEY_ENTER;
	i->back        = KEY_BACKSPACE;
	gr_input_file_get_custom_values(i); /* retrieve customized controls from settings.txt */
}

extern void gr_input_free(InputData *in){
	free(in);
}

static void gr_input_file_get_custom_values(InputData *i){
	char tag[10];
	int value;
	FILE *fp;
	fp = fopen("../settings.txt", "r");
	if(fp != NULL){
		fscanf(fp, "%s%d", tag, &value);
		if(strcmp("up", tag) == 0){
			i->up = value;
		}
		fclose(fp);
	}
	else{
		printf("unable to open file\n");
	}
}

