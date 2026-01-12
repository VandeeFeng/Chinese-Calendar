#ifndef LUNAR_H
#define LUNAR_H

#include "utils/common.h"

extern const char *ganzhi_year[];
extern const char *ganzhi_day[];

typedef struct {
    int year;
    int month;
    int day;
    int is_leap;
    char zodiac[10];
    char ganzhi_year[10];
    char ganzhi_month[10];
    char ganzhi_day[10];
} LunarDate;

int solar_to_lunar(const Date *solar, LunarDate *lunar);
int lunar_to_solar(LunarDate *lunar __attribute__((unused)), Date *solar __attribute__((unused)));
void lunar_get_zodiac(int year, char *zodiac);
void lunar_get_ganzhi_year(int year, char *ganzhi);
void lunar_get_ganzhi_month(int year, int month, int leap __attribute__((unused)), char *ganzhi);
void lunar_get_ganzhi_day(const Date *solar, char *ganzhi);

int lunar_get_leap_month(int year);
int lunar_days_in_month(int year, int month, int leap);
int lunar_get_days_in_year(int year);

#endif
