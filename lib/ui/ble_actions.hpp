#ifndef BLE_ACTIONS_H
#define BLE_ACTIONS_H

#include "lvgl.h"

void stop_ble_sniffer();

#ifdef __cplusplus
extern "C" {
#endif

void action_go_to_ble_page(lv_event_t *e);
void action_start_ble_sniffer(lv_event_t *e);
void action_start_ble_spam(lv_event_t *e);
void action_stop_ble_spam(lv_event_t *e);

#ifdef __cplusplus
}
#endif

#endif