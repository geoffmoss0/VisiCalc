#include <ncurses.h>
#include <string.h>
#include <stdlib.h>

#include "layout.h"
#include "functions.h"
#include "data.h"
#include "cursor.h"

static int col;
static int row;
static int x;
static int y;

void start() {
	draw_screenyx();
	//will need to be fixed once I implement column sizing
	draw_axes(0, 0);
	//draw_screenyx();
	refresh();
	char cursor[9] = "        ";
	//draw_axes(20, 20);
	char ch = getch();
	endwin();
}

void main(char *argc, char **argv) {
	initscr();
	refresh();
	setup();
	start();
} 
