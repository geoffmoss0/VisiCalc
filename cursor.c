#include <ncurses.h>
#include <string.h>
#include <stdlib.h>

#include "cursor.h"
#include "layout.h"
#include "functions.h"
#include "data.h"

//These don't really need to be static, I'm just a slave to my java habits
//Ok don't yell at me I just didn't feel like throwing all these values around
static int col; //The column of the cursor
static int row; //The row of the cursor
static int x; //The on-screen position of the actual cursor
static int y; // -----------------------------------------
static int max_x; //bounds of the screen
static int max_y; //(how big it is)
static int corner_row; //the row and column in the upper left corner
static int corner_col; //---------------------------------------
static int entry_size;
static cell (*table)[64];

///Called by the driver file, sets up the layout and sets all various x and y values
///Calls input(), which handles all user input
void start() {
	draw_size = 8;
	draw_screenyx();
	//will need to be fixed once I implement column sizing
	draw_axes(1, 1);
	corner_row = 1;
	corner_col = 1;
	//draw_screenyx();
	refresh();
	//char cursor[9] = "        ";
	//draw_axes(20, 20);

	move(4, 3);
	printw("        ");
	move(4, 3);
	x = 3;
	y = 4;
	row = 1;
	col = 1;
	getmaxyx(curscr, max_y, max_x);
	entry_size = max_x - 12;
	refresh();
	cell *tab = init_table();
	table = (cell (*)[64])tab;
	input();
	
	char ch = getch();
	endwin();
}


void set_icon(int row, int col) {
	char *letters = to_char(col - 1);
	//printw("%u", strlen(letters));
	move(0, 1);
	if (col < 27) {
		printw(" ");
	}
	printw("%s", letters);
	free(letters);
	printw("%d  ", row); //padding to make sure any other numbers are overwritten
	
	//TODO add the indicator for <L> (label), <V> (value), etc
	move(0, 6);
	printw("<X>");

	//TODO replace this with the data entry for the next thing, clear the rest
	for (int i = 9; i < max_x; i++) {
		printw(" ");
	}
}


///Gets entry when anything besides the arrow keys are typed
///Handles screen sizing automatically, will not scroll past size of screen
void entry(int ch) {
	
	char *entry_line = calloc(entry_size, sizeof(char));

	int typed = 0;
	move(0, 10);
	if (ch >= 32 && ch <= 122) {
		for (int i = 11; i < max_x; i++) {
			printw(" ");
		}
		move(0, 11);
		printw("%c", ch);
		entry_line[typed] = ch;
		typed++;
	}

	while((ch = getch()) != 10) {
		if (ch == 127) {
			if (typed > 0) {
				move(0, 10 + typed);
				printw(" ");
				move(0, 10 + typed);
				entry_line[typed] = 0;
				typed--;
			}
		} else if (ch == 27){
			free(entry_line);
			return;
		} else {
			if (typed < entry_size && ch <= 122 && ch >= 32) {
				printw("%c", ch);
				entry_line[typed] = ch;
				typed++;
			} else if (ch == '\033') {
				//flushinp();
				getch(); //clearing out arrow key notation
				
				getch();
			}
		}
	}
	
	move(0, 10);
	for (int i = 10; i < max_x; i++) {
		printw(" ");
	}
	
	move(y, x);
	set_data(entry_line, row, col, table);
	fill_in(y, x, row, col);
	free(entry_line);
}

///Draw the cursor at the new location with the data inside
void fill_in(int y, int x, int row, int col) {
	move(y, x);
	printw("%s", print_data(row, col, draw_size, table));
	move(y, x);
}


//Rewrite the cell that just had the cursor whlie keeping the data
void refill(int y, int x, int row, int col) {
	color_off();
	move(y, x);
	printw("%s", print_data(row, col, draw_size, table));
	move(y, x);
	color_on();
}

void input() {
	int ch;
	while((ch = getch()) != '\0') {
		if (ch == '\033') {
			getch(); //Arrow keys are in the form of [[A, this clears out the second bracket
			int real = getch();
			if (real == 'A') { //up
				if (row > 1 && row > corner_row) {
					refill(y, x, row, col);
					move(y-1, x);
					row--;
					y--;
					//printw("        ");
					fill_in(y, x, row, col);
					set_icon(row, col); //This should have been a one time thing
					move(y, x);         //But it broke everything when I tried it
				} else if(corner_row > 1) {                             
					draw_axes(corner_row-1, corner_col);
					row--;
					corner_row--;
					set_icon(row, col);
					move(y, x);
					fill_in(y, x, row, col);
				}
			} else if(real == 'B') { //down
				if (y < max_y - 1) {
					refill(y, x, row, col);
					move(y+1, x);
					row++;
					y++;
					fill_in(y, x, row, col);
					set_icon(row, col);
					move(y, x);
				} else if (row < 254) {
					draw_axes(corner_row + 1, corner_col);
					row++;
					corner_row++;
					fill_in(y, x, row, col);
					set_icon(row, col);
					move(y, x);
					//TODO
				}
			} else if (real == 'C') { //right
				if (x <= max_x - (2 * draw_size)) {
					refill(y, x, row, col);
					move(y, x+draw_size);
					col++;
					x+=draw_size;
					fill_in(y, x, row, col);
					set_icon(row, col);
					move(y, x);
				} else if(col < 63) {
					draw_axes(corner_row, corner_col + 1);
					col++;
					corner_col++;
					set_icon(row, col);
					fill_in(y, x, row, col);
					move(y, x);
				}
			} else if (real == 'D') { //left
				if (x >= draw_size) {
					refill(y, x, row, col);
					move(y, x-draw_size);
					//printw("        ");
					col--;
					x-=draw_size;
					set_icon(row, col);
					fill_in(y, x, row, col);
					move(y, x);
				} else if(col > 1) {
					draw_axes(corner_row, corner_col - 1);
					col--;
					corner_col--;
					set_icon(row, col);
					fill_in(y, x, row, col);
					move(y, x);
				}
			}
		} else if (ch <= 127) {
			entry(ch);
			//refill(y, x);
		}
	} 
}

void main(char *argc, char **argv) {
	initscr();
	refresh();
	setup();
	start();
} 
