#include <stdlib.h>
#include "calendar/lunar.h"
#include "calendar/lunar_data.h"
#include "utils/constants.h"

const char *ganzhi_year[] = {
    "甲子", "乙丑", "丙寅", "丁卯", "戊辰", "己巳", "庚午", "辛未", "壬申", "癸酉",
    "甲戌", "乙亥", "丙子", "丁丑", "戊寅", "己卯", "庚辰", "辛巳", "壬午", "癸未",
    "甲申", "乙酉", "丙戌", "丁亥", "戊子", "己丑", "庚寅", "辛卯", "壬辰", "癸巳",
    "甲午", "乙未", "丙申", "丁酉", "戊戌", "己亥", "庚子", "辛丑", "壬寅", "癸卯",
    "甲辰", "乙巳", "丙午", "丁未", "戊申", "己酉", "庚戌", "辛亥", "壬子", "癸丑",
    "甲寅", "乙卯", "丙辰", "丁巳", "戊午", "己未", "庚申", "辛酉", "壬戌", "癸亥"
};

const char *ganzhi_day[] = {
    "甲子", "乙丑", "丙寅", "丁卯", "戊辰", "己巳", "庚午", "辛未", "壬申", "癸酉",
    "甲戌", "乙亥", "丙子", "丁丑", "戊寅", "己卯", "庚辰", "辛巳", "壬午", "癸未",
    "甲申", "乙酉", "丙戌", "丁亥", "戊子", "己丑", "庚寅", "辛卯", "壬辰", "癸巳",
    "甲午", "乙未", "丙申", "丁酉", "戊戌", "己亥", "庚子", "辛丑", "壬寅", "癸卯",
    "甲辰", "乙巳", "丙午", "丁未", "戊申", "己酉", "庚戌", "辛亥", "壬子", "癸丑",
    "甲寅", "乙卯", "丙辰", "丁巳", "戊午", "己未", "庚申", "辛酉", "壬戌", "癸亥"
};

static const char *zodiac_animal[] = {
    "鼠", "牛", "虎", "兔", "龙", "蛇", "马", "羊", "猴", "鸡", "狗", "猪"
};

static const int month_add[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};

static int get_lunar_month_days(unsigned int lunar_info, int month_index) {
    if (month_index < 1 || month_index > LUNAR_MAX_MONTHS) {
        return LUNAR_DAYS_29;
    }
    return (lunar_info & (LUNAR_INFO_MONTH_DAY_MASK >> (month_index - 1))) ? LUNAR_DAYS_30 : LUNAR_DAYS_29;
}

static int get_leap_month(unsigned int lunar_info) {
    return (lunar_info >> LUNAR_INFO_LEAP_MONTH_SHIFT) & LUNAR_INFO_LEAP_MONTH_MASK;
}

static int calculate_spring_day_offset(unsigned int lunar_info) {
    const int spring_month = lunar_info & LUNAR_INFO_SPRING_MONTH_MASK;
    const int spring_day = (lunar_info >> 4) & LUNAR_INFO_SPRING_DAY_MASK;
    return (spring_month == 1) ? spring_day - 1 : SOLAR_DAYS_IN_JANUARY + spring_day - 1;
}

static int calculate_solar_day_offset(const Date *solar) {
    int offset = month_add[solar->month - 1] + solar->day - 1;

    if (date_is_leap_year(solar->year) && solar->month > 2) {
        offset++;
    }

    return offset;
}

static void calculate_after_spring(const Date *solar, int sun_ny, LunarDate *lunar) {
    const int year_index = solar->year - LUNAR_MIN_YEAR;
    const unsigned int lunar_info = lunar_data[year_index];
    const int leap_month = get_leap_month(lunar_info);

    lunar->month = 1;
    int month_index = 1;
    int leap_flag = 0;

    int days_in_month = get_lunar_month_days(lunar_info, month_index);

    while (sun_ny >= days_in_month) {
        sun_ny -= days_in_month;
        month_index++;

        if (month_index > LUNAR_MAX_MONTHS) {
            return;
        }

        if (lunar->month == leap_month) {
            leap_flag = ~leap_flag;
            if (leap_flag == 0) lunar->month++;
        } else {
            lunar->month++;
        }

        days_in_month = get_lunar_month_days(lunar_info, month_index);
    }

    lunar->day = sun_ny + 1;
    lunar->is_leap = (lunar->month == leap_month && leap_flag) ? 1 : 0;

    if (lunar->month > LUNAR_MONTHS_PER_YEAR) {
        lunar->month -= LUNAR_MONTHS_PER_YEAR;
    }
}

static void calculate_before_spring(int spring_ny, LunarDate *lunar) {
    lunar->year--;

    if (lunar->year < LUNAR_MIN_YEAR) {
        return;
    }

    const unsigned int prev_lunar_info = lunar_data[lunar->year - LUNAR_MIN_YEAR];
    const int leap_month = get_leap_month(prev_lunar_info);

    lunar->month = 12;
    int month_index = (leap_month == 0) ? 12 : LUNAR_MAX_MONTHS;
    int leap_flag = 0;

    int days_in_month = get_lunar_month_days(prev_lunar_info, month_index);

    while (spring_ny > days_in_month) {
        spring_ny -= days_in_month;
        month_index--;

        if (month_index < 1) {
            return;
        }

        if (leap_flag == 0) lunar->month--;

        if (lunar->month == leap_month) leap_flag = ~leap_flag;

        days_in_month = get_lunar_month_days(prev_lunar_info, month_index);
    }

    lunar->day = days_in_month - spring_ny + 1;
    lunar->is_leap = (lunar->month == leap_month && leap_flag) ? 1 : 0;
}

int solar_to_lunar(const Date *solar, LunarDate *lunar) {
    if (solar->year < LUNAR_MIN_YEAR || solar->year > LUNAR_MAX_YEAR) {
        return -1;
    }

    lunar->year = solar->year;

    const unsigned int lunar_info = lunar_data[lunar->year - LUNAR_MIN_YEAR];
    const int spring_ny = calculate_spring_day_offset(lunar_info);
    const int sun_ny = calculate_solar_day_offset(solar);

    if (sun_ny >= spring_ny) {
        calculate_after_spring(solar, sun_ny - spring_ny, lunar);
    } else {
        calculate_before_spring(spring_ny - sun_ny, lunar);
    }

    lunar_get_zodiac(lunar->year, lunar->zodiac);
    lunar_get_ganzhi_year(lunar->year, lunar->ganzhi_year);
    lunar_get_ganzhi_day(solar, lunar->ganzhi_day);

    return 0;
}

int lunar_to_solar(LunarDate *lunar __attribute__((unused)), Date *solar __attribute__((unused))) {
    return 0;
}

void lunar_get_zodiac(int year, char *zodiac) {
    int offset = (year - 4) % 12;
    if (offset < 0) offset += 12;

    strncpy(zodiac, zodiac_animal[offset], ZODIAC_SIZE - 1);
    zodiac[ZODIAC_SIZE - 1] = '\0';
}

void lunar_get_ganzhi_year(int year, char *ganzhi) {
    int offset = (year - 4) % 60;
    if (offset < 0) offset += 60;

    strncpy(ganzhi, ganzhi_year[offset], GANZHI_SIZE - 1);
    ganzhi[GANZHI_SIZE - 1] = '\0';
}

void lunar_get_ganzhi_month(int year, int month, int leap __attribute__((unused)), char *ganzhi) {
    int year_offset = (year - 4) % 60;
    if (year_offset < 0) year_offset += 60;

    int month_idx = month - 1;
    if (month_idx < 0) month_idx += 12;

    const int ganzhi_month_idx = (year_offset * 12 + month_idx) % 60;
    strncpy(ganzhi, ganzhi_year[ganzhi_month_idx], GANZHI_SIZE - 1);
    ganzhi[GANZHI_SIZE - 1] = '\0';
}

void lunar_get_ganzhi_day(const Date *solar, char *ganzhi) {
    const Date base_date = {1900, 1, 31};
    long days_diff = 0;

    for (int y = base_date.year; y < solar->year; y++) {
        days_diff += ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)) ? 366 : 365;
    }

    days_diff += date_to_day_of_year(solar) - 31;

    int offset = days_diff % 60;
    if (offset < 0) offset += 60;

    strncpy(ganzhi, ganzhi_day[offset], GANZHI_SIZE - 1);
    ganzhi[GANZHI_SIZE - 1] = '\0';
}

int lunar_get_leap_month(int year) {
    if (year < LUNAR_MIN_YEAR || year > LUNAR_MAX_YEAR) return 0;
    const int year_index = year - LUNAR_MIN_YEAR;
    return (lunar_data[year_index] >> LUNAR_INFO_LEAP_MONTH_SHIFT) & LUNAR_INFO_LEAP_MONTH_MASK;
}

int lunar_days_in_month(int year, int month, int leap) {
    if (year < LUNAR_MIN_YEAR || year > LUNAR_MAX_YEAR) return 0;
    if (month < 1 || month > LUNAR_MONTHS_PER_YEAR) return 0;

    const int year_index = year - LUNAR_MIN_YEAR;
    const unsigned int lunar_info = lunar_data[year_index];
    const int leap_month = get_leap_month(lunar_info);

    if (leap && month != leap_month) return 0;

    const int month_index = leap && month == leap_month ? LUNAR_MAX_MONTHS : month;
    return (lunar_info & (LUNAR_INFO_MONTH_DAY_MASK >> (month_index - 1))) ? LUNAR_DAYS_30 : LUNAR_DAYS_29;
}

int lunar_get_days_in_year(int year) {
    if (year < LUNAR_MIN_YEAR || year > LUNAR_MAX_YEAR) return 0;

    int total = 0;
    for (int i = 1; i <= LUNAR_MONTHS_PER_YEAR; i++) {
        total += lunar_days_in_month(year, i, 0);
    }

    const int leap_month = lunar_get_leap_month(year);
    if (leap_month > 0) {
        total += lunar_days_in_month(year, leap_month, 1);
    }

    return total;
}