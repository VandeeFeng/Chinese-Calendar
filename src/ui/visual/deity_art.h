#ifndef DEITY_ART_H
#define DEITY_ART_H

#include "utils/common.h"

typedef enum {
    DEITY_CAISHEN,
    DEITY_ZAOSHEN,
    DEITY_MENSHEN,
    DEITY_YUELAO,
    DEITY_TU_DIGONG,
    DEITY_COUNT
} DeityType;

typedef struct {
    int current_frame;
    int total_frames;
    int frame_delay_ms;
    unsigned long last_update_ms;
} AnimationState;

void deity_draw(WINDOW *win, int y, int x, DeityType type, AnimationState *anim_state);
const char* deity_get_name(DeityType type);
DeityType get_daily_deity(const Date *date);
void deity_animation_init(AnimationState *anim_state, int total_frames, int frame_delay_ms);

#endif
