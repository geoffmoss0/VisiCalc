#include <ncurses.h>

int main(void) {
	initscr();
	refresh();
	noecho();
	refresh();
	int ch, x, y, trash;
	x = 0; 
	y = 0;
	move(0, 0);
	while((ch = getch()) != '\0') {
		if (ch == '\033') {
			getch();
			int real = getch();
			if (real == 'A') {
				if (y != 0) {
					move(y-1, x);
					y--;
				}
			}
			if (real == 'B') {
				move(y+1, x);
				y++;
			}
			if (real == 'C') {
				move(y, x+1);
				x++;
			}
			if (real == 'D') {
				if (x != 0) {
					move(y, x-1);
					x--;
				}
			}
		} else if (ch == 127) { //backspace
			trash = getyx(curscr, y, x);
			//mvprintw(0, 0, "x: %d, y: %d\n", x, y);
			move(y, x-1);
			x--;
			delch();
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
