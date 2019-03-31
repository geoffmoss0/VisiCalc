#ifndef DATA
#define DATA

struct table_s {
	int rows;
	int cols;
	
};

struct cell_s {
	int row;
	int col;
	int contents; //based on the number, contains a number, string, or function
};

union data_s {
	int value;
	char *label;
	void (*func)(cell, cell, table);
};

#endif
