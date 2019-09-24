#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <ncurses.h>

#include "data.h"

//static cell **table;
static int count = 0;

struct cell_s **init_table() {
	struct cell_s **tab = (struct cell_s **)calloc(256 * 64, sizeof(struct cell_s *));
	//table = tab;
	return tab;
}

//should this be void? idk
void set_data(char *input, int row, int col, cell table[256][64]) {
	if (input[0] == 34) {
		//Label
		//TODO make sure quotes are consistent
		if (table[row-1][col-1] == NULL) {
			cell new = (cell)malloc(sizeof(struct cell_s));
			new->row = row;
			new->col = col;
			new->contents = 2;
			new->data = (data)malloc(sizeof(union data_s));
			new->data->label = (char *)malloc(strlen(input));
			strcpy(new->data->label, input+1);
			if(new->data->label[strlen(input)-2] == '"')
				new->data->label[strlen(input)-2] = '\0';
			table[row-1][col-1] = new;
		} else {
			table[row-1][col-1] = realloc(table[row-1][col-1]->data->label, strlen(input));
			strcpy(table[row-1][col-1]->data->label, input+1);
			if(table[row-1][col-1]->data->label[strlen(input)-2] == '"') {
				table[row-1][col-1]->data->label[strlen(input)-2] = '\0';
			}
		}
	} else if (strchr(input, '.')) {

	//double
	char **trash;
		double num = strtod(input, trash);
		if (table[row-1][col-1]== NULL) {
			//TODO fix this
			cell new = (cell)malloc(sizeof(struct cell_s));
			new->row = row;
			new->col = col;
			new->contents = 1;
			new->data = (data)malloc(sizeof(union data_s));
			new->data->value = num;
			table[row-1][col-1] = new;
		}
	} else {
		/*
		move(21, 20);
		printw("parsing an int: %s", input);
		refresh();
		*/
		//long int (must be all numbers, no other symbols)
		long int num;
		if (input[0] >= 48 && input[0] <= 57) {
			num = strtol(input, NULL, 10);
		} else {
			return;
		}
		if (table[row-1][col-1] == NULL) {
			//TODO fix this
			cell new = (cell)malloc(sizeof(struct cell_s));
			new->row = row;
			new->col = col;
			new->contents = 0;
			new->data = (data)malloc(sizeof(union data_s));
			new->data->num = num;
			table[row-1][col-1] = new;
		} else {
			table[row-1][col-1]->data->num = num;
		}
	}
	//Functions to come later, I have no idea how that will work
}


///return the format in which the data of a cell at row and col should be displayed
char *print_data(int row, int col, int draw_size, cell table[256][64]) {
	char *out = (char *)calloc(draw_size + 1, sizeof(char));

	cell print = table[row-1][col-1];

	if (print == NULL) {
		//Cell does not have any data
		for (int i = 0; i < draw_size; i++) {
			strcat(out, " ");
		}
		return out;
	} else if (print->contents == 2) {
		//string guaranteed to be in correct form with quotes on either side
		strncat(out, print->data->label, draw_size);
		for (int i = strlen(out); i < draw_size; i++) {
			strcat(out, " ");
		}
		return out;
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
			char create[draw_size+1];
			snprintf(create, draw_size, "%ld", print->data->num);
			for (int i = strlen(create); i < draw_size; i++) {
				strcat(out, " ");
			}
			strcat(out, create);
			return out;
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
