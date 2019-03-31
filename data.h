#ifndef DATA
#define DATA

struct table_s {
	int rows;
	int cols;
	struct cell_s **cells[rows][cols];
};

struct cell_s {
	int row;
	int col;
	int contents; //based on the number, contains a number, string, or function
	union data_s *data;
};

union data_s {
	int value;
	char *label;
	void (*func)(struct cell_s, struct cell_s, struct table_s);
};

#endif
