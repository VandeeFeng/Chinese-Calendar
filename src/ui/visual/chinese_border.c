#include "chinese_border.h"

static const char *DOUBLE_TOP_LEFT = "╔";
static const char *DOUBLE_TOP_RIGHT = "╗";
static const char *DOUBLE_BOTTOM_LEFT = "╚";
static const char *DOUBLE_BOTTOM_RIGHT = "╝";
static const char *DOUBLE_HORIZONTAL = "═";
static const char *DOUBLE_VERTICAL = "║";

static const char *CLOUD_DECORATION = "❀";
static const char *CLOUD_FILLED = "●";
static const char *MEIHUA_FLOWER = "✿";
static const char *MOSAIC_PATTERN = "◆";

#define CLOUD_PERIOD 8
#define MEIHUA_PERIOD 6
#define MOSAIC_PERIOD 5

void chinese_border_draw_top(int y, int x, int width, BorderStyle style, int color_pair) {
    if (width < 2) return;

    if (color_pair > 0) {
        attron(COLOR_PAIR(color_pair));
    }

    mvprintw(y, x, "%s", DOUBLE_TOP_LEFT);

    switch (style) {
        case BORDER_STYLE_SIMPLE:
            for (int i = 1; i < width - 1; i++) {
                mvprintw(y, x + i, "%s", DOUBLE_HORIZONTAL);
            }
            break;

        case BORDER_STYLE_CLOUD:
            for (int i = 1; i < width - 1; i++) {
                if ((i - 1) % CLOUD_PERIOD == 0 && i > 1 && i < width - 2) {
                    mvprintw(y, x + i, "%s", CLOUD_DECORATION);
                    i++;
                } else {
                    mvprintw(y, x + i, "%s", DOUBLE_HORIZONTAL);
                }
            }
            break;

        case BORDER_STYLE_MEIHUA:
            for (int i = 1; i < width - 1; i++) {
                if ((i - 1) % MEIHUA_PERIOD == 0 && i > 1 && i < width - 2) {
                    mvprintw(y, x + i, "%s", MEIHUA_FLOWER);
                    i++;
                } else {
                    mvprintw(y, x + i, "%s", DOUBLE_HORIZONTAL);
                }
            }
            break;

        case BORDER_STYLE_MOSAIC:
            for (int i = 1; i < width - 1; i++) {
                if ((i - 1) % MOSAIC_PERIOD == 0 && i > 1 && i < width - 2) {
                    mvprintw(y, x + i, "%s", MOSAIC_PATTERN);
                    i++;
                } else {
                    mvprintw(y, x + i, "%s", DOUBLE_HORIZONTAL);
                }
            }
            break;

        case BORDER_STYLE_DECORATED:
            for (int i = 1; i < width - 1; i++) {
                if ((i - 1) % CLOUD_PERIOD == 0 && i > 1 && i < width - 2) {
                    mvprintw(y, x + i, "%s", CLOUD_DECORATION);
                    i++;
                } else if ((i - 1) % (CLOUD_PERIOD / 2) == 0 && i > 1 && i < width - 2) {
                    mvprintw(y, x + i, "%s", CLOUD_FILLED);
                    i++;
                } else {
                    mvprintw(y, x + i, "%s", DOUBLE_HORIZONTAL);
                }
            }
            break;

        default:
            for (int i = 1; i < width - 1; i++) {
                mvprintw(y, x + i, "%s", DOUBLE_HORIZONTAL);
            }
            break;
    }

    mvprintw(y, x + width - 1, "%s", DOUBLE_TOP_RIGHT);

    if (color_pair > 0) {
        attroff(COLOR_PAIR(color_pair));
    }
}

void chinese_border_draw_bottom(int y, int x, int width, BorderStyle style, int color_pair) {
    if (width < 2) return;

    if (color_pair > 0) {
        attron(COLOR_PAIR(color_pair));
    }

    mvprintw(y, x, "%s", DOUBLE_BOTTOM_LEFT);

    switch (style) {
        case BORDER_STYLE_SIMPLE:
            for (int i = 1; i < width - 1; i++) {
                mvprintw(y, x + i, "%s", DOUBLE_HORIZONTAL);
            }
            break;

        case BORDER_STYLE_CLOUD:
            for (int i = 1; i < width - 1; i++) {
                if ((i - 1) % CLOUD_PERIOD == 0 && i > 1 && i < width - 2) {
                    mvprintw(y, x + i, "%s", CLOUD_DECORATION);
                    i++;
                } else {
                    mvprintw(y, x + i, "%s", DOUBLE_HORIZONTAL);
                }
            }
            break;

        case BORDER_STYLE_MEIHUA:
            for (int i = 1; i < width - 1; i++) {
                if ((i - 1) % MEIHUA_PERIOD == 0 && i > 1 && i < width - 2) {
                    mvprintw(y, x + i, "%s", MEIHUA_FLOWER);
                    i++;
                } else {
                    mvprintw(y, x + i, "%s", DOUBLE_HORIZONTAL);
                }
            }
            break;

        case BORDER_STYLE_MOSAIC:
            for (int i = 1; i < width - 1; i++) {
                if ((i - 1) % MOSAIC_PERIOD == 0 && i > 1 && i < width - 2) {
                    mvprintw(y, x + i, "%s", MOSAIC_PATTERN);
                    i++;
                } else {
                    mvprintw(y, x + i, "%s", DOUBLE_HORIZONTAL);
                }
            }
            break;

        case BORDER_STYLE_DECORATED:
            for (int i = 1; i < width - 1; i++) {
                if ((i - 1) % CLOUD_PERIOD == 0 && i > 1 && i < width - 2) {
                    mvprintw(y, x + i, "%s", CLOUD_DECORATION);
                    i++;
                } else if ((i - 1) % (CLOUD_PERIOD / 2) == 0 && i > 1 && i < width - 2) {
                    mvprintw(y, x + i, "%s", CLOUD_FILLED);
                    i++;
                } else {
                    mvprintw(y, x + i, "%s", DOUBLE_HORIZONTAL);
                }
            }
            break;

        default:
            for (int i = 1; i < width - 1; i++) {
                mvprintw(y, x + i, "%s", DOUBLE_HORIZONTAL);
            }
            break;
    }

    mvprintw(y, x + width - 1, "%s", DOUBLE_BOTTOM_RIGHT);

    if (color_pair > 0) {
        attroff(COLOR_PAIR(color_pair));
    }
}

void chinese_border_draw_left(int y, int x, int height, BorderStyle style __attribute__((unused)), int color_pair, int padding __attribute__((unused))) {
    if (height < 2) return;

    if (color_pair > 0) {
        attron(COLOR_PAIR(color_pair));
    }

    for (int i = 0; i < height; i++) {
        mvprintw(y + i, x, "%s", DOUBLE_VERTICAL);
    }

    if (color_pair > 0) {
        attroff(COLOR_PAIR(color_pair));
    }
}

void chinese_border_draw_right(int y, int x, int height, BorderStyle style __attribute__((unused)), int color_pair, int padding __attribute__((unused))) {
    if (height < 2) return;

    if (color_pair > 0) {
        attron(COLOR_PAIR(color_pair));
    }

    for (int i = 0; i < height; i++) {
        mvprintw(y + i, x, "%s", DOUBLE_VERTICAL);
    }

    if (color_pair > 0) {
        attroff(COLOR_PAIR(color_pair));
    }
}

void chinese_border_draw_corners(int y, int x, int height, int width, BorderStyle style, int color_pair) {
    (void)style; // Unused parameter (corners are the same for all styles)
    if (height < 2 || width < 2) return;

    if (color_pair > 0) {
        attron(COLOR_PAIR(color_pair));
    }

    mvprintw(y, x, "%s", DOUBLE_TOP_LEFT);
    mvprintw(y, x + width - 1, "%s", DOUBLE_TOP_RIGHT);
    mvprintw(y + height - 1, x, "%s", DOUBLE_BOTTOM_LEFT);
    mvprintw(y + height - 1, x + width - 1, "%s", DOUBLE_BOTTOM_RIGHT);

    if (color_pair > 0) {
        attroff(COLOR_PAIR(color_pair));
    }
}

void chinese_border_draw(const BorderConfig *config) {
    if (!config || config->height < 2 || config->width < 2) {
        return;
    }

    int padding = config->padding;

    // Check terminal bounds
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    if (config->y + config->height > max_y || config->x + config->width > max_x) {
        return;
    }

    chinese_border_draw_top(config->y, config->x, config->width, config->style, config->color_pair);

    chinese_border_draw_bottom(config->y + config->height - 1, config->x, config->width,
                                config->style, config->color_pair);

    chinese_border_draw_left(config->y + 1, config->x, config->height - 2,
                               config->style, config->color_pair, padding);

    chinese_border_draw_right(config->y + 1, config->x + config->width - 1, config->height - 2,
                                 config->style, config->color_pair, padding);
}

void chinese_border_draw_separator(int y, int x, int width, BorderStyle style, int color_pair) {
    if (width < 2) return;

    if (color_pair > 0) {
        attron(COLOR_PAIR(color_pair));
    }

    mvprintw(y, x, "╟");

    switch (style) {
        case BORDER_STYLE_SIMPLE:
            for (int i = 1; i < width - 1; i++) {
                mvprintw(y, x + i, "%s", DOUBLE_HORIZONTAL);
            }
            break;

        case BORDER_STYLE_CLOUD:
            for (int i = 1; i < width - 1; i++) {
                if ((i - 1) % CLOUD_PERIOD == 0 && i > 1 && i < width - 2) {
                    mvprintw(y, x + i, "%s", CLOUD_DECORATION);
                    i++;
                } else {
                    mvprintw(y, x + i, "%s", DOUBLE_HORIZONTAL);
                }
            }
            break;

        case BORDER_STYLE_MEIHUA:
            for (int i = 1; i < width - 1; i++) {
                if ((i - 1) % MEIHUA_PERIOD == 0 && i > 1 && i < width - 2) {
                    mvprintw(y, x + i, "%s", MEIHUA_FLOWER);
                    i++;
                } else {
                    mvprintw(y, x + i, "%s", DOUBLE_HORIZONTAL);
                }
            }
            break;

        case BORDER_STYLE_MOSAIC:
            for (int i = 1; i < width - 1; i++) {
                if ((i - 1) % MOSAIC_PERIOD == 0 && i > 1 && i < width - 2) {
                    mvprintw(y, x + i, "%s", MOSAIC_PATTERN);
                    i++;
                } else {
                    mvprintw(y, x + i, "%s", DOUBLE_HORIZONTAL);
                }
            }
            break;

        case BORDER_STYLE_DECORATED:
            for (int i = 1; i < width - 1; i++) {
                if ((i - 1) % CLOUD_PERIOD == 0 && i > 1 && i < width - 2) {
                    mvprintw(y, x + i, "%s", CLOUD_DECORATION);
                    i++;
                } else if ((i - 1) % (CLOUD_PERIOD / 2) == 0 && i > 1 && i < width - 2) {
                    mvprintw(y, x + i, "%s", CLOUD_FILLED);
                    i++;
                } else {
                    mvprintw(y, x + i, "%s", DOUBLE_HORIZONTAL);
                }
            }
            break;

        default:
            for (int i = 1; i < width - 1; i++) {
                mvprintw(y, x + i, "%s", DOUBLE_HORIZONTAL);
            }
            break;
    }

    mvprintw(y, x + width - 1, "╢");

    if (color_pair > 0) {
        attroff(COLOR_PAIR(color_pair));
    }
}
