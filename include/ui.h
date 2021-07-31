#ifndef UI_H
#define UI_H

const char UI_TITLE[12][61];

typedef struct{
	unsigned int x,y;
	unsigned int width, height;
	unsigned int options_length; 
	unsigned int highlighted;
}UiMenu;

UiMenu ui_menu_create_title(unsigned int x, unsigned int y);
UiMenu ui_menu_create_char_creation(unsigned int x, unsigned int y);


void ui_menu_draw_title(WINDOW *w, UiMenu *m, int *input, int *game_loop_run);
void ui_menu_draw_char_creation(WINDOW *w, UiMenu *m, int *input, int *game_loop_run);

#endif /* UI_H */
