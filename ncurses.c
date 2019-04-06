#include <ncurses.h>
#include <string.h>


void refill(int y, int x, char *cursor) {
	attroff(COLOR_PAIR(1));
	printw("%s", cursor);
	attron(COLOR_PAIR(1));
	move(y, x);
	start_color();
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
	x = 0; 
	y = 0;
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
			if (real == 'A') {
				if (y > 0) {
					refill(y, x, cursor);
					move(y-1, x);
					y--;
					printw("%s", cursor);
					move(y, x);
				}
			}
			if (real == 'B') {
				if (y < max_y - 1) {
					refill(y, x, cursor);
					move(y+1, x);
					y++;
					printw("%s", cursor);
					move(y, x);
				}
			}
			if (real == 'C') {
				if (x <= max_x - (2 *draw_size) ) {
					refill(y, x, cursor);
					move(y, x+draw_size);
					x+=draw_size;
					printw("%s", cursor);
					move(y, x);
				}
			}
			if (real == 'D') {
				if (x >= draw_size) {
					refill(y, x, cursor);
					move(y, x-draw_size);
					x-=draw_size;
					printw("%s", cursor);
					move(y, x);
				}
			}
		} else if (ch == 127) { //backspace
			trash = getyx(curscr, y, x);
			//mvprintw(0, 0, "x: %d, y: %d\n", x, y);
			move(y, x-draw_size);
			x-=draw_size;
			printw("%s", cursor);
		} else {
			printw("%c", ch);
			x++;
		}
		refresh();
	}
	
	ch = getch();
	endwin();

	return 0;
}
