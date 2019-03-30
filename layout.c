#include <ncurses.h>

#include "layout.h"

int draw_screenyx(int y, int x) {
	//Do I really need these parameters?
	if (curscr == NULL) {
		fprintf(stderr, "Window has not yet been initialized\n");
		return 0;
	}
	start_color();
	init_pair(2, COLOR_BLACK, COLOR_BLUE);
	attron(COLOR_PAIR(2));
	int max_x, max_y;
	getmaxyx(curscr, max_y, max_x);
	for (int x = 0; x < max_x; x++) {
		printw(" ");
	}
}



int main(void) {
	initscr();
	refresh();
	noecho();
	start_color();
	init_pair(5, COLOR_BLACK, COLOR_BLUE);
	
	/**
	attron(COLOR_PAIR(1));
	printw("Works              ");
	attroff(COLOR_PAIR(1));
	*/
	draw_screenyx(0, 0);
	refresh();
	char ch = getch();
	endwin();
}
