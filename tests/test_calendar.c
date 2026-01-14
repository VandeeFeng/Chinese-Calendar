#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "calendar/lunar.h"
#include "calendar/lunar_data.h"
#include "utils/common.h"
#include "utils/constants.h"

static unsigned int get_lunar_info(int year) {
    if (year < LUNAR_MIN_YEAR || year > LUNAR_MAX_YEAR) {
        return 0;
    }
    return lunar_data[year - LUNAR_MIN_YEAR];
}

static int helper_lunar_leap_month(int year) {
    return get_lunar_info(year) & LUNAR_INFO_LEAP_MONTH_MASK;
}

static int helper_lunar_leap_month_days(int year) {
    unsigned int info = get_lunar_info(year);
    if (helper_lunar_leap_month(year) == 0) {
        return 0;
    }
    return (info & LUNAR_INFO_LEAP_MONTH_DAY_BIT) ? LUNAR_DAYS_30 : LUNAR_DAYS_29;
}

static int helper_lunar_month_days(int year, int month) {
    unsigned int info = get_lunar_info(year);
    if ((info & (LUNAR_INFO_LEAP_MONTH_DAY_BIT >> month)) == 0) {
        return LUNAR_DAYS_29;
    }
    return LUNAR_DAYS_30;
}

static int helper_lunar_days_in_month(int year, int month, int leap) {
    if (year < LUNAR_MIN_YEAR || year > LUNAR_MAX_YEAR) return 0;
    if (month < 1 || month > LUNAR_MONTHS_PER_YEAR) return 0;

    const int leap_month = helper_lunar_leap_month(year);

    if (leap && month != leap_month) return 0;
    if (leap && month == leap_month) return helper_lunar_leap_month_days(year);

    return helper_lunar_month_days(year, month);
}

static int helper_lunar_get_leap_month(int year) {
    if (year < LUNAR_MIN_YEAR || year > LUNAR_MAX_YEAR) return 0;
    return helper_lunar_leap_month(year);
}

void test_solar_to_lunar() {
    printf("Testing solar_to_lunar...\n");

    Date solar;
    LunarDate lunar;
    int result;

    solar = (Date){2024, 1, 1};
    result = solar_to_lunar(&solar, &lunar);
    assert(result == 0);
    assert(lunar.year == 2023);
    assert(lunar.month == 11);
    assert(lunar.day == 20);
    assert(strcmp(lunar.zodiac, "兔") == 0);
    printf("  2024-01-01 -> Lunar 2023-11-20 (rabbit)\n");

    solar = (Date){2024, 2, 10};
    result = solar_to_lunar(&solar, &lunar);
    assert(result == 0);
    assert(lunar.year == 2024);
    assert(lunar.month == 1);
    assert(lunar.day == 1);
    printf("  2024-02-10 -> Lunar 2024-01-01 (New Year)\n");

    solar = (Date){2024, 6, 1};
    result = solar_to_lunar(&solar, &lunar);
    assert(result == 0);
    assert(lunar.year == 2024);
    assert(lunar.month == 4);
    assert(lunar.day == 25);
    printf("  2024-06-01 -> Lunar 2024-04-25 (dragon)\n");

    solar = (Date){2025, 1, 29};
    result = solar_to_lunar(&solar, &lunar);
    assert(result == 0);
    assert(lunar.year == 2025);
    assert(lunar.month == 1);
    assert(lunar.day == 1);
    assert(strcmp(lunar.zodiac, "蛇") == 0);
    printf("  2025-01-29 -> Lunar 2025-01-01 (New Year, snake)\n");
}

void test_lunar_get_zodiac() {
    printf("Testing lunar_get_zodiac...\n");

    char zodiac[ZODIAC_SIZE];

    lunar_get_zodiac(2024, zodiac);
    assert(strcmp(zodiac, "龙") == 0);
    printf("  2024 -> Dragon\n");

    lunar_get_zodiac(2025, zodiac);
    assert(strcmp(zodiac, "蛇") == 0);
    printf("  2025 -> Snake\n");

    lunar_get_zodiac(2000, zodiac);
    assert(strcmp(zodiac, "龙") == 0);
    printf("  2000 -> Dragon\n");

    lunar_get_zodiac(1990, zodiac);
    assert(strcmp(zodiac, "马") == 0);
    printf("  1990 -> Horse\n");
}

void test_lunar_get_ganzhi_year() {
    printf("Testing lunar_get_ganzhi_year...\n");

    char ganzhi[GANZHI_SIZE];

    lunar_get_ganzhi_year(2024, ganzhi);
    printf("  2024 -> %s\n", ganzhi);

    lunar_get_ganzhi_year(2025, ganzhi);
    printf("  2025 -> %s\n", ganzhi);

    lunar_get_ganzhi_year(1984, ganzhi);
    printf("  1984 -> %s\n", ganzhi);
}

void test_lunar_days_in_month() {
    printf("Testing lunar_days_in_month...\n");

    int days;

    days = helper_lunar_days_in_month(2024, 11, 0);
    assert(days == LUNAR_DAYS_30 || days == LUNAR_DAYS_29);
    printf("  2024 month 11 has %d days\n", days);

    days = helper_lunar_days_in_month(2024, 12, 0);
    assert(days == LUNAR_DAYS_30 || days == LUNAR_DAYS_29);
    printf("  2024 month 12 has %d days\n", days);
}

void test_lunar_get_leap_month() {
    printf("Testing lunar_get_leap_month...\n");

    int leap = helper_lunar_get_leap_month(2024);
    printf("  2024 leap month: %d\n", leap);
    assert(leap == 0 || (leap >= 1 && leap <= 12));

    leap = helper_lunar_get_leap_month(2025);
    printf("  2025 leap month: %d\n", leap);
    assert(leap == 0 || (leap >= 1 && leap <= 12));
}

void test_lunar_get_days_in_year() {
    printf("Testing lunar_get_days_in_year...\n");

    int total;
    int leap_month;

    total = 0;
    for (int i = 1; i <= LUNAR_MONTHS_PER_YEAR; i++) {
        total += helper_lunar_days_in_month(2024, i, 0);
    }
    leap_month = helper_lunar_get_leap_month(2024);
    if (leap_month > 0) {
        total += helper_lunar_days_in_month(2024, leap_month, 1);
    }
    assert(total >= 354 && total <= 384);
    printf("  2024 has %d lunar days\n", total);

    total = 0;
    for (int i = 1; i <= LUNAR_MONTHS_PER_YEAR; i++) {
        total += helper_lunar_days_in_month(2025, i, 0);
    }
    leap_month = helper_lunar_get_leap_month(2025);
    if (leap_month > 0) {
        total += helper_lunar_days_in_month(2025, leap_month, 1);
    }
    assert(total >= 354 && total <= 384);
    printf("  2025 has %d lunar days\n", total);
}

int main(void) {
    printf("=== Calendar Module Tests ===\n\n");

    test_solar_to_lunar();
    test_lunar_get_zodiac();
    test_lunar_get_ganzhi_year();
    test_lunar_days_in_month();
    test_lunar_get_leap_month();
    test_lunar_get_days_in_year();

    printf("\n=== All calendar tests passed! ===\n");
    return 0;
}
