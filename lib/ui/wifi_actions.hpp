#ifndef WIFI_ACTIONS_H
#define WIFI_ACTIONS_H

#include "lvgl.h"

void wifi_stop_sniffer();

#ifdef __cplusplus
extern "C" {
#endif

void action_go_to_main_page(lv_event_t *e);

void action_go_to_wifi_page(lv_event_t * e);
void action_go_to_wifi_scan(lv_event_t * e);
void action_next_wifi_network(lv_event_t *e);
void action_save_wifi_scan_to_sd(lv_event_t *e);
void action_wifi_stop_sniffer(lv_event_t *e);
void action_wifi_start_bssid_sniffer(lv_event_t *e);
void action_go_to_net_selection(lv_event_t *e);
void action_go_to_wifi_sniffer(lv_event_t *e);

void action_go_to_evilportal(lv_event_t *e);

void action_wifi_stop_evilportal(lv_event_t *e);

void action_go_to_dhcpglutton(lv_event_t *e);

void action_dhcpglutton_stop(lv_event_t *e);
#ifdef __cplusplus
}
#endif

#endif