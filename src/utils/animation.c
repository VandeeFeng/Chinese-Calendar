#define _DEFAULT_SOURCE
#include "utils/common.h"
#include "utils/constants.h"
#include <ncurses.h>
#include <unistd.h>

void animation_page_turn(Date *date, int direction) {
    const int height = LINES;
    const int width = COLS;
    const int day_delta = (direction > 0) ? 1 : -1;
    const char *corner_char = (direction > 0) ? "╱" : "╲";

    for (int i = 0; i < PAGE_TURN_FRAMES; i++) {
        for (int j = 0; j < 3; j++) {
            const int curl_y = height - 1 - i - j;
            const int curl_x = width - 1 - i * 2 - j;

            if (curl_y > 0 && curl_x > 0) {
                mvprintw(curl_y, curl_x, "%s", corner_char);
            }
        }

        refresh();
        usleep(PAGE_TURN_DELAY_US);
    }

    date_add_days(date, day_delta);
}
