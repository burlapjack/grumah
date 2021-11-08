#ifndef GR_INPUT_H
#define GR_INPUT_H

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
}Input;

void gr_input_file_get_custom_values(Input *i);

#endif /* GR_INPUT_H */
