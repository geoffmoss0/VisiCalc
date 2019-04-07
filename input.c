#include <ncurses.h>

#include "input.h"
#include "data.h"
#include "layout.h"

static int x_pos = 0;
static int y_pos = 0;
static int x_real = 4;
static int y_real = 4;




void draw_input() {

}


void parse_input() {
	char ch;
	int max_x, max_y;
	getmaxyx(curscr, max_y, max_x);
	while ((ch = getch()) != '\n') {
		if (ch == '\033') {
			getch();
			int real = getch();
			if (real == 'A') { //up
				if (y_pos == y_start) {
					//shift
					if (y_start != 0) 
						draw_axes(y_start - 1, x);
					//draw cursor
					move(x_real, y_real);
					attron(COLOR_PAIR(2));
					
				} else {
					attroff(COLOR_PAIR(2));
					for (int i = 0; i < draw_size; i++) {
						printw(" ");
					}
					move(x_real, y_real)
				}
			} else if (real == 'B') { //down
				if (y_pos - y_start + 4 >= max_y) {
					//shift
				} else {
					
				}
			} else if (real == 'C') { //right
				if ( ((x_pos - x_start) * draw_size) + 3  ) {
					//shift
				} else {
					
				}
			} else if (real == 'D') { //left
				if (x_pos == x_start) {
					//shift
				} else {
					
				}
			}
		} else {
			
		}
	}
}
