#include "ui/layout/ui_layout.h"
#include <string.h>
#include "utils/constants.h"

void layout_init(Layout *layout) {
    getmaxyx(stdscr, layout->height, layout->width);
    layout->min_height = MIN_TERMINAL_HEIGHT;
    layout->min_width = MIN_TERMINAL_WIDTH;
    layout->header_height = HEADER_HEIGHT;
    layout->footer_height = FOOTER_HEIGHT;
    layout->content_height = layout->height - layout->header_height - layout->footer_height;
}

int layout_check_min_size(const Layout *layout) {
    return (layout->height >= layout->min_height && layout->width >= layout->min_width);
}

void layout_calculate_panels(Layout *layout, PanelLayout *panels) {
    panels->header.y = OUTER_BORDER_PADDING;
    panels->header.x = OUTER_BORDER_PADDING;
    panels->header.height = layout->header_height;
    panels->header.width = layout->width - 2 * OUTER_BORDER_PADDING;

    const int available_width = layout->width - CONTENT_PADDING * 2 - OUTER_BORDER_PADDING * 2;
    int center_panel_width = available_width - LEFT_PANEL_WIDTH - RIGHT_PANEL_WIDTH - PANEL_GAP * 2;

    if (center_panel_width < MIN_CENTER_PANEL_WIDTH) {
        center_panel_width = MIN_CENTER_PANEL_WIDTH;
    }

    const int help_panel_height = 7;
    const int calendar_panel_height = 10;

    int deity_panel_height, almanac_panel_height;

    if (layout->content_height >= help_panel_height + calendar_panel_height + PANEL_GAP * 2) {
        deity_panel_height = layout->content_height - help_panel_height - PANEL_GAP;
        almanac_panel_height = layout->content_height - calendar_panel_height - PANEL_GAP;
    } else {
        deity_panel_height = layout->content_height / 2;
        almanac_panel_height = layout->content_height / 2;
    }

    panels->left_panel.y = layout->header_height;
    panels->left_panel.x = CONTENT_PADDING + OUTER_BORDER_PADDING;
    panels->left_panel.height = deity_panel_height;
    panels->left_panel.width = LEFT_PANEL_WIDTH;

    panels->center_panel.y = layout->header_height;
    panels->center_panel.x = CONTENT_PADDING + OUTER_BORDER_PADDING + LEFT_PANEL_WIDTH + PANEL_GAP;
    panels->center_panel.height = layout->content_height;
    panels->center_panel.width = center_panel_width;

    panels->right_panel.y = layout->header_height;
    panels->right_panel.x = CONTENT_PADDING + OUTER_BORDER_PADDING + LEFT_PANEL_WIDTH + center_panel_width + PANEL_GAP * 2;
    panels->right_panel.height = almanac_panel_height;
    panels->right_panel.width = RIGHT_PANEL_WIDTH;

    panels->calendar_panel.y = layout->header_height + almanac_panel_height + PANEL_GAP;
    panels->calendar_panel.x = CONTENT_PADDING + OUTER_BORDER_PADDING + LEFT_PANEL_WIDTH + center_panel_width + PANEL_GAP * 2;
    panels->calendar_panel.height = calendar_panel_height;
    panels->calendar_panel.width = RIGHT_PANEL_WIDTH;

    panels->help_panel.y = layout->header_height + deity_panel_height + PANEL_GAP;
    panels->help_panel.x = CONTENT_PADDING + OUTER_BORDER_PADDING;
    panels->help_panel.height = help_panel_height;
    panels->help_panel.width = LEFT_PANEL_WIDTH;

    panels->footer.y = layout->height - layout->footer_height;
    panels->footer.x = 0;
    panels->footer.height = layout->footer_height;
    panels->footer.width = layout->width;
}

void layout_draw_separator(int y, int x, int width) {
    for (int i = 0; i < width; i++) {
        mvprintw(y, x + i, "─");
    }
}

Rect layout_get_content_rect(const Rect *border_rect, int padding) {
    Rect content_rect;
    content_rect.y = border_rect->y + padding + 1;
    content_rect.x = border_rect->x + padding + 1;
    content_rect.height = border_rect->height - 2 * (padding + 1);
    content_rect.width = border_rect->width - 2 * (padding + 1);
    return content_rect;
}
