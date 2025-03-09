/*
 * This file is part of the Capibara zero (https://github.com/CapibaraZero/fw or
 * https://capibarazero.github.io/). Copyright (c) 2025 Andrea Canale.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef EEZ_LVGL_UI_EVENTS_H
#define EEZ_LVGL_UI_EVENTS_H

#include <lvgl.h>

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

#endif /*EEZ_LVGL_UI_EVENTS_H*/