#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "utils/common.h"

void test_date_to_weekday() {
    printf("Testing date_to_weekday...\n");
    
    Date date;
    
    date.year = 2024;
    date.month = 1;
    date.day = 1;
    int weekday = date_to_weekday(&date);
    printf("  2024-01-01 is weekday %d (Monday=1)\n", weekday);
    assert(weekday == 1);
    
    date.year = 2024;
    date.month = 2;
    date.day = 10;
    weekday = date_to_weekday(&date);
    printf("  2024-02-10 is weekday %d (Saturday=6)\n", weekday);
    assert(weekday == 6);
    
    date.year = 2024;
    date.month = 12;
    date.day = 25;
    weekday = date_to_weekday(&date);
    printf("  2024-12-25 is weekday %d (Wednesday=3)\n", weekday);
    assert(weekday == 3);
}

void test_date_days_in_month() {
    printf("Testing date_days_in_month...\n");
    
    Date date;
    
    date.year = 2024;
    date.month = 1;
    int days = date_days_in_month(&date);
    assert(days == 31);
    printf("  2024-01 has 31 days\n");
    
    date.year = 2024;
    date.month = 2;
    days = date_days_in_month(&date);
    assert(days == 29);
    printf("  2024-02 has 29 days (leap year)\n");
    
    date.year = 2023;
    date.month = 2;
    days = date_days_in_month(&date);
    assert(days == 28);
    printf("  2023-02 has 28 days\n");
    
    date.year = 2024;
    date.month = 4;
    days = date_days_in_month(&date);
    assert(days == 30);
    printf("  2024-04 has 30 days\n");
}

void test_date_add_days() {
    printf("Testing date_add_days...\n");
    
    Date date;
    
    date.year = 2024;
    date.month = 1;
    date.day = 1;
    
    date_add_days(&date, 1);
    assert(date.day == 2);
    assert(date.month == 1);
    printf("  2024-01-01 + 1 day = 2024-01-02\n");
    
    date.year = 2024;
    date.month = 1;
    date.day = 31;
    
    date_add_days(&date, 1);
    assert(date.day == 1);
    assert(date.month == 2);
    printf("  2024-01-31 + 1 day = 2024-02-01\n");
    
    date.year = 2024;
    date.month = 12;
    date.day = 31;
    
    date_add_days(&date, 1);
    assert(date.day == 1);
    assert(date.month == 1);
    assert(date.year == 2025);
    printf("  2024-12-31 + 1 day = 2025-01-01\n");
    
    date.year = 2024;
    date.month = 3;
    date.day = 1;
    
    date_add_days(&date, -1);
    assert(date.day == 29);
    assert(date.month == 2);
    printf("  2024-03-01 - 1 day = 2024-02-29\n");
}

void test_date_add_months() {
    printf("Testing date_add_months...\n");
    
    Date date;
    
    date.year = 2024;
    date.month = 1;
    date.day = 15;
    
    date_add_months(&date, 1);
    assert(date.month == 2);
    printf("  2024-01-15 + 1 month = 2024-02-15\n");
    
    date.year = 2024;
    date.month = 12;
    date.day = 15;
    
    date_add_months(&date, 1);
    assert(date.year == 2025);
    assert(date.month == 1);
    printf("  2024-12-15 + 1 month = 2025-01-15\n");
    
    date.year = 2024;
    date.month = 3;
    date.day = 31;
    
    date_add_months(&date, -1);
    assert(date.month == 2);
    assert(date.day == 29);
    printf("  2024-03-31 - 1 month = 2024-02-29\n");
}

void test_date_to_today() {
    printf("Testing date_to_today...\n");
    
    Date date;
    date_to_today(&date);
    
    assert(date.year >= 2024);
    assert(date.month >= 1 && date.month <= 12);
    assert(date.day >= 1 && date.day <= 31);
    
    printf("  Today is %04d-%02d-%02d\n", date.year, date.month, date.day);
}

void test_date_to_day_of_year() {
    printf("Testing date_to_day_of_year...\n");
    
    Date date;
    
    date.year = 2024;
    date.month = 1;
    date.day = 1;
    int doy = date_to_day_of_year(&date);
    assert(doy == 1);
    printf("  2024-01-01 is day %d of year\n", doy);
    
    date.year = 2024;
    date.month = 12;
    date.day = 31;
    doy = date_to_day_of_year(&date);
    assert(doy == 366);
    printf("  2024-12-31 is day %d of year (leap year)\n", doy);
    
    date.year = 2023;
    date.month = 12;
    date.day = 31;
    doy = date_to_day_of_year(&date);
    assert(doy == 365);
    printf("  2023-12-31 is day %d of year\n", doy);
}

void test_leap_year() {
    printf("Testing leap year detection...\n");
    
    Date date;
    
    date.year = 2024;
    date.month = 2;
    assert(date_days_in_month(&date) == 29);
    printf("  2024 is a leap year\n");
    
    date.year = 2023;
    date.month = 2;
    assert(date_days_in_month(&date) == 28);
    printf("  2023 is not a leap year\n");
    
    date.year = 2000;
    date.month = 2;
    assert(date_days_in_month(&date) == 29);
    printf("  2000 is a leap year\n");
    
    date.year = 1900;
    date.month = 2;
    assert(date_days_in_month(&date) == 28);
    printf("  1900 is not a leap year\n");
}

int main(void) {
    printf("=== DateTime Utility Tests ===\n\n");
    
    test_date_to_weekday();
    test_date_days_in_month();
    test_date_add_days();
    test_date_add_months();
    test_date_to_today();
    test_date_to_day_of_year();
    test_leap_year();
    
    printf("\n=== All datetime tests passed! ===\n");
    return 0;
}
