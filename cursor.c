#include <ncurses.h>
#include <string.h>
#include <stdlib.h>

#include "cursor.h"
#include "layout.h"
#include "functions.h"
#include "data.h" 

//These don't really need to be static, I'm just a slave to my java habits
static int col; //The column of the cursor
static int row; //The row of the cursor
static int x; //The on-screen position of the actual cursor
static int y; // -----------------------------------------
static int max_x; //bounds of the screen
static int max_y; //(how big it is)
static int corner_row; //the row and column in the upper left corner
static int corner_col; //---------------------------------------
static int entry_size;


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


void entry(int ch) {
	int typed = 0;
	move(0, 10);
	if (ch >= 43 && ch <= 122) {
		for (int i = 11; i < max_x; i++) {
			printw(" ");
		}
		move(0, 11);
		printw("%c", ch);
		typed++;
	}

	while((ch = getch()) != 10) {
		if (ch == 127) {
			if (typed > 0) {
				move(0, 10 + typed);
				printw(" ");
				move(0, 10 + typed);
				typed--;
			}
		} else {
			if (typed < entry_size) {
				printw("%c", ch);
				typed++;
			}
		}

		/*
		if (typed < entry_size) {
			if (ch == 127 && typed > 0) {
				color_off();
				move(0, 10 + typed);
				printw(" ");
				move(0, 10 + typed);
				typed--;
				color_on();
			} else {
				printw("%c", ch);
				typed++;
			}
		}
		*/
	}
	
	//TODO figure out how to display the data I just entered
	move(0, 10);
	for (int i = 10; i < max_x; i++) {
		printw(" ");
	}
}


//This is just going to print a blank cursor for now
void refill(int y, int x) {
	move(y, x);
	color_off();
	printw("        ");
	move(y, x);
	color_on();
}

void input() {
	int ch;
	while((ch = getch()) != '\0') {
		char entry_line[entry_size]; 
		if (ch == '\033') {
			getch(); //Arrow keys are in the form of [[A, this clears out the second bracket
			int real = getch();
			if (real == 'A') { //up
				if (row > 1 && row > corner_row) {
					refill(y, x);
					move(y-1, x);
					row--;
					y--;
					printw("        ");
					set_icon(row, col); //This should have been a one time thing
					move(y, x);         //But it broke everything when I tried it
					//TODO add contents of new cell to entry line
				} else if(corner_row > 1) {                             
					draw_axes(corner_row-1, corner_col);
					row--;
					corner_row--;
					set_icon(row, col);
					move(y, x);
					//TODO see above
				}
			} else if(real == 'B') { //down
				if (y < max_y - 1) {
					refill(y, x);
					move(y+1, x);
					row++;
					y++;
					printw("        ");
					set_icon(row, col);
					move(y, x);
					//TODO
				} else if (row < 254) {
					draw_axes(corner_row + 1, corner_col);
					row++;
					corner_row++;
					//this will be replaced later (also add in all the other directions)
					//printw("        ");
					set_icon(row, col);
					move(y, x);
					//TODO
				}
			} else if (real == 'C') { //right
				if (x <= max_x - (2 * draw_size)) {
					refill(y, x);
					move(y, x+draw_size);
					printw("        ");
					col++;
					x+=draw_size;
					set_icon(row, col);
					move(y, x);
				} else if(col < 63) {
					draw_axes(corner_row, corner_col + 1);
					col++;
					corner_col++;
					set_icon(row, col);
					move(y, x);
				}
			} else if (real == 'D') { //left
				if (x >= draw_size) {
					refill(y, x);
					move(y, x-draw_size);
					printw("        ");
					col--;
					x-=draw_size;
					set_icon(row, col);
					move(y, x);
				} else if(col > 1) {
					draw_axes(corner_row, corner_col - 1);
					col--;
					corner_col--;
					set_icon(row, col);
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
