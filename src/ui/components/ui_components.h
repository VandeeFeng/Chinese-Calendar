#ifndef UI_COMPONENTS_H
#define UI_COMPONENTS_H

#include <ncurses.h>
#include "calendar/lunar.h"
#include "almanac/almanac.h"
#include "ui/visual/deity_art.h"

#include "ui/visual/big_numbers.h"
#include "ui/layout/ui_layout.h"

typedef struct {
    int y;
    int x;
    const char *text;
    int color_pair;
} Label;

void draw_box(int y, int x, int height, int width);
void draw_calendar_grid(int y, int x, const Date *date, int max_y);
void ui_draw_header(const Rect *rect);
void ui_draw_footer(const Rect *rect);
void ui_draw_left_panel(const Rect *rect, const Date *date);
void ui_draw_center_panel(const Rect *rect, const Date *date);
void ui_draw_right_panel(const Rect *rect, const Date *date, const LunarDate *lunar, const Almanac *alm, int mode);
void ui_draw_calendar_panel(const Rect *rect, const Date *date);
void ui_draw_help_panel(const Rect *rect);
void ui_draw_label(int y, int x, const char *text, int color_pair);
void ui_draw_outer_border(int height, int width);

#endif
