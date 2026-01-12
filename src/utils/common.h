#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

typedef struct {
    int year;
    int month;
    int day;
} Date;

void date_init(Date *date, int year, int month, int day);
void date_copy(Date *dst, const Date *src);
int date_compare(const Date *a, const Date *b);
void date_add_days(Date *date, int days);
void date_add_months(Date *date, int months);
int date_days_in_month(const Date *date);
int date_is_leap_year(int year);
int date_to_weekday(const Date *date);
int date_to_day_of_year(const Date *date);
void date_to_today(Date *date);

void animation_page_turn(Date *date, int direction);
int handle_input(int ch, Date *date, int *mode, int *needs_redraw);

#endif
