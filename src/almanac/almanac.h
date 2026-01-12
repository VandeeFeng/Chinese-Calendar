#ifndef ALMANAC_H
#define ALMANAC_H

#include "utils/common.h"
#include "utils/constants.h"
#include "calendar/lunar.h"

typedef struct {
    char yi[ALMANAC_BUFFER_SIZE];
    char ji[ALMANAC_BUFFER_SIZE];
    char chong[ALMANAC_SHORT_SIZE];
    char chaishen[ALMANAC_SHORT_SIZE];
    char xishen[ALMANAC_SHORT_SIZE];
    char fushen[ALMANAC_SHORT_SIZE];
    char jishen[ALMANAC_SHORT_SIZE * 8];
    char xiongsha[ALMANAC_SHORT_SIZE * 8];
    char pengzu[ALMANAC_SHORT_SIZE * 4];
    char jiushen[ALMANAC_SHORT_SIZE * 8];
    char weizhi[ALMANAC_SHORT_SIZE];
    char xishen_zhi[ALMANAC_SHORT_SIZE];
    char taisui[ALMANAC_SHORT_SIZE];
} Almanac;

void almanac_init(Almanac *alm);
int almanac_calculate(const Date *solar, const LunarDate *lunar, Almanac *alm);

#endif
