#include <ncurses.h>
#include <string.h>
#include <stdlib.h>

#include "cursor.h"
#include "layout.h"
#include "functions.h"
#include "data.h"

//These don't really need to be static, I'm just a slave to my java habits
static int col;
static int row;
static int x;
static int y;
static int max_x;
static int max_y;


///Called by the driver file, sets up the layout and sets all various x and y values
///Calls input(), which handles all user input
void start() {
	draw_size = 8;
	draw_screenyx();
	//will need to be fixed once I implement column sizing
	draw_axes(0, 0);
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

void input() {
	int ch;
	while((ch = getch()) != '\0') {
		if (ch == '\033') {
			getch(); //Arrow keys are in the form of [[A, this clears out the second bracket
			int real = getch();
			if (real == 'A') { //up
				if (row > 1) {
					color_off();
					printw("        ");
					color_on();
					//placeholder, eventually I'll get this from data.c
					move(y-1, x);
					row--;
					y--;
					printw("        ");
					move(y, x);
				}
			} 
			if(real == 'B') { //down
				if (y < max_y - 1 && row < 256) {
					color_off();
					//placeholder
					printw("        ");
					color_on();
					move(y+1, x);
					row++;
					y++;
					printw("        ");
					move(y, x);
				}
			}
			if (real == 'C') { //right
				if (x <= max_x - (2 * draw_size) && col < 256) {
					color_off();
					//placeholder
					printw("        ");
					color_on();
					move(y, x+draw_size);
					printw("        ");
					col++;
					x+=draw_size;
					move(y, x);
				}
			} 
			if (real == 'D') { //left
				if (x >= draw_size && col > 1) {
					color_off();
					//placeholder
					printw("        ");
					color_on();
					move(y, x - draw_size);
					printw("        ");
					col--;
					x-=draw_size;
					move(y, x);
				}
			}
		}
	} 
}

void main(char *argc, char **argv) {
	initscr();
	refresh();
	setup();
	start();
} 
