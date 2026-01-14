#include "utils/common.h"
#include <ncurses.h>
#include <stdio.h>

#define KEY_CTRL(c) ((c) & 0x1f)

int handle_input(int ch, Date *date, int *mode, int *needs_redraw) {
    *needs_redraw = 0;

    switch (ch) {
    case 'h':
        date_add_days(date, -1);
        *needs_redraw = 1;
        break;
    case 'j':
        date_add_days(date, 7);
        *needs_redraw = 1;
        break;
    case 'k':
        date_add_days(date, -7);
        *needs_redraw = 1;
        break;
    case 'l':
        date_add_days(date, 1);
        *needs_redraw = 1;
        break;
    case 'm':
        *mode = 1 - *mode;
        *needs_redraw = 1;
        break;
    case 'd':
        break;
    case KEY_CTRL('f'):
        date_add_months(date, 1);
        *needs_redraw = 1;
        break;
    case KEY_CTRL('b'):
        date_add_months(date, -1);
        *needs_redraw = 1;
        break;
    case 'q':
    case 27:
        printf("退出程序\n");
        return 1;
    default:
        break;
    }

    return 0;
}
