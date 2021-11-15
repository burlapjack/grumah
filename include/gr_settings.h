#ifndef GR_SETTINGS_H
#define GR_SETTINGS_H

typedef struct{
	int up;
	int down;
	int left;
	int right;
	int up_right;
	int up_left;
	int down_right;
	int down_left;
	int select;
	int back;
	int inventory;
}SettingsData;

extern void gr_settings_init(SettingsData *s);
extern void gr_settings_free(SettingsData *s);
extern char* gr_settings_read_string(FILE *file, char const *desired_tag);
extern int gr_settings_read_int(FILE *file, char const *desired_tag, int *ret);
#endif /* GR_SETTINGS_H */
