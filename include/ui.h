#ifndef UI_H
#define UI_H


typedef struct{
	unsigned int x,y;
	unsigned int width, height;
	unsigned int options_length; 
	unsigned int highlighted;
}UiMenu;

void ui_start_menu_draw(WINDOW *w, UiMenu *m, int *input, int *game_loop_run);

#endif /* UI_H */
