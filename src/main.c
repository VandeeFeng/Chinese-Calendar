#define _DEFAULT_SOURCE
#include <ncurses.h>
#include <locale.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "utils/common.h"
#include "utils/constants.h"
#include "calendar/lunar.h"
#include "almanac/almanac.h"
#include "ncurses/ncurses.h"

#include "ui/visual/deity_art.h"
#include "ui/visual/big_numbers.h"
#include "ui/layout/ui_layout.h"
#include "ui/components/ui_components.h"

int main(void) {
    init_ncurses();

    Date current_date;
    date_to_today(&current_date);

    int mode = 0;
    int ch;
    int needs_redraw = 1;

    Layout layout;
    PanelLayout panels;

    static int prev_height = 0;
    static int prev_width = 0;

    while (1) {
        if (needs_redraw ||
            (prev_height != 0 && prev_height != LINES) ||
            (prev_width != 0 && prev_width != COLS)) {
            erase();
            needs_redraw = 0;
        }

        getmaxyx(stdscr, layout.height, layout.width);
        layout_init(&layout);

        if (!layout_check_min_size(&layout)) {
            mvprintw(0, 0, "终端尺寸太小，请使用至少 %dx%d 的终端", MIN_TERMINAL_HEIGHT, MIN_TERMINAL_WIDTH);
            mvprintw(1, 0, "当前尺寸: %dx%d", layout.height, layout.width);
            refresh();
            endwin();
            fprintf(stderr, "Error: Terminal size too small\n");
            fprintf(stderr, "Required: at least %dx%d\n", MIN_TERMINAL_HEIGHT, MIN_TERMINAL_WIDTH);
            fprintf(stderr, "Current: %dx%d\n", layout.height, layout.width);
            return EXIT_FAILURE;
        }

        layout_calculate_panels(&layout, &panels);

        LunarDate lunar;
        if (solar_to_lunar(&current_date, &lunar) != 0) {
            mvprintw(0, 0, "错误: 无法转换日期");
            refresh();
            continue;
        }

        Almanac alm;
        almanac_init(&alm);
        almanac_calculate(&current_date, &lunar, &alm);

        ui_draw_header(&panels.header);
        ui_draw_left_panel(&panels.left_panel, &current_date);
        ui_draw_center_panel(&panels.center_panel, &current_date);
        ui_draw_right_panel(&panels.right_panel, &current_date, &lunar, &alm, mode);
        ui_draw_calendar_panel(&panels.calendar_panel, &current_date);
        ui_draw_help_panel(&panels.help_panel);
        ui_draw_footer(&panels.footer);

        ui_draw_outer_border(layout.height, layout.width);

        refresh();

        ch = getch();

        if (handle_input(ch, &current_date, &mode, &needs_redraw)) {
            return EXIT_SUCCESS;
        }

        prev_height = layout.height;
        prev_width = layout.width;
    }

    return EXIT_SUCCESS;
}
