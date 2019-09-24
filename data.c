#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <ncurses.h>

#include "data.h"

//static cell **table;

struct cell_s **init_table() {
	struct cell_s **tab = calloc(256 * 64, sizeof(struct cell_s *));
	printw("%p", tab);
	//table = tab;
	return tab;
}

//should this be void? idk
void set_data(char *input, int row, int col, cell table[256][64]) {
	if (input[0] == 58) {
		//Label
		//TODO make sure quotes are consistent
		//TODO sanitize quotes from input
		if (table[row-1][col-1]->data == NULL) {
			cell new = table[row-1][col-1];
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
			if (table[row-1][col-1]->data == NULL) {
				//TODO fix this
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
			if (table[row-1][col-1]->data == NULL) {
				//TODO fix this
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
char *print_data(int row, int col, int draw_size, cell table[256][64]) {
	char *out = (char *)calloc(draw_size + 1, sizeof(char));

	cell print = table[1][1];

	if (print == NULL) {
		//Cell does not have any data
		for (int i = 0; i < draw_size; i++) {
			strcat(out, " ");
		}
		return out;
	} else if (print->contents == 2) {
		//string guaranteed to be in correct form with quotes on either side
		strncat(out, print->data->label, draw_size);
		//for (int i = 
	} else if(print->contents == 1) {
		//gotta display ">>>" if the number is too large, cut off decimal places
		//TODO
	} else if(print->contents == 0) {
		//int
		if(print->contents > pow(10, draw_size)) {
			//too big to display
			strcat(out, ">>>");
			for (int i = 3; i < draw_size; i++) {
				strcat(out, " ");
			}
			return out;
		} else {
			snprintf(out, draw_size, "%ld", print->data->num);
			//strcat(
		}
	}
	return NULL;
}


///returns if the given cell is a value or label
char get_type(int row, int col) {
	(void) row;
	(void) col;
	return 0;
}
