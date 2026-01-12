#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "almanac/almanac.h"
#include "calendar/lunar.h"
#include "utils/common.h"

void test_almanac_init() {
    printf("Testing almanac_init...\n");
    
    Almanac alm;
    almanac_init(&alm);
    
    assert(alm.yi[0] == '\0');
    assert(alm.ji[0] == '\0');
    assert(alm.chong[0] == '\0');
    
    printf("  Almanac initialized correctly\n");
}

void test_almanac_calculate() {
    printf("Testing almanac_calculate...\n");
    
    Date solar;
    LunarDate lunar;
    Almanac alm;
    
    solar.year = 2024;
    solar.month = 1;
    solar.day = 1;
    
    solar_to_lunar(&solar, &lunar);
    almanac_init(&alm);
    
    int result = almanac_calculate(&solar, &lunar, &alm);
    assert(result == 0);
    
    assert(strlen(alm.yi) > 0);
    assert(strlen(alm.ji) > 0);
    assert(strlen(alm.chong) > 0);
    assert(strlen(alm.chaishen) > 0);
    assert(strlen(alm.xishen) > 0);
    assert(strlen(alm.fushen) > 0);
    assert(strlen(alm.pengzu) > 0);
    
    printf("  Almanac calculated for 2024-01-01:\n");
    printf("    Yi: %s\n", alm.yi);
    printf("    Ji: %s\n", alm.ji);
    printf("    Chong: %s\n", alm.chong);
    printf("    Chaishen: %s\n", alm.chaishen);
}

void test_almanac_consistency() {
    printf("Testing almanac consistency across days...\n");
    
    Date solar;
    LunarDate lunar;
    Almanac alm1, alm2;
    
    solar.year = 2024;
    solar.month = 1;
    solar.day = 1;
    
    solar_to_lunar(&solar, &lunar);
    almanac_init(&alm1);
    almanac_calculate(&solar, &lunar, &alm1);
    
    solar.year = 2024;
    solar.month = 1;
    solar.day = 2;
    
    solar_to_lunar(&solar, &lunar);
    almanac_init(&alm2);
    almanac_calculate(&solar, &lunar, &alm2);
    
    printf("  Day 1:\n");
    printf("    Chong: %s\n", alm1.chong);
    printf("    Pengzu: %s\n", alm1.pengzu);
    
    printf("  Day 2:\n");
    printf("    Chong: %s\n", alm2.chong);
    printf("    Pengzu: %s\n", alm2.pengzu);
}

void test_almanac_yi_ji() {
    printf("Testing yi and ji items...\n");
    
    Date solar;
    LunarDate lunar;
    Almanac alm;
    
    solar.year = 2024;
    solar.month = 2;
    solar.day = 10;
    
    solar_to_lunar(&solar, &lunar);
    almanac_init(&alm);
    almanac_calculate(&solar, &lunar, &alm);
    
    printf("  New Year 2024 almanac:\n");
    printf("    Yi: %s\n", alm.yi);
    printf("    Ji: %s\n", alm.ji);
    
    assert(strlen(alm.yi) > 0);
    assert(strlen(alm.ji) > 0);
}

int main(void) {
    printf("=== Almanac Module Tests ===\n\n");
    
    test_almanac_init();
    test_almanac_calculate();
    test_almanac_consistency();
    test_almanac_yi_ji();
    
    printf("\n=== All almanac tests passed! ===\n");
    return 0;
}
