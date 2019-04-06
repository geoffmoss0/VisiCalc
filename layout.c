#include <ncurses.h>
#include <string.h>
#include <stdlib.h>

#include "layout.h"
#include "functions.h"
#include "data.h"


///Draw the axes, with y as the starting row and x as the starting column (converted to letters)
void draw_axes(int y, int x, int draw_size) {
	int max_x, max_y;
	getmaxyx(curscr, max_y, max_x);
	move(4, 0);
	int b = 4;
	attron(COLOR_PAIR(2));
	for (int a = y; a < max_y; a++) {
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
	while ( (k * draw_size) + 3 < max_x) {
		for (int j = 0; j < draw_size; j++) {
			if (k + x < 26) {
				if (j != ((draw_size / 2)) )
					printw(" ");
				else {
					char *letters = to_char(k + x);
					printw("%s", letters);
					j++;
					free(letters);
				}			
			} else {
				if (j != (int) ((draw_size - 0.5) / 2) ) {
					printw(" ");
				} else {
					char *letters = to_char(k + x);
					printw("%s", letters);
					j++;
					free(letters);
				}
			}

		}
		k++;
	}
}

///Draws the data inside the cells. Definitely not working on this now
void draw_cells(int y, int x) {

}


///Initial setup for the screen, at some point I might make this work with
///the modular drawing functions. However, that day is not today
int draw_screenyx() {
	//Do I really need these parameters?
	if (curscr == NULL) {
		fprintf(stderr, "Window has not yet been initialized\n");
		return 0;
	}
	start_color();
	//Background: 36, 76, 122
	//Foreground: 143, 199, 240 
	//init_color(COLOR_BLACK, 141, 297, 477);
	init_color(COLOR_BLACK, 187, 39, 141);
	init_color(COLOR_BLUE, 334, 627, 845);
	init_pair(2, COLOR_BLACK, COLOR_BLUE); //Light background
	init_pair(1, COLOR_BLUE, COLOR_BLACK); //Dark background
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
	
	printw("   ");
	int b = 4;
	move(b, 0);
	for (int y = 0; y < max_y - 4; y++) {
		if (y >= 9)
			printw(" %d", y + 1);
		else 
			printw("  %d", y + 1);
		move(b + 1, 0);
		b++;
	}
	
	move(3, 3);
	int x = 0;
	int j = 0;
	while ((x * 9) < max_x - 9) {
		for (j = 0; j < 9; j++) {
			if (j != 4)
				printw(" ");
			else {
				char *letters = to_char(x);
				printw("%c", letters);
				free(letters);
			}
		}
		x++;
	}
	refresh();
	return 0;
}



int main(void) {
	initscr();
	refresh();
	noecho();
	curs_set(0);
	/**
	attron(COLOR_PAIR(1));
	printw("Works              ");
	attroff(COLOR_PAIR(1));
	*/
	draw_screenyx();
	refresh();
	char cursor[9] = "        ";
	draw_axes(20, 20, 8);
	char ch = getch();
	endwin();
	return 0;
}
