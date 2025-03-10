#include "lvgl.h"

void create_btn(const char *label, lv_obj_t *parent_obj, lv_event_cb_t callback, void *user_data) {
    lv_obj_t *obj = lv_btn_create(parent_obj);
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 34);
    lv_obj_add_event_cb(obj, callback, LV_EVENT_PRESSED, user_data);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, label);
            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
}