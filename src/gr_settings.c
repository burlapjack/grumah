#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#include "../include/gr_settings.h"


extern void gr_settings_init(SettingsData *s){
	/* set default values */
	s->up          = 'k';
	s->down        = 'j';
	s->left        = 'h';
	s->right       = 'l';
	s->up_right    = 'u';
	s->up_left     = 'y';
	s->down_right  = 'n';
	s->down_left   = 'b';
	s->inventory   = 'i';
	s->select      = KEY_ENTER;
	s->back        = KEY_BACKSPACE;

	//fp = fopen("settings.txt", "a+");
	//fclose(fp);
}

extern void
gr_settings_free(SettingsData *s)
{
	free(s);
}

extern char* 
gr_settings_read_string(FILE *file, char const *desired_tag)
{
	char tag[64];
	char val[64];
	while (fscanf(file, "%63[^=]=%63[^\n]%*c", tag, val) == 2) {
		if (0 == strcmp(tag, desired_tag)) {
			return strdup(val);
		}
	}
	return NULL;
}

extern int
gr_settings_read_int(FILE *file, char const *desired_tag, int *ret)
{
	char *temp = gr_settings_read_string(file, desired_tag);
	char *stop;
	*ret = strtol(temp, &stop, 10);
	int ret_val = stop == NULL || *stop != '\0';
	free(temp);
	return ret_val;
}
