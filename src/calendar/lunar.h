#ifndef LUNAR_H
#define LUNAR_H

#include "utils/common.h"
#include "utils/constants.h"

extern const char *ganzhi_year[];
extern const char *ganzhi_day[];

typedef struct {
    int year;
    int month;
    int day;
    int is_leap;
    char zodiac[ZODIAC_SIZE];
    char ganzhi_year[GANZHI_SIZE];
    char ganzhi_month[GANZHI_SIZE];
    char ganzhi_day[GANZHI_SIZE];
} LunarDate;

int solar_to_lunar(const Date *solar, LunarDate *lunar);
int lunar_to_solar(LunarDate *lunar, Date *solar);
void lunar_get_zodiac(int year, char *zodiac);
void lunar_get_ganzhi_year(int year, char *ganzhi);
void lunar_get_ganzhi_day(const Date *solar, char *ganzhi);

#endif
