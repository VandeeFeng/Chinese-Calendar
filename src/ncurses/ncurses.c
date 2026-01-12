#include "ncurses/ncurses.h"
#include "utils/constants.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

void init_colors(void) {
    if (!has_colors()) {
        fprintf(stderr, "Warning: Terminal does not support colors\n");
        return;
    }

    init_pair(COLOR_PAIR_RED, COLOR_RED, COLOR_BLACK);
    init_pair(COLOR_PAIR_GREEN, COLOR_GREEN, COLOR_BLACK);
    init_pair(COLOR_PAIR_YELLOW, COLOR_YELLOW, COLOR_BLACK);
}

void cleanup_ncurses(void) {
    endwin();
}

void init_ncurses(void) {
    setlocale(LC_ALL, "");

    if (initscr() == NULL) {
        fprintf(stderr, "Error: Failed to initialize ncurses\n");
        exit(EXIT_FAILURE);
    }

    atexit(cleanup_ncurses);

    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    start_color();
    timeout(300);

    init_colors();

    refresh();
}
