#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "calendar/lunar.h"
#include "utils/common.h"

void test_solar_to_lunar() {
    printf("Testing solar_to_lunar...\n");
    
    Date solar;
    LunarDate lunar;
    
    solar.year = 2024;
    solar.month = 1;
    solar.day = 1;
    
    int result = solar_to_lunar(&solar, &lunar);
    assert(result == 0);
    assert(lunar.year == 2023);
    assert(lunar.month == 11);
    assert(lunar.day == 26);
    assert(strcmp(lunar.zodiac, "兔") == 0);
    
    printf("  2024-01-01 -> Lunar 2023-11-26 (rabbit)\n");
    
    solar.year = 2024;
    solar.month = 2;
    solar.day = 10;
    
    result = solar_to_lunar(&solar, &lunar);
    assert(result == 0);
    assert(lunar.year == 2024);
    assert(lunar.month == 1);
    assert(lunar.day == 7);
    
    printf("  2024-02-10 -> Lunar 2024-1-07 (New Year period)\n");
    
    solar.year = 2025;
    solar.month = 1;
    solar.day = 29;
    
    result = solar_to_lunar(&solar, &lunar);
    assert(result == 0);
    assert(lunar.year == 2024);
    assert(lunar.month == 12);
    assert(lunar.day == 9);
    
    printf("  2025-01-29 -> Lunar 2024-12-09 (pre-New Year)\n");
}

void test_lunar_get_zodiac() {
    printf("Testing lunar_get_zodiac...\n");
    
    char zodiac[10];
    
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
    
    char ganzhi[10];
    
    lunar_get_ganzhi_year(2024, ganzhi);
    printf("  2024 -> %s\n", ganzhi);
    
    lunar_get_ganzhi_year(2025, ganzhi);
    printf("  2025 -> %s\n", ganzhi);
    
    lunar_get_ganzhi_year(1984, ganzhi);
    printf("  1984 -> %s\n", ganzhi);
}

void test_lunar_days_in_month() {
    printf("Testing lunar_days_in_month...\n");
    
    int days = lunar_days_in_month(2024, 11, 0);
    assert(days == 30 || days == 29);
    printf("  2024 month 11 has %d days\n", days);
    
    days = lunar_days_in_month(2024, 12, 0);
    assert(days == 30 || days == 29);
    printf("  2024 month 12 has %d days\n", days);
}

void test_lunar_get_leap_month() {
    printf("Testing lunar_get_leap_month...\n");
    
    int leap = lunar_get_leap_month(2024);
    printf("  2024 leap month: %d\n", leap);
    assert(leap == 0 || (leap >= 1 && leap <= 12));
    
    leap = lunar_get_leap_month(2025);
    printf("  2025 leap month: %d\n", leap);
    assert(leap == 0 || (leap >= 1 && leap <= 12));
}

void test_lunar_get_days_in_year() {
    printf("Testing lunar_get_days_in_year...\n");
    
    int days = lunar_get_days_in_year(2024);
    assert(days >= 354 && days <= 384);
    printf("  2024 has %d lunar days\n", days);
    
    days = lunar_get_days_in_year(2025);
    assert(days >= 354 && days <= 384);
    printf("  2025 has %d lunar days\n", days);
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
