#ifndef UI_H
#define UI_H

const char UI_TITLE[12][61];


typedef struct{
	unsigned int id;
	char name[32];
	unsigned int x,y;
}UiMenuOption;


typedef struct{
	unsigned int id;
	unsigned int x,y;
	unsigned int width, height;
	unsigned int options_length; 
	unsigned int highlighted;
	UiMenuOption options[32];
}UiMenu;




UiMenu ui_menu_create_title(unsigned int x, unsigned int y);
UiMenu ui_menu_create_char_creation(unsigned int x, unsigned int y);


void ui_menu_draw(WINDOW *w, UiMenu *m, int *input, unsigned int *game_loop_run, unsigned int *game_state);
void ui_menu_draw_title(WINDOW *w, UiMenu *m, int *input, unsigned int *game_loop_run, unsigned int *game_state);
void ui_menu_draw_character_creation(WINDOW *w, UiMenu *m, int *input, unsigned int *game_loop_run, unsigned int *game_state);

#endif /* UI_H */
