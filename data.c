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
			cell new = table[row-1][col-1];
			if (new->contents == 2) {
				new->data->label = (char *)realloc(new->data->label, strlen(input));
			} else {
				new->data->label = (char *)malloc(strlen(input));
				new->contents = 2;
			}
			strcpy(new->data->label, input+1);
			if(new->data->label[strlen(input)-2] == '"') {
				new->data->label[strlen(input)-2] = '\0';
			}
		}
	} else if (strchr(input, '.')) {
		//double
		double num = strtod(input, NULL);
		if (num == 0.0 && input[0] != '0')
			return; //Failed, didn't parse 0
		if (table[row-1][col-1] == NULL) {
			cell new = (cell)malloc(sizeof(struct cell_s));
			new->row = row;
			new->col = col;
			new->contents = 1;
			new->data = (data)malloc(sizeof(union data_s));
			new->data->value = num;
			table[row-1][col-1] = new;
		} else {
			cell new = table[row-1][col-1];
			if (new->contents == 2) {
				free(new->data->label);
			}
			new->contents = 1;
			new->data->value = num; 
		}
	} else {
		//long int (must be all numbers, no other symbols)
		long int num;
		if (input[0] >= 48 && input[0] <= 57) {
			num = strtol(input, NULL, 10);
		} else {
			return;
		}
		if (table[row-1][col-1] == NULL) {
			cell new = (cell)malloc(sizeof(struct cell_s));
			new->row = row;
			new->col = col;
			new->contents = 0;
			new->data = (data)malloc(sizeof(union data_s));
			new->data->num = num;
			table[row-1][col-1] = new;
		} else {
			cell new = table[row-1][col-1];
			if (new->contents == 2)
				free(new->data->label);
			new->data->num = num;
			new->contents = 0;
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
		char make[draw_size+1];
		strncat(make, print->data->label, draw_size);
		for (int i = 0; i < draw_size - strlen(make); i++) {
			strcat(out, " ");
		}
		strcat(out, make);
		return out;
	} else if(print->contents == 1) {
		//gotta display ">>>" if the number is too large, cut off decimal places
		if (print->data->value >= pow(10, draw_size)) {
			for (int i = 0; i < draw_size-3; i++) {
				strcat(out, " ");
			}
			strcat(out, ">>>");
			return out;
		}
		else {
			char make[draw_size + 1];
			snprintf(make, draw_size+1, "%'.15f", print->data->value);
			//remove trailing zeros
			int i = strlen(make)-1;
			while (i >= 0 && make[i] == '0') {
				make[i] = '\0'; //no harm in filling it up with null bytes
				i--;
			}
			//pad out to fit the length of the columns
			for (int i = 0; i < draw_size - strlen(make); i++) {
				strcat(out, " ");
			}
			strcat(out, make);
			return out;
		}
	} else if(print->contents == 0) {
		//int
		if(print->data->num > pow(10, draw_size)) {
			//too big to display
			for (int i = 0; i < draw_size-3; i++) {
				strcat(out, " ");
			}
			strcat(out, ">>>");
			return out;
		} else {
			char create[draw_size+1];
			snprintf(create, draw_size + 1, "%ld", print->data->num);
			for (int i = strlen(create); i < draw_size; i++) {
				strcat(out, " ");
			}
			strcat(out, create);
			return out;
		}
	}
	return NULL;
}


char *get_raw(int row, int col, int entry_size, cell (**table)[64]) {
	char *out = (char *)calloc(entry_size + 1, sizeof(char));
	cell from = (*table)[row-1][col-1];
	if (from == NULL) {
		return NULL;
	}

	if (from->contents == 2) {
		//label
		strncat(out, from->data->label, entry_size);
		return out;
	} else if (from->contents == 1) {

		snprintf(out, entry_size, "%'.15f", from->data->value);
		//get rid of trailing zeros
		int i = strlen(out) - 1;
		while(i >= 0 && out[i] == '0') {
			out[i] = '\0';
		}
		return out;
	} else {
		//int
		snprintf(out, entry_size, "%ld", from->data->num);
		return out;
	}
}
