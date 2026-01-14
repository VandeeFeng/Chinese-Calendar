#include <ncurses.h>
#include "ui/visual/chinese_border.h"

// Color definitions
#define COLOR_RED     1
#define COLOR_GREEN   2
#define COLOR_YELLOW  3
#define COLOR_BLUE    4
#define COLOR_MAGENTA 5
#define COLOR_CYAN    6

int main(void) {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    // Initialize colors
    if (has_colors()) {
        start_color();
        init_pair(COLOR_RED, COLOR_RED, COLOR_BLACK);
        init_pair(COLOR_GREEN, COLOR_GREEN, COLOR_BLACK);
        init_pair(COLOR_YELLOW, COLOR_YELLOW, COLOR_BLACK);
        init_pair(COLOR_BLUE, COLOR_BLUE, COLOR_BLACK);
        init_pair(COLOR_MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(COLOR_CYAN, COLOR_CYAN, COLOR_BLACK);
    }

    int y = 2;
    int x = 5;
    int height = 8;
    int width = 40;

    clear();
    mvprintw(0, 0, "中式传统边框样式展示 (Chinese Border Styles)");

    // Style 1: Simple (双线框)
    mvprintw(y, x, "1. SIMPLE - 双线框");
    BorderConfig simple = {y + 1, x, height, width, BORDER_STYLE_SIMPLE, 0, 0};
    chinese_border_draw(&simple);

    // Style 2: Cloud (祥云纹)
    mvprintw(y + height + 2, x, "2. CLOUD - 祥云纹");
    BorderConfig cloud = {y + height + 3, x, height, width, BORDER_STYLE_CLOUD, COLOR_RED, 0};
    chinese_border_draw(&cloud);

    // Style 3: Meihua (梅花纹)
    mvprintw(y + height * 2 + 4, x, "3. MEIHUA - 梅花纹");
    BorderConfig meihua = {y + height * 2 + 5, x, height, width, BORDER_STYLE_MEIHUA, COLOR_YELLOW, 0};
    chinese_border_draw(&meihua);

    // Style 4: Mosaic (镶嵌式)
    mvprintw(y + height * 3 + 6, x, "4. MOSAIC - 镶嵌式");
    BorderConfig mosaic = {y + height * 3 + 7, x, height, width, BORDER_STYLE_MOSAIC, COLOR_BLUE, 0};
    chinese_border_draw(&mosaic);

    // Style 5: Decorated (混合装饰 - 推荐)
    mvprintw(y + height * 4 + 8, x, "5. DECORATED - 混合装饰 (推荐)");
    BorderConfig decorated = {y + height * 4 + 9, x, height, width, BORDER_STYLE_DECORATED, COLOR_CYAN, 0};
    chinese_border_draw(&decorated);

    // Draw separator line
    mvprintw(y + height * 5 + 10, x, "分隔线示例");
    chinese_border_draw_separator(y + height * 5 + 11, x, width, BORDER_STYLE_DECORATED, COLOR_MAGENTA);

    mvprintw(y + height * 5 + 13, 0, "按任意键退出...");
    refresh();

    getch();
    endwin();
    return 0;
}
