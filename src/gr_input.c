#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#include <unistd.h>
#include "../include/gr_input.h"

void gr_input_init(InputData *i){
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
};

void gr_input_file_get_custom_values(InputData *i){
	char tag[15];
	int value;
	//if(access("../settings.txt", F_OK|R_OK) == 0){
		FILE *fp;
		fp = fopen("settings.txt", "r");
		//while(fscanf(fp, "%s %d", tag, &value) != EOF){
			fscanf(fp, "%s %d", tag, &value);
			//if(strcmp(tag, "up") == 0) i->up = value;
			//else if(strcmp(tag,"down") == 0) i->down = value;
			//else if(strcmp(tag,"left") == 0) i->left = value;
			//else if(strcmp(tag,"right") == 0) i->right = value;
			//else if(strcmp(tag,"up_right") == 0) i->up_right = value;
			//else if(strcmp(tag,"up_left") == 0) i->up_left = value;
			//else if(strcmp(tag,"down_right") == 0) i->down_right = value;
			//else if(strcmp(tag,"down_left") == 0) i->down_left = value;
			//else if(strcmp(tag,"inventory") == 0) i->inventory = value;
			//else if(strcmp(tag,"select") == 0) i->select = value;
			//else if(strcmp(tag,"back") == 0) i->back = value;
		//}
			fclose(fp);
	//}
}

