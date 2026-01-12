#ifndef CHINESE_BORDER_H
#define CHINESE_BORDER_H

#include <ncurses.h>

typedef enum {
    BORDER_STYLE_SIMPLE,
    BORDER_STYLE_CLOUD,
    BORDER_STYLE_MEIHUA,
    BORDER_STYLE_MOSAIC,
    BORDER_STYLE_DECORATED
} BorderStyle;

typedef struct {
    int y;
    int x;
    int height;
    int width;
    BorderStyle style;
    int color_pair;
    int padding;
} BorderConfig;

void chinese_border_draw(const BorderConfig *config);
void chinese_border_draw_top(int y, int x, int width, BorderStyle style, int color_pair);
void chinese_border_draw_bottom(int y, int x, int width, BorderStyle style, int color_pair);
void chinese_border_draw_left(int y, int x, int height, BorderStyle style, int color_pair, int padding);
void chinese_border_draw_right(int y, int x, int height, BorderStyle style, int color_pair, int padding);
void chinese_border_draw_corners(int y, int x, int height, int width, BorderStyle style, int color_pair);
void chinese_border_draw_separator(int y, int x, int width, BorderStyle style, int color_pair);

#endif
