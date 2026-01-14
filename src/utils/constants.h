#ifndef CONSTANTS_H
#define CONSTANTS_H

/* Terminal dimensions */
#define MIN_TERMINAL_HEIGHT 10
#define MIN_TERMINAL_WIDTH 50

/* UI layout dimensions */
#define HEADER_HEIGHT 3
#define FOOTER_HEIGHT 1
#define CONTENT_PADDING 2
#define LEFT_PANEL_WIDTH 20
#define RIGHT_PANEL_WIDTH 35
#define CALENDAR_PANEL_WIDTH 25
#define PANEL_GAP 4
#define MIN_CENTER_PANEL_WIDTH 20
#define OUTER_BORDER_PADDING 2

/* Animation settings */
#define PAGE_TURN_FRAMES 8
#define PAGE_TURN_DELAY_US 30000

/* Color pairs */
#define COLOR_PAIR_RED 1
#define COLOR_PAIR_GREEN 2
#define COLOR_PAIR_YELLOW 3

/* String buffer sizes */
#define ALMANAC_BUFFER_SIZE 512
#define ALMANAC_SHORT_SIZE 32
#define GANZHI_SIZE 10
#define ZODIAC_SIZE 10
#define SOLAR_TERM_SIZE 10

/* Array sizes */
#define GANZHI_ARRAY_SIZE 60
#define ZODIAC_ARRAY_SIZE 12
#define YI_ITEMS_COUNT 32
#define JI_ITEMS_COUNT 24
#define JISHEN_COUNT 20
#define XIONGSHA_COUNT 15
#define DIRECTIONS_COUNT 8
#define SOLAR_TERM_COUNT 24

/* Lunar calendar data bit masks */
#define LUNAR_INFO_LEAP_MONTH_MASK 0xF
#define LUNAR_INFO_LEAP_MONTH_DAY_BIT 0x10000

/* Lunar calendar constants */
#define LUNAR_MIN_YEAR 1900
#define LUNAR_MAX_YEAR 2100
#define LUNAR_MONTHS_PER_YEAR 12
#define LUNAR_MAX_MONTHS 13
#define LUNAR_DAYS_30 30
#define LUNAR_DAYS_29 29

#endif
