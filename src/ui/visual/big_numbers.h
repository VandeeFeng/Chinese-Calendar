#ifndef BIG_NUMBERS_H
#define BIG_NUMBERS_H

#define BIG_DIGIT_HEIGHT 11
#define BIG_DIGIT_WIDTH 10

int big_number_get_day_width(int day);
void big_number_draw_digit(WINDOW *win, int y, int x, int digit);
void big_number_draw_date(WINDOW *win, int y, int x, int month, int day);
void big_number_draw_day(WINDOW *win, int y, int x, int day);

#endif
