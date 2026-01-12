#define _POSIX_C_SOURCE 199309L
#include <ncurses.h>
#include <string.h>
#include <time.h>
#include "ui/visual/deity_art.h"
#include "calendar/lunar.h"

static const char* deity_names[] = {
    "财神",
    "灶神",
    "门神",
    "月老",
    "土地公"
};

static const char* caishen_art_0[] = {
    "      ╭-──────-───╮",
    "     ╱            ╲",
    "    │   ◉   ◉    │",
    "    │     ──     │",
    "    │   ┌────┐   │",
    "   ╱│   │    │   │╲",
    "  │ │   └────┘   │ │",
    "  │ │  ╭──────╮  │ │",
    "  │ │  │  ◢◣  │  │ │",
    "  │ │  │  ◥◤  │  │ │",
    "  │ │  ╰──────╯  │ │",
    "  │ │            │ │",
    "   ╲│  财神驾到  │╱",
    "    │            │",
    "     ╲          ╱",
    "      ╰──────────╯"
};

static const char* caishen_art_1[] = {
    "      ╭-──────-───╮",
    "     ╱            ╲",
    "    │   ◉   ◉    │",
    "    │     ──     │",
    "    │   ┌────┐   │",
    "   ╱│   │    │   │╲",
    "  │ │   └────┘   │ │",
    "  │ │  ╭──────╮  │ │",
    "  │ │  │      │  │ │",
    "  │ │  │  ◢◣  │  │ │",
    "  │ │  │  ◥◤  │  │ │",
    "  │ │  ╰──────╯  │ │",
    "   ╲│  财神驾到  │╱",
    "    │            │",
    "     ╲          ╱",
    "      ╰──────────╯"
};

static const char* caishen_art_2[] = {
    "      ╭-──────-───╮",
    "     ╱            ╲",
    "    │   ◉   ◉    │",
    "    │     ──     │",
    "    │   ┌────┐   │",
    "   ╱│   │    │   │╲",
    "  │ │   └────┘   │ │",
    "  │ │  ╭──────╮  │ │",
    "  │ │  │      │  │ │",
    "  │ │  │      │  │ │",
    "  │ │  │  ◢◣  │  │ │",
    "  │ │  │  ◥◤  │  │ │",
    "  │ │  ╰──────╯  │ │",
    "   ╲│  财神驾到  │╱",
    "    │            │",
    "     ╲          ╱",
    "      ╰──────────╯"
};

static const char* zaoshen_art_0[] = {
    "      ╭-──────-───╮",
    "     ╱            ╲",
    "    │   ○   ○    │",
    "    │     ━━     │",
    "    │   ┌────┐   │",
    "   ╱│   │锅盖│   │╲",
    "  │ │   └────┘   │ │",
    "  │ │  ╭──────╮  │ │",
    "  │ │  │ ┌──┐ │  │ │",
    "  │ │  │ └│┘ │  │ │",
    "  │ │  ╰──────╯  │ │",
    "  │ │            │ │",
    "   ╲│  灶神保佑  │╱",
    "    │            │",
    "     ╲          ╱",
    "      ╰──────────╯"
};

static const char* zaoshen_art_1[] = {
    "      ╭-──────-───╮",
    "     ╱            ╲",
    "    │   ○   ○    │",
    "    │     ━━     │",
    "    │   ┌────┐   │",
    "   ╱│   │锅盖│   │╲",
    "  │ │   └────┘   │ │",
    "  │ │  ╭──────╮  │ │",
    "  │ │  │  ╱  │  │ │",
    "  │ │  │ └──┘ │  │ │",
    "  │ │  ╰──────╯  │ │",
    "  │ │            │ │",
    "   ╲│  灶神保佑  │╱",
    "    │            │",
    "     ╲          ╱",
    "      ╰──────────╯"
};

static const char* zaoshen_art_2[] = {
    "      ╭-──────-───╮",
    "     ╱            ╲",
    "    │   ○   ○    │",
    "    │     ━━     │",
    "    │   ┌────┐   │",
    "   ╱│   │锅盖│   │╲",
    "  │ │   └────┘   │ │",
    "  │ │  ╭──────╮  │ │",
    "  │ │  │ ┌──┐ │  │ │",
    "  │ │  │ │┘└ │  │ │",
    "  │ │  ╰──────╯  │ │",
    "  │ │            │ │",
    "   ╲│  灶神保佑  │╱",
    "    │            │",
    "     ╲          ╱",
    "      ╰──────────╯"
};

static const char* zaoshen_art_3[] = {
    "      ╭-──────-───╮",
    "     ╱            ╲",
    "    │   ○   ○    │",
    "    │     ━━     │",
    "    │   ┌────┐   │",
    "   ╱│   │锅盖│   │╲",
    "  │ │   └────┘   │ │",
    "  │ │  ╭──────╮  │ │",
    "  │ │  │ ┌──┐ │  │ │",
    "  │ │  │ ╲──┘ │  │ │",
    "  │ │  ╰──────╯  │ │",
    "  │ │            │ │",
    "   ╲│  灶神保佑  │╱",
    "    │            │",
    "     ╲          ╱",
    "      ╰──────────╯"
};

static const char* menshen_art_0[] = {
    "      ╭-──────-───╮",
    "     ╱            ╲",
    "    │   ●   ●    │",
    "    │     ━━     │",
    "    │   ┌────┐   │",
    "   ╱│   │盔甲│   │╲",
    "  │ │   └────┘   │ │",
    "  │ │  ╭──────╮  │ │",
    "  │ │  │  ⚔   │  │ │",
    "  │ │  │  │   │  │ │",
    "  │ │  ╰──────╯  │ │",
    "  │ │            │ │",
    "   ╲│  门神守护  │╱",
    "    │            │",
    "     ╲          ╱",
    "      ╰──────────╯"
};

static const char* menshen_art_1[] = {
    "      ╭-──────-───╮",
    "     ╱            ╲",
    "    │   ●   ●    │",
    "    │     ━━     │",
    "    │   ┌────┐   │",
    "   ╱│   │盔甲│   │╲",
    "  │ │   └────┘   │ │",
    "  │ │  ╭──────╮  │ │",
    "  │ │  │ ╱⚔   │  │ │",
    "  │ │  │╱     │  │ │",
    "  │ │  ╰──────╯  │ │",
    "  │ │            │ │",
    "   ╲│  门神守护  │╱",
    "    │            │",
    "     ╲          ╱",
    "      ╰──────────╯"
};

static const char* menshen_art_2[] = {
    "      ╭-──────-───╮",
    "     ╱            ╲",
    "    │   ●   ●    │",
    "    │     ━━     │",
    "    │   ┌────┐   │",
    "   ╱│   │盔甲│   │╲",
    "  │ │   └────┘   │ │",
    "  │ │  ╭──────╮  │ │",
    "  │ │  │ ⚔╲   │  │ │",
    "  │ │  │     ╲│  │ │",
    "  │ │  ╰──────╯  │ │",
    "  │ │            │ │",
    "   ╲│  门神守护  │╱",
    "    │            │",
    "     ╲          ╱",
    "      ╰──────────╯"
};

static const char* yuelao_art_0[] = {
    "      ╭-──────-───╮",
    "     ╱            ╲",
    "    │   ◉   ◉    │",
    "    │     ~~      │",
    "    │   ┌────┐   │",
    "   ╱│   │长袍│   │╲",
    "  │ │   └────┘   │ │",
    "  │ │  ╭──────╮  │ │",
    "  │ │  │ ──── │  │ │",
    "  │ │  │ ~~~~ │  │ │",
    "  │ │  ╰──────╯  │ │",
    "  │ │            │ │",
    "   ╲│  月老牵线  │╱",
    "    │            │",
    "     ╲          ╱",
    "      ╰──────────╯"
};

static const char* yuelao_art_1[] = {
    "      ╭-──────-───╮",
    "     ╱            ╲",
    "    │   ◉   ◉    │",
    "    │     ~~      │",
    "    │   ┌────┐   │",
    "   ╱│   │长袍│   │╲",
    "  │ │   └────┘   │ │",
    "  │ │  ╭──────╮  │ │",
    "  │ │  │ ~~~~~ │  │ │",
    "  │ │  │ ─~~~ │  │ │",
    "  │ │  ╰──────╯  │ │",
    "  │ │            │ │",
    "   ╲│  月老牵线  │╱",
    "    │            │",
    "     ╲          ╱",
    "      ╰──────────╯"
};

static const char* yuelao_art_2[] = {
    "      ╭-──────-───╮",
    "     ╱            ╲",
    "    │   ◉   ◉    │",
    "    │     ~~      │",
    "    │   ┌────┐   │",
    "   ╱│   │长袍│   │╲",
    "  │ │   └────┘   │ │",
    "  │ │  ╭──────╮  │ │",
    "  │ │  │ ──── │  │ │",
    "  │ │  │ ~~~~ │  │ │",
    "  │ │  ╰──────╯  │ │",
    "  │ │            │ │",
    "   ╲│  月老牵线  │╱",
    "    │            │",
    "     ╲          ╱",
    "      ╰──────────╯"
};

static const char* yuelao_art_3[] = {
    "      ╭-──────-───╮",
    "     ╱            ╲",
    "    │   ◉   ◉    │",
    "    │     ~~      │",
    "    │   ┌────┐   │",
    "   ╱│   │长袍│   │╲",
    "  │ │   └────┘   │ │",
    "  │ │  ╭──────╮  │ │",
    "  │ │  │ ~~~~~ │  │ │",
    "  │ │  │ ~~~─ │  │ │",
    "  │ │  ╰──────╯  │ │",
    "  │ │            │ │",
    "   ╲│  月老牵线  │╱",
    "    │            │",
    "     ╲          ╱",
    "      ╰──────────╯"
};

static const char* tudigong_art_0[] = {
    "      ╭-──────-───╮",
    "     ╱            ╲",
    "    │   ○   ○    │",
    "    │     ━━     │",
    "    │   ┌────┐   │",
    "   ╱│   │素衣│   │╲",
    "  │ │   └────┘   │ │",
    "  │ │  ╭──────╮  │ │",
    "  │ │  │ ╭──┐ │  │ │",
    "  │ │  │ ╰──┘ │  │ │",
    "  │ │  │  │   │  │ │",
    "  │ │  ╰──────╯  │ │",
    "   ╲│ 土地公公  │╱",
    "    │            │",
    "     ╲          ╱",
    "      ╰──────────╯"
};

static const char* tudigong_art_1[] = {
    "      ╭-──────-───╮",
    "     ╱            ╲",
    "    │   ○   ○    │",
    "    │     ━━     │",
    "    │   ┌────┐   │",
    "   ╱│   │素衣│   │╲",
    "  │ │   └────┘   │ │",
    "  │ │  ╭──────╮  │ │",
    "  │ │  │ ╭──┐ │  │ │",
    "  │ │  │ ╰──┘ │  │ │",
    "  │ │  │   │  │  │ │",
    "  │ │  ╰──────╯  │ │",
    "   ╲│ 土地公公  │╱",
    "    │            │",
    "     ╲          ╱",
    "      ╰──────────╯"
};

typedef struct {
    const char** frames[4];
    int frame_count;
} DeityFrames;

static const DeityFrames deity_frames[] = {
    { {caishen_art_0, caishen_art_1, caishen_art_2}, 3 },
    { {zaoshen_art_0, zaoshen_art_1, zaoshen_art_2, zaoshen_art_3}, 4 },
    { {menshen_art_0, menshen_art_1, menshen_art_2}, 3 },
    { {yuelao_art_0, yuelao_art_1, yuelao_art_2, yuelao_art_3}, 4 },
    { {tudigong_art_0, tudigong_art_1}, 2 }
};

void deity_animation_init(AnimationState *anim_state, int total_frames, int frame_delay_ms) {
    if (anim_state == NULL) {
        return;
    }
    anim_state->current_frame = 0;
    anim_state->total_frames = total_frames;
    anim_state->frame_delay_ms = frame_delay_ms;
    anim_state->last_update_ms = 0;
}

static unsigned long get_current_time_ms(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
}

void deity_draw(WINDOW *win, int y, int x, DeityType type, AnimationState *anim_state) {
    if (type < 0 || type >= DEITY_COUNT) {
        return;
    }

    const DeityFrames *frames = &deity_frames[type];

    if (anim_state != NULL && anim_state->frame_delay_ms > 0) {
        unsigned long now = get_current_time_ms();
        if (now - anim_state->last_update_ms >= (unsigned long)anim_state->frame_delay_ms) {
            anim_state->current_frame = (anim_state->current_frame + 1) % frames->frame_count;
            anim_state->last_update_ms = now;
        }
    }

    const char** art = frames->frames[anim_state ? anim_state->current_frame : 0];
    const int lines = 16;

    for (int i = 0; i < lines; i++) {
        if (art[i] != NULL) {
            mvwprintw(win, y + i, x, "%s", art[i]);
        }
    }
}

const char* deity_get_name(DeityType type) {
    if (type < 0 || type >= DEITY_COUNT) {
        return "未知";
    }
    return deity_names[type];
}

DeityType get_daily_deity(const Date *date) {
    if (date == NULL) {
        return DEITY_CAISHEN;
    }
    const int seed = (date->year + date->month + date->day) % DEITY_COUNT;
    return (DeityType)seed;
}
