#include <ncurses.h>
#include <string.h>
#include <stdlib.h>

#include "layout.h"
#include "functions.h"
#include "data.h"


static int draw_size;
static int x_start;
static int y_start;


void color_on() {
	attroff(COLOR_PAIR(1));
	attron(COLOR_PAIR(2));
}

void color_off() {
	attroff(COLOR_PAIR(2));
	attron(COLOR_PAIR(1));
}
///Draw the axes, with y as the starting row and x as the starting column (converted to letters)
///This function is a goddamn mess and I should never touch it once it works
void draw_axes(int yn, int xn) {
	xn--; //don't
	yn--; //ask
	x_start = xn;
	y_start = yn;
	int max_x, max_y;
	getmaxyx(curscr, max_y, max_x);
	move(4, 0);
	int b = 4;
	attron(COLOR_PAIR(2));
	for (int a = yn+1; a < max_y - 3 + yn; a++) {
		if (a >= 100) {
			printw("%d", a);
		} else if (a >= 10) {
			printw(" %d", a);
		} else {
			printw("  %d", a);
		}
		
		move(b + 1, 0);
		b++;
	}
	
	move(3, 3);
	
	int k = 0;
	while ( ((k+1) * draw_size) + 3 < max_x) {
		for (int j = 0; j < draw_size; j++) {
			if (k + xn < 26) {
				if (j != ((draw_size / 2)) )
					printw(" ");
				else {
					char *letters = to_char(k + xn);
					printw("%s", letters);
					free(letters);
				}			
			} else {
				if (j != (int) ((draw_size - 0.5) / 2)) {
					printw(" ");
				} else {
					char *letters = to_char(k + xn);
					printw("%s", letters);
					j++;
					free(letters);
				}
			}

		}
		k++;
	}
	//move(4, 4);
	//draw_cells(start_y, start_x);
}

///Draws the data inside the cells. Definitely not working on this now
//void draw_cells(int y, int x) {
	//make sure to keep track of cursor position locally
//}


///Initial setup for the screen, at some point I might make this work with
///the modular drawing functions. However, that day is not today
int draw_screenyx() {
	//Do I really need these parameters?
	if (curscr == NULL) {
		fprintf(stderr, "Window has not yet been initialized\n");
		return 0;
	}
	move(0, 0);
	start_color();
	//Background: 36, 76, 122
	//Foreground: 143, 199, 240 
	//init_color(COLOR_BLACK, 141, 297, 477);
	init_color(COLOR_BLACK, 187, 39, 141);
	init_color(COLOR_BLUE, 334, 627, 845);
	init_pair(2, COLOR_BLACK, COLOR_BLUE); //Light background
	init_pair(1, COLOR_BLUE, COLOR_BLACK); //Dark background
	attron(COLOR_PAIR(2));

	printw("  A1  ");

	int max_x, max_y;
	getmaxyx(curscr, max_y, max_x);
	for (int x = 6; x < max_x; x++) {
		printw(" ");
	}
	move(1, 0);
	for (int x = 0; x < max_x; x++) {
		printw(" ");
	}
	attroff(COLOR_PAIR(2));
	attron(COLOR_PAIR(1));
	for (int x = 0; x < max_x; x++) {
		printw(" ");
	}
	attroff(COLOR_PAIR(1));
	attron(COLOR_PAIR(2));
	
	printw("   ");
	draw_axes(1, 1);
	refresh();
	return 0;
}

void setup() {
	noecho();
	curs_set(0);
	draw_size = 8;
}

/*
int main(void) {
	draw_size = 8;
	initscr();
	refresh();
	noecho();
	curs_set(0);
	draw_size = 8;
	
	//attron(COLOR_PAIR(1));
	//printw("Works              ");
	//attroff(COLOR_PAIR(1));

	draw_screenyx();
	refresh();
	char cursor[9] = "        ";
	draw_axes(20, 20);
	char ch = getch();
	endwin();
	return 0;
}
*/
