#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "calendar/lunar.h"
#include "utils/common.h"
#include "utils/constants.h"

static void assert_solar_term(Date date, const char *expected_name) {
    LunarDate lunar;
    solar_to_lunar(&date, &lunar);
    printf("  %04d-%02d-%02d -> %s (%s expected)\n", date.year, date.month, date.day,
           lunar.solar_term_name, expected_name);
    assert(lunar.solar_term >= 0);
    assert(strcmp(lunar.solar_term_name, expected_name) == 0);
}

static void assert_no_solar_term(Date date) {
    LunarDate lunar;
    solar_to_lunar(&date, &lunar);
    printf("  %04d-%02d-%02d -> solar_term = %d (should be -1)\n",
           date.year, date.month, date.day, lunar.solar_term);
    assert(lunar.solar_term == -1);
}

static void assert_solar_term_index(Date date, int expected_index, const char *name) {
    LunarDate lunar;
    solar_to_lunar(&date, &lunar);
    printf("  %s: index=%d, name=%s\n", name, lunar.solar_term, lunar.solar_term_name);
    assert(lunar.solar_term == expected_index);
}

void test_solar_term_basic() {
    printf("Testing solar term calculation...\n");
    assert_solar_term((Date){2024, 12, 21}, "冬至");
    assert_solar_term((Date){2024, 6, 21}, "夏至");
    assert_solar_term((Date){2024, 3, 20}, "春分");
    assert_solar_term((Date){2024, 9, 22}, "秋分");
    assert_solar_term((Date){2024, 4, 4}, "清明");
}

void test_solar_term_negative() {
    printf("Testing dates that are not solar terms...\n");
    assert_no_solar_term((Date){2024, 12, 25});
    assert_no_solar_term((Date){2024, 6, 25});
    assert_no_solar_term((Date){2024, 1, 15});
}

void test_solar_term_index() {
    printf("Testing solar term indices...\n");
    assert_solar_term_index((Date){2024, 12, 21}, 0, "冬至");
    assert_solar_term_index((Date){2024, 6, 21}, 12, "夏至");
    assert_solar_term_index((Date){2024, 3, 20}, 6, "春分");
    assert_solar_term_index((Date){2024, 9, 22}, 18, "秋分");
}

int main(void) {
    printf("=== Solar Terms Tests ===\n\n");
    test_solar_term_basic();
    test_solar_term_negative();
    test_solar_term_index();
    printf("\n=== All solar terms tests passed! ===\n");
    return 0;
}
