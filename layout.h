#include "data.h"
#ifndef LAYOUT
#define LAYOUT

static int draw_size;

int draw_screenyx();

void draw_axes(int y, int x);

void draw_cells(int row, int col, int max_y, int max_x, int draw_size, cell (**table)[64]);

void setup();

void color_on();

void color_off();

#endif
