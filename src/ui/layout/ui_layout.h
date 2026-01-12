#ifndef UI_LAYOUT_H
#define UI_LAYOUT_H

#include <ncurses.h>

typedef struct {
    int y;
    int x;
    int height;
    int width;
} Rect;

typedef struct {
    int height;
    int width;
    int min_height;
    int min_width;
    int content_height;
    int header_height;
    int footer_height;
} Layout;

typedef struct {
    Rect header;
    Rect left_panel;
    Rect center_panel;
    Rect right_panel;
    Rect calendar_panel;
    Rect help_panel;
    Rect footer;
} PanelLayout;

void layout_init(Layout *layout);
int layout_check_min_size(const Layout *layout);
void layout_calculate_panels(Layout *layout, PanelLayout *panels);
void layout_draw_separator(int y, int x, int width);
Rect layout_get_content_rect(const Rect *border_rect, int padding);

#endif
