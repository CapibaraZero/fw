#ifndef SUBGHZ_ACTIONS_H
#define SUBGHZ_ACTIONS_H

#include "lvgl.h"

#ifdef __cplusplus
extern "C" {
#endif

void action_go_to_subghz(lv_event_t *e);
void action_subghz_start_frequency_analyzer(lv_event_t *e);
void action_stop_subghz_frequency_analyzer(lv_event_t *e);

void action_subghz_start_record_raw(lv_event_t *e);

void action_subghz_start_sender(lv_event_t *e);
#ifdef __cplusplus
}
#endif

#endif