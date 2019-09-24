#include <stdlib.h>
#include <string.h>

#include "data.h"

typedef struct cell_s *cell;

typedef union  data_s *data;

static cell **table;

cell **init_table() {
	cell **tab = (cell **)calloc(256 * 64, sizeof(cell));
	table = tab;
	return tab;
}

//should this be void? idk
void set_data(char *input, int row, int col) {
	if (input[0] == 58) {
		//Label
		//TODO make sure quotes are consistent
		if (table[row-1][col-1] == NULL) {
			cell new = (cell)malloc(sizeof(struct cell_s));
			new->row = row;
			new->col = col;
			new->contents = 2;
			new->data = (data)malloc(sizeof(union data_s));
			strcpy(new->data->label, input);
			table[row-1][col-1] = new;
		} else if (strchr(input, '.')) {
			//double
			char **trash;
			double num = strtod(input, trash);
			if (table[row-1][col-1] == NULL) {
				cell new = (cell)malloc(sizeof(struct cell_s));
				new->row = row;
				new->col = col;
				new->contents = 1;
				new->data = (data)malloc(sizeof(union data_s));
				new->data->value = num;
			}
		} else {
			//long int (must be all numbers, no other symbols)
			char **trash;
			long int num = strtol(input, trash, 10);
			if (table[row-1][col-1] == NULL) {
				cell new = (cell)malloc(sizeof(struct cell_s));
				new->row = row;
				new->col = col;
				new->contents = 0;
				new->data = (data)malloc(sizeof(union data_s));
				new->data->num = num;
			}
		}
		//Functions to come later, I have no idea how that will work
	}
}


///return the format in which the data of a cell at row and col should be displayed
char *print_data(int row, int col, int draw_size) {
	char *out = (char *)calloc(draw_size + 1, sizeof(char));
	cell print = table[row-1][col-1];
	if (print == NULL) {
		for (int i = 0; i < draw_size; i++) {
			strcat(out, " ");
		}
		return out;
	}
	return NULL;
}


///returns if the given cell is a value or label
char get_type(int row, int col) {
	(void) row;
	(void) col;
	return 0;
}
