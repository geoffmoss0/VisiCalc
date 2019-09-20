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
	refresh();
	input();
	
	char ch = getch();
	endwin();
}

//This is just going to print a blank cursor for now
void refill(int y, int x) {
	color_off();
	printw("        ");
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
					refill(y, x);
					move(y-1, x);
					row--;
					y--;
					printw("        ");
					move(y, x);
				}
			} else if(real == 'B') { //down
				if (y < max_y - 1) {
					refill(y, x);
					move(y+1, x);
					row++;
					y++;
					printw("        ");
					move(y, x);
				} else if (row < 255) {
					draw_axes(corner_row + 1, col);
					row++;
					corner_row++;
					move(y, x);
					//this will be replaced later
					printw("        ");
					move(y, x);
				}
			} else if (real == 'C') { //right
				if (x <= max_x - (2 * draw_size) && col < 256) {
					refill(y, x);
					move(y, x+draw_size);
					printw("        ");
					col++;
					x+=draw_size;
					move(y, x);
				}
			} else if (real == 'D') { //left
				if (x >= draw_size && col > 1) {
					refill(y, x);
					move(y, x-draw_size);
					printw("        ");
					col--;
					x-=draw_size;
					move(y, x);
				}
			}
		} else {
			printw("%c", ch);
		}
	} 
}

void main(char *argc, char **argv) {
	initscr();
	refresh();
	setup();
	start();
} 
