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

static const int solar_month_days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

static int is_solar_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

static int solar_days_in_month(int year, int month) {
    if (month == 2 && is_solar_leap_year(year)) {
        return 29;
    }
    return solar_month_days[month];
}

static unsigned int get_lunar_info(int year) {
    if (year < LUNAR_MIN_YEAR || year > LUNAR_MAX_YEAR) {
        return 0;
    }
    return lunar_data[year - LUNAR_MIN_YEAR];
}

static int lunar_leap_month(int year) {
    return get_lunar_info(year) & LUNAR_INFO_LEAP_MONTH_MASK;
}

static int lunar_leap_month_days(int year) {
    unsigned int info = get_lunar_info(year);
    if (lunar_leap_month(year) == 0) {
        return 0;
    }
    return (info & LUNAR_INFO_LEAP_MONTH_DAY_BIT) ? LUNAR_DAYS_30 : LUNAR_DAYS_29;
}

static int lunar_month_days(int year, int month) {
    unsigned int info = get_lunar_info(year);
    if ((info & (LUNAR_INFO_LEAP_MONTH_DAY_BIT >> month)) == 0) {
        return LUNAR_DAYS_29;
    }
    return LUNAR_DAYS_30;
}

static int lunar_total_days(int year) {
    int total = 0;
    for (int i = 1; i <= LUNAR_MONTHS_PER_YEAR; i++) {
        total += lunar_month_days(year, i);
    }
    total += lunar_leap_month_days(year);
    return total;
}

static int days_from_1900_1_31(int year, int month, int day) {
    int days = 0;

    for (int m = 1; m < month; m++) {
        days += solar_days_in_month(year, m);
    }

    days += (year - 1900) * 365 + (year - 1900) / 4 + day - 31;

    if (is_solar_leap_year(year) && month != 12 && day != 31) {
        days -= 1;
    }

    return days;
}

int solar_to_lunar(const Date *solar, LunarDate *lunar) {
    if (solar->year < LUNAR_MIN_YEAR || solar->year > LUNAR_MAX_YEAR) {
        return -1;
    }

    int all_days = days_from_1900_1_31(solar->year, solar->month, solar->day);
    int year;
    int leap_month;
    int is_leap = 0;
    int days_in_month;

    for (year = 1900; all_days >= lunar_total_days(year); year++) {
        all_days -= lunar_total_days(year);
    }

    lunar->year = year;
    leap_month = lunar_leap_month(year);

    for (int month = 1; month <= LUNAR_MONTHS_PER_YEAR; month++) {
        if (leap_month > 0 && month == (leap_month + 1) && !is_leap) {
            month--;
            is_leap = 1;
            days_in_month = lunar_leap_month_days(year);
        } else {
            days_in_month = lunar_month_days(year, month);
        }

        if (is_leap && month == leap_month + 1) {
            is_leap = 0;
        }

        if (all_days < days_in_month) {
            lunar->month = month;
            lunar->day = all_days + 1;
            lunar->is_leap = (leap_month > 0 && month == leap_month && is_leap) ? 1 : 0;
            break;
        }

        all_days -= days_in_month;
    }

    lunar_get_zodiac(lunar->year, lunar->zodiac);
    lunar_get_ganzhi_year(lunar->year, lunar->ganzhi_year);
    lunar_get_ganzhi_day(solar, lunar->ganzhi_day);

    return 0;
}

int lunar_to_solar(LunarDate *lunar, Date *solar) {
    (void)lunar;
    (void)solar;
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

void lunar_get_ganzhi_day(const Date *solar, char *ganzhi) {
    const Date base_date = {1900, 1, 31};
    long days_diff = 0;

    for (int y = base_date.year; y < solar->year; y++) {
        days_diff += is_solar_leap_year(y) ? 366 : 365;
    }

    for (int m = 1; m < solar->month; m++) {
        days_diff += solar_days_in_month(solar->year, m);
    }

    days_diff += solar->day - base_date.day;

    int offset = days_diff % 60;
    if (offset < 0) offset += 60;

    strncpy(ganzhi, ganzhi_day[offset], GANZHI_SIZE - 1);
    ganzhi[GANZHI_SIZE - 1] = '\0';
}

