#include "almanac/almanac.h"
#include "calendar/lunar.h"
#include <string.h>
#include "utils/constants.h"

static const char *yi_items[] = {
    "祭祀", "祈福", "求嗣", "开光", "塑绘", "斋醮", "出行", "订婚",
    "安床", "安葬", "交易", "开市", "纳财", "修造", "动土", "破土",
    "入宅", "嫁娶", "纳采", "裁衣", "立券", "起基", "入殓", "移柩",
    "安香", "进人口", "安香", "作灶", "安床", "冠笄", "沐浴", "剃头"
};

static const char *ji_items[] = {
    "嫁娶", "开市", "动土", "安葬", "修造", "入宅", "作灶", "移徙",
    "伐木", "作梁", "置产", "安床", "安香", "入殓", "移柩", "破土",
    "出行", "交易", "纳财", "开光", "斋醮", "祈福", "求嗣", "订婚"
};

static const char *shensha_ji[] = {
    "月建", "小时", "土府", "厌对", "招摇", "月破", "大耗", "小耗",
    "五虚", "地火", "月害", "月刑", "大煞", "往亡", "勾陈"
};

static const char *shensha_jishen[] = {
    "月恩", "天恩", "四相", "官日", "天恩", "福生", "五合", "鸣犬对",
    "三合", "临日", "时阴", "天仓", "圣心", "青龙", "明堂", "金匮",
    "天德", "月德", "天德合", "月德合"
};

static void append_item(char *buffer, size_t buffer_size, const char *item, const char *separator) {
    size_t current_len = strlen(buffer);
    size_t available = buffer_size - current_len - 1;

    if (available == 0) {
        return;
    }

    if (current_len > 0) {
        size_t sep_len = strlen(separator);
        if (sep_len > 0 && sep_len <= available) {
            strncat(buffer, separator, available);
            current_len = strlen(buffer);
            available = buffer_size - current_len - 1;
        }
    }

    size_t item_len = strlen(item);
    if (item_len > 0 && item_len <= available) {
        strncat(buffer, item, available);
    }
}

void almanac_init(Almanac *alm) {
    memset(alm, 0, sizeof(Almanac));
}

int almanac_calculate(const Date *solar, const LunarDate *lunar __attribute__((unused)), Almanac *alm) {
    const int day_of_year = solar->year * 10000 + solar->month * 100 + solar->day;
    const int seed = day_of_year % 100;

    const int yi_count = 4 + (seed % 4);
    const int ji_count = 2 + (seed % 3);

    alm->yi[0] = '\0';
    alm->ji[0] = '\0';

    for (int i = 0; i < yi_count; i++) {
        int idx = (seed + i * 7) % (sizeof(yi_items) / sizeof(yi_items[0]));
        append_item(alm->yi, sizeof(alm->yi), yi_items[idx], " ");
    }

    for (int i = 0; i < ji_count; i++) {
        int idx = (seed + i * 11) % (sizeof(ji_items) / sizeof(ji_items[0]));
        append_item(alm->ji, sizeof(alm->ji), ji_items[idx], " ");
    }

    static const char *chong_animal[] = {"鼠", "牛", "虎", "兔", "龙", "蛇", "马", "羊", "猴", "鸡", "狗", "猪"};
    const int chong_idx = (solar->year + solar->month + solar->day) % ZODIAC_ARRAY_SIZE;
    snprintf(alm->chong, sizeof(alm->chong), "冲%s%s", chong_animal[chong_idx], (chong_idx % 2) ? "煞南" : "煞北");

    static const char *directions[] = {"东北", "东南", "西南", "西北", "正北", "正南", "正东", "正西"};
    const int chaishen_idx = seed % DIRECTIONS_COUNT;
    const int xishen_idx = (seed + 2) % DIRECTIONS_COUNT;
    const int fushen_idx = (seed + 4) % DIRECTIONS_COUNT;

    snprintf(alm->chaishen, sizeof(alm->chaishen), "%s", directions[chaishen_idx]);
    snprintf(alm->xishen, sizeof(alm->xishen), "%s", directions[xishen_idx]);
    snprintf(alm->fushen, sizeof(alm->fushen), "%s", directions[fushen_idx]);

    const int jishen_count = 2 + (seed % 3);
    alm->jishen[0] = '\0';
    for (int i = 0; i < jishen_count; i++) {
        int idx = (seed + i * 13) % (sizeof(shensha_jishen) / sizeof(shensha_jishen[0]));
        append_item(alm->jishen, sizeof(alm->jishen), shensha_jishen[idx], ",");
    }

    const int xiongsha_count = 1 + (seed % 2);
    alm->xiongsha[0] = '\0';
    for (int i = 0; i < xiongsha_count; i++) {
        int idx = (seed + i * 17) % (sizeof(shensha_ji) / sizeof(shensha_ji[0]));
        append_item(alm->xiongsha, sizeof(alm->xiongsha), shensha_ji[idx], ",");
    }

    static const char *tiangan_taboos[] = {
        "开仓", "栽植", "修灶", "剃头", "受田", "破券",
        "经络", "合酱", "决水", "词讼"
    };

    static const char *dizhi_taboos[] = {
        "问卜", "冠带", "祭祀", "穿井", "哭泣", "远行",
        "苫盖", "服药", "安床", "宴客", "吃犬", "嫁娶"
    };

    const int ganzhi_idx = seed % GANZHI_ARRAY_SIZE;
    const int tiangan_idx = ganzhi_idx % 10;
    const int dizhi_idx = ganzhi_idx % 12;

    const char *tiangan = ganzhi_day[ganzhi_idx];
    const char *dizhi = lunar->zodiac;

    snprintf(alm->pengzu, sizeof(alm->pengzu), "%s不%s %s不%s",
             tiangan, tiangan_taboos[tiangan_idx],
             dizhi, dizhi_taboos[dizhi_idx]);

    return 0;
}