#ifndef DATA
#define DATA

struct cell_s {
	int row;
	int col;
	//do I really need this for the simplest version?
	int contents; //based on the number, contains an int, double, or string (label)
	union data_s *data;
};

union data_s {
	long int num;
	double value;
	char *label;
	//maybe function pointer later?
};

typedef struct cell_s *cell;

typedef union data_s *data;


cell *init_table();

void set_data(char *input, int row, int col, cell table[256][64]);

char *print_data(int row, int col, int draw_size, cell table[256][64]);

#endif
