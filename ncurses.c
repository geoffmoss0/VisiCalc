#include <ncurses.h>
#include <string.h>


void refill(int y, int x, char *cursor) {
	attroff(COLOR_PAIR(1));
	for (int i = 0; i < 8; i++) {
		printw("%c", mvinch(y, x + i));
	}
	//printw("%s", cursor);
	attron(COLOR_PAIR(1));
	move(y, x);
	start_color();
}

void draw_cursor(int y, int x, char *cursor) {
	for (int i = 0; i < 8; i++) {
		printw("%c", mvinch(y, x + i));
	}
	move(y, x);
}


int main(void) {


	int draw_size = 8;
	initscr();
	refresh();
	noecho();
	refresh();
	curs_set(0);
	printw("          ");
	int ch, x, y, trash;
	x = 0; //current absolute x position
	y = 0; //current absolute y position
	int typed = 0;
	int max_x;
	int max_y;
	getmaxyx(curscr, max_y, max_x);
	move(0, 0);
	start_color();
	init_color(COLOR_BLACK, 187, 39, 141);
	//init_color(COLOR_BLACK, 141, 297, 477);
	//init_color(COLOR_BLUE, 559, 777, 937);
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	attron(COLOR_PAIR(1));
	char cursor[9] = "        ";
	//printf("%s", cursor);
	refresh();
	while((ch = getch()) != '\0') {
		if (ch == '\033') {
			getch();
			int real = getch();
			if (real == 'A') { //up
				if (y > 0) {
					refill(y, x, cursor);
					move(y-1, x);
					y--;
					//printw("%s", cursor);
					draw_cursor(y, x, cursor);
					//move(y, x);
					typed = 0;
				}
			}
			if (real == 'B') {
				if (y < max_y - 1) {
					refill(y, x, cursor);
					move(y+1, x);
					y++;
					//printw("%s", cursor);
					draw_cursor(y, x, cursor);
					//move(y, x);
					typed = 0;
				}
			}
			if (real == 'C') { //right
				if (x <= max_x - (2 *draw_size) ) {
					refill(y, x, cursor);
					move(y, x+draw_size);
					x+=draw_size;
					//printw("%s", cursor);
					draw_cursor(y, x, cursor);
					//move(y, x);
					typed = 0;
				}
			}
			if (real == 'D') {
				if (x >= draw_size) {
					refill(y, x, cursor);
					move(y, x-draw_size);
					x-=draw_size;
					//printw("%s", cursor);
					draw_cursor(y, x, cursor);
					//move(y, x);
					typed = 0;
				}
			}
		} else if (ch == 127) { //backspace
			if (typed > 0) {
				//trash = getyx(curscr, y, x);
				//mvprintw(0, 0, "x: %d, y: %d\n", x, y);
				move(y, x+typed-1);
				printw(" ");
				move(y, x+typed);
				typed--;
			}
		} else {
			if (typed < 8) {
				move(y, x + typed);
				printw("%c", ch);
				typed++;
			}
		}
		refresh();
	}
	
	ch = getch();
	endwin();

	return 0;
}
