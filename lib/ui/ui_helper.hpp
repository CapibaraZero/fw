#ifndef UI_HELPER_H
#define UI_HELPER_H

#include "lvgl.h"

void create_btn(const char *label, lv_obj_t *parent_obj, lv_event_cb_t callback, void *user_data, int w = 320, int h = 34);

#endif