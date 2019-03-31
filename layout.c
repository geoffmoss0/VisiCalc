#include <ncurses.h>

#include "layout.h"
#include "functions.h"
#include "data.h"

int draw_screenyx() {
	//Do I really need these parameters?
	if (curscr == NULL) {
		fprintf(stderr, "Window has not yet been initialized\n");
		return 0;
	}
	start_color();
	init_pair(2, COLOR_BLACK, COLOR_BLUE);
	init_pair(1, COLOR_BLUE, COLOR_BLACK);
	attron(COLOR_PAIR(2));

	printw("   A1  ");

	int max_x, max_y;
	getmaxyx(curscr, max_y, max_x);
	for (int x = 7; x < max_x; x++) {
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
	for (int y = 0; y < max_y - 3; y++) {
		for (int x = 0; x < 3; x++) {
			if (y == 0)
				printw(" ");
			else if (y < 10) {
				if (x < 2) 
					printw(" ");
				else
					printw("%d", y);
			} else {
				if (x == 0) {
					printw(" ");
				}
				else if (x == 1) {
					printw("%d", y / 10);
				} else {
					printw("%d", y % 10);
				}
			}
		}
		printw("\n");
	}
	
	move(3, 3);
	int x = 0;
	int j = 0;
	while ((x * 9) < max_x - 9) {
		for (j; j < 9; j++) {
			if (j != 4)
				printw(" ");
			else 
				printw("%c", to_num(j));
		}
	}
}



int main(void) {
	initscr();
	refresh();
	noecho();
	start_color();
	curs_set(0);
	init_pair(5, COLOR_BLACK, COLOR_BLUE);
	
	/**
	attron(COLOR_PAIR(1));
	printw("Works              ");
	attroff(COLOR_PAIR(1));
	*/
	draw_screenyx();
	refresh();
	char ch = getch();
	endwin();
}
