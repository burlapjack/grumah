#ifndef UI_H
#define UI_H

typedef struct{
	unsigned int x,y;
	char *options[3];
}UiMenuStart;

void ui_draw_menu_start(WINDOW *win, UiMenuStart *s);

#endif /* UI_H */
