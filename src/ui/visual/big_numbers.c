#include <ncurses.h>
#include <string.h>
#include "big_numbers.h"

static const char* big_digits[10][BIG_DIGIT_HEIGHT] = {
    {
        "██████████",
        "██      ██",
        "██      ██",
        "██      ██",
        "██      ██",
        "██      ██",
        "██      ██",
        "██      ██",
        "██      ██",
        "██      ██",
        "██████████"
    },
    {
        "    ██   ",
        "    ██   ",
        "    ██   ",
        "    ██   ",
        "    ██   ",
        "    ██   ",
        "    ██   ",
        "    ██   ",
        "    ██   ",
        "    ██   ",
        "    ██   "
    },
    {
        "██████████",
        "        ██",
        "        ██",
        "        ██",
        "        ██",
        "██████████",
        "██        ",
        "██        ",
        "██        ",
        "██        ",
        "██████████"
    },
    {
        "██████████",
        "        ██",
        "        ██",
        "        ██",
        "        ██",
        "██████████",
        "        ██",
        "        ██",
        "        ██",
        "        ██",
        "██████████"
    },
    {
        "██      ██",
        "██      ██",
        "██      ██",
        "██      ██",
        "██      ██",
        "██████████",
        "        ██",
        "        ██",
        "        ██",
        "        ██",
        "        ██",
    },
    {
        "██████████",
        "██        ",
        "██        ",
        "██        ",
        "██        ",
        "██████████",
        "        ██",
        "        ██",
        "        ██",
        "        ██",
        "██████████"
    },
    {
        "██████████",
        "██        ",
        "██        ",
        "██        ",
        "██        ",
        "██████████",
        "██      ██",
        "██      ██",
        "██      ██",
        "██      ██",
        "██████████"
    },
    {
        "██████████",
        "        ██",
        "        ██",
        "        ██",
        "        ██",
        "        ██",
        "        ██",
        "        ██",
        "        ██",
        "        ██",
        "        ██"
    },
    {
        "██████████",
        "██      ██",
        "██      ██",
        "██      ██",
        "██      ██",
        "██████████",
        "██      ██",
        "██      ██",
        "██      ██",
        "██      ██",
        "██████████"
    },
    {
        "██████████",
        "██      ██",
        "██      ██",
        "██      ██",
        "██      ██",
        "██████████",
        "        ██",
        "        ██",
        "        ██",
        "        ██",
        "██████████"
    }
};

int big_number_get_day_width(int day) {
    if (day >= 1 && day <= 9) {
        return BIG_DIGIT_WIDTH;
    } else if (day >= 10 && day <= 31) {
        return BIG_DIGIT_WIDTH + 2 + BIG_DIGIT_WIDTH;
    }
    return BIG_DIGIT_WIDTH;
}

void big_number_draw_digit(WINDOW *win, int y, int x, int digit) {
    if (digit < 0 || digit > 9) {
        return;
    }
    
    for (int i = 0; i < BIG_DIGIT_HEIGHT; i++) {
        mvwprintw(win, y + i, x, "%s", big_digits[digit][i]);
    }
}

void big_number_draw_date(WINDOW *win, int y, int x, int month, int day) {
    int current_x = x;

    int month_tens = month / 10;
    int month_units = month % 10;

    big_number_draw_digit(win, y, current_x, month_tens);
    current_x += BIG_DIGIT_WIDTH + 1;
    big_number_draw_digit(win, y, current_x, month_units);
    current_x += BIG_DIGIT_WIDTH + 2;

    mvwprintw(win, y + 5, current_x, "月");
    current_x += 2;

    current_x += 2;

    int day_tens = day / 10;
    int day_units = day % 10;

    big_number_draw_digit(win, y, current_x, day_tens);
    current_x += BIG_DIGIT_WIDTH + 1;
    big_number_draw_digit(win, y, current_x, day_units);
    current_x += BIG_DIGIT_WIDTH + 2;

    mvwprintw(win, y + 5, current_x, "日");
}

void big_number_draw_day(WINDOW *win, int y, int x, int day) {
    int day_tens = day / 10;
    int day_units = day % 10;

    int start_x = x;
    if (day_tens == 0) {
        start_x = x + BIG_DIGIT_WIDTH + 1;
    }

    if (day_tens != 0) {
        big_number_draw_digit(win, y, start_x, day_tens);
        start_x += BIG_DIGIT_WIDTH + 2;
    }

    big_number_draw_digit(win, y, start_x, day_units);
}
