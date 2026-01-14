#include "ui/components/ui_components.h"
#include "ui/visual/big_numbers.h"
#include "ui/visual/chinese_border.h"
#include "utils/constants.h"
#include <string.h>

static const char *weekday_names[] = {"日", "一", "二", "三", "四", "五", "六"};

void draw_box(int y, int x, int height, int width) {
    if (width < 2 || height < 2) {
        return;
    }

    // Use Chinese border with DECORATED style (recommended)
    BorderConfig config = {
        .y = y,
        .x = x,
        .height = height,
        .width = width,
        .style = BORDER_STYLE_DECORATED,
        .color_pair = 0,
        .padding = OUTER_BORDER_PADDING
    };
    chinese_border_draw(&config);
}

void ui_draw_label(int y, int x, const char *text, int color_pair) {
    if (color_pair > 0) attron(COLOR_PAIR(color_pair));
    mvprintw(y, x, "%s", text);
    if (color_pair > 0) attroff(COLOR_PAIR(color_pair));
}

void ui_draw_header(const Rect *rect) {
    mvprintw(rect->y, rect->x + (rect->width - 10) / 2, "中国传统农历黄历");
}

void ui_draw_footer(const Rect *rect __attribute__((unused))) {}

void ui_draw_help_panel(const Rect *rect) {
    const int y = rect->y + 1;
    const int x = rect->x + 1;
    const int max_y = rect->y + rect->height - 1;

    if (y <= max_y)
        mvprintw(y, x, "导航: h/j/k/l 上/下/左/右");
    if (y + 1 <= max_y)
        mvprintw(y + 1, x, "      Ctrl+F/B 上一/下一月");
    if (y + 2 <= max_y)
        mvprintw(y + 2, x, "显示: m 切换日历");
    if (y + 3 <= max_y)
        mvprintw(y + 3, x, "      d 切换神仙");
    if (y + 4 <= max_y)
        mvprintw(y + 4, x, "退出: q 或 Esc");
}

void ui_draw_left_panel(const Rect *rect, const Date *date) {
    const int y = rect->y + 1;
    const int x = rect->x;
    const int deity_art_height = 16;
    const int deity_label_gap = 2;

    static AnimationState deity_anim_state;
    static DeityType last_deity = -1;
    static int anim_initialized = 0;

    DeityType deity = get_daily_deity(date);

    if (!anim_initialized || deity != last_deity) {
        deity_animation_init(&deity_anim_state, 3, 300);
        anim_initialized = 1;
        last_deity = deity;
    }

    deity_draw(stdscr, y, x, deity, &deity_anim_state);

    const int deity_label_y = y + deity_art_height + deity_label_gap;
    const char* deity_name = deity_get_name(deity);
    const int deity_label_x = x + (rect->width - strlen(deity_name) - strlen("守护")) / 2;
    mvprintw(deity_label_y, deity_label_x, "%s守护", deity_name);
}

void ui_draw_center_panel(const Rect *rect, const Date *date) {
    const int date_width = big_number_get_day_width(date->day);
    const int weekday_idx = date_to_weekday(date);
    const int valid_weekday = (weekday_idx >= 0 && weekday_idx < 7);

    int text_width;
    const char *weekday_str = valid_weekday ? weekday_names[weekday_idx] : "?";

    text_width = snprintf(NULL, 0, "%d年%d月 星期%s", date->year, date->month, weekday_str);

    const int max_width = (date_width > text_width) ? date_width : text_width;
    const int centered_x = rect->x + (rect->width - max_width) / 2;

    const int top_y = rect->y + 1;

    if (valid_weekday) {
        mvprintw(top_y, centered_x, "%d年%d月 星期%s", date->year, date->month, weekday_names[weekday_idx]);
    }
    big_number_draw_day(stdscr, top_y + 3, centered_x, date->day);
}

void draw_calendar_grid(int y, int x, const Date *date, int max_y) {
    mvprintw(y, x + 12, "%d年%d月", date->year, date->month);
    mvprintw(y + 1, x, "日 一 二 三 四 五 六");

    Date first_day = {date->year, date->month, 1};
    const int first_weekday = date_to_weekday(&first_day);
    const int days_in_month = date_days_in_month(date);
    const int row = y + 2;

    for (int day = 1; day <= days_in_month; day++) {
        const int col = x + ((first_weekday + day - 1) % 7) * 3;
        const int row_pos = row + (first_weekday + day - 1) / 7;

        if (row_pos > max_y) break;

        if (day == date->day) attron(A_REVERSE);
        mvprintw(row_pos, col, "%2d", day);
        if (day == date->day) attroff(A_REVERSE);
    }
}

void ui_draw_right_panel(const Rect *rect, const Date *date __attribute__((unused)), const LunarDate *lunar,
                         const Almanac *alm, int mode __attribute__((unused))) {
    const int y = rect->y + 1;
    const int x = rect->x + 2;
    static const char *lunar_months[] = {"", "正", "二", "三", "四", "五", "六", "七", "八", "九", "十", "十一", "腊"};
    const int month_idx = (lunar->month >= 1 && lunar->month <= 12) ? lunar->month : 0;

    mvprintw(y, x, "农历: %s年%s%s月%d日",
             lunar->ganzhi_year, lunar->is_leap ? "闰" : "",
             lunar_months[month_idx], lunar->day);
    mvprintw(y + 1, x, "生肖: %s", lunar->zodiac);
    mvprintw(y + 2, x, "干支: %s", lunar->ganzhi_day);

    if (lunar->solar_term >= 0) {
        attron(COLOR_PAIR(COLOR_PAIR_YELLOW));
        mvprintw(y + 3, x, "节气: %s", lunar->solar_term_name);
        attroff(COLOR_PAIR(COLOR_PAIR_YELLOW));
    }

    BorderConfig border = {
        .style = BORDER_STYLE_DECORATED,
        .color_pair = 0,
        .padding = 1
    };

    border.y = y + 5;
    border.x = x - 2;
    border.height = 3;
    border.width = 35;
    chinese_border_draw(&border);
    attron(COLOR_PAIR(COLOR_PAIR_GREEN));
    mvprintw(y + 5, x + 16, "宜");
    attroff(COLOR_PAIR(COLOR_PAIR_GREEN));
    mvprintw(y + 6, x, " %s", alm->yi);

    border.y = y + 9;
    chinese_border_draw(&border);
    attron(COLOR_PAIR(COLOR_PAIR_RED));
    mvprintw(y + 9, x + 16, "忌");
    attroff(COLOR_PAIR(COLOR_PAIR_RED));
    mvprintw(y + 10, x, " %s", alm->ji);

    attron(COLOR_PAIR(COLOR_PAIR_YELLOW));
    mvprintw(y + 12, x, "冲煞: %s", alm->chong);
    attroff(COLOR_PAIR(COLOR_PAIR_YELLOW));
    mvprintw(y + 13, x, "财神:%s", alm->chaishen);
    mvprintw(y + 14, x, "喜神:%s  福神:%s", alm->xishen, alm->fushen);
    mvprintw(y + 15, x, "吉神: %s", alm->jishen);
    mvprintw(y + 16, x, "凶煞: %s", alm->xiongsha);
    mvprintw(y + 17, x, "彭祖: %s", alm->pengzu);
}

void ui_draw_calendar_panel(const Rect *rect, const Date *date) {
    const int y = rect->y + 1;
    const int x = rect->x + 2;
    const int max_y = rect->y + rect->height - 1;

    if (rect->height < 9) {
        mvprintw(y, x, "空间不足");
        return;
    }

    draw_calendar_grid(y, x, date, max_y);
}

void ui_draw_outer_border(int height, int width) {
    if (height < 3 || width < 3) {
        return;
    }

    const int y = 0;
    const int x = 0;

    BorderConfig config = {
        .y = y,
        .x = x,
        .height = height,
        .width = width,
        .style = BORDER_STYLE_DECORATED,
        .color_pair = 0,
        .padding = OUTER_BORDER_PADDING
    };
    chinese_border_draw(&config);
}
