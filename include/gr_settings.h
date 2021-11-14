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
extern void gr_settings_edit_value(SettingsData * s, char tag[], int value);
#endif /* GR_SETTINGS_H */
