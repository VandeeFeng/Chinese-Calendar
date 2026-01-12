#include "utils/common.h"

void date_init(Date *date, int year, int month, int day) {
    date->year = year;
    date->month = month;
    date->day = day;
}

void date_copy(Date *dst, const Date *src) {
    dst->year = src->year;
    dst->month = src->month;
    dst->day = src->day;
}

int date_compare(const Date *a, const Date *b) {
    if (a->year != b->year) return a->year - b->year;
    if (a->month != b->month) return a->month - b->month;
    return a->day - b->day;
}

int date_is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int date_days_in_month(const Date *date) {
    static const int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (date->month == 2 && date_is_leap_year(date->year)) {
        return 29;
    }
    return days[date->month - 1];
}

int date_to_weekday(const Date *date) {
    int y = date->year;
    int m = date->month;
    int d = date->day;

    if (m < 3) {
        m += 12;
        y--;
    }

    y = y % 100;

    const int w = (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 + 1) % 7;
    return w;
}

int date_to_day_of_year(const Date *date) {
    int day = date->day;
    static const int month_days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    for (int i = 1; i < date->month; i++) {
        day += month_days[i - 1];
        if (i == 2 && date_is_leap_year(date->year)) {
            day++;
        }
    }

    return day;
}

void date_add_days(Date *date, int days) {
    date->day += days;

    while (date->day > date_days_in_month(date)) {
        date->day -= date_days_in_month(date);
        if (++date->month > 12) {
            date->month = 1;
            date->year++;
        }
    }

    while (date->day < 1) {
        if (--date->month < 1) {
            date->month = 12;
            date->year--;
        }
        date->day += date_days_in_month(date);
    }
}

void date_add_months(Date *date, int months) {
    const int year_offset = months / 12;
    const int month_offset = months % 12;

    date->year += year_offset;
    date->month += month_offset;

    if (date->month > 12) {
        date->month -= 12;
        date->year++;
    } else if (date->month < 1) {
        date->month += 12;
        date->year--;
    }

    const int max_day = date_days_in_month(date);
    if (date->day > max_day) {
        date->day = max_day;
    }
}

void date_to_today(Date *date) {
    const time_t t = time(NULL);
    struct tm *tm = localtime(&t);

    if (tm != NULL) {
        date->year = tm->tm_year + 1900;
        date->month = tm->tm_mon + 1;
        date->day = tm->tm_mday;
    }
}