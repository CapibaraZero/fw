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
 
#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *wi_fi_page;
    lv_obj_t *wi_fi_scan_page;
    lv_obj_t *wi_fi_net_view;
    lv_obj_t *wi_fi_net_selection;
    lv_obj_t *sniffer;
    lv_obj_t *evil_portal;
    lv_obj_t *dhcp_glutton;
    lv_obj_t *invalid_config;
    lv_obj_t *ble_page;
    lv_obj_t *ble_spam;
    lv_obj_t *file_explorer;
    lv_obj_t *sub_ghz_page;
    lv_obj_t *sub_ghz_frequency_analyzer_page;
    lv_obj_t *wifi_stack_init_text;
    lv_obj_t *obj0;
    lv_obj_t *obj1;
    lv_obj_t *obj2;
    lv_obj_t *obj3;
    lv_obj_t *obj4;
    lv_obj_t *obj5;
    lv_obj_t *obj6;
    lv_obj_t *obj7;
    lv_obj_t *obj8;
    lv_obj_t *obj9;
    lv_obj_t *obj10;
    lv_obj_t *obj11;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_MAIN = 1,
    SCREEN_ID_WI_FI_PAGE = 2,
    SCREEN_ID_WI_FI_SCAN_PAGE = 3,
    SCREEN_ID_WI_FI_NET_VIEW = 4,
    SCREEN_ID_WI_FI_NET_SELECTION = 5,
    SCREEN_ID_SNIFFER = 6,
    SCREEN_ID_EVIL_PORTAL = 7,
    SCREEN_ID_DHCP_GLUTTON = 8,
    SCREEN_ID_INVALID_CONFIG = 9,
    SCREEN_ID_BLE_PAGE = 10,
    SCREEN_ID_BLE_SPAM = 11,
    SCREEN_ID_FILE_EXPLORER = 12,
    SCREEN_ID_SUB_GHZ_PAGE = 13,
    SCREEN_ID_SUB_GHZ_FREQUENCY_ANALYZER_PAGE = 14,
};

void create_screen_main();
void delete_screen_main();
void tick_screen_main();

void create_screen_wi_fi_page();
void delete_screen_wi_fi_page();
void tick_screen_wi_fi_page();

void create_screen_wi_fi_scan_page();
void delete_screen_wi_fi_scan_page();
void tick_screen_wi_fi_scan_page();

void create_screen_wi_fi_net_view();
void delete_screen_wi_fi_net_view();
void tick_screen_wi_fi_net_view();

void create_screen_wi_fi_net_selection();
void delete_screen_wi_fi_net_selection();
void tick_screen_wi_fi_net_selection();

void create_screen_sniffer();
void delete_screen_sniffer();
void tick_screen_sniffer();

void create_screen_evil_portal();
void delete_screen_evil_portal();
void tick_screen_evil_portal();

void create_screen_dhcp_glutton();
void delete_screen_dhcp_glutton();
void tick_screen_dhcp_glutton();

void create_screen_invalid_config();
void delete_screen_invalid_config();
void tick_screen_invalid_config();

void create_screen_ble_page();
void delete_screen_ble_page();
void tick_screen_ble_page();

void create_screen_ble_spam();
void delete_screen_ble_spam();
void tick_screen_ble_spam();

void create_screen_file_explorer();
void delete_screen_file_explorer();
void tick_screen_file_explorer();

void create_screen_sub_ghz_page();
void delete_screen_sub_ghz_page();
void tick_screen_sub_ghz_page();

void create_screen_sub_ghz_frequency_analyzer_page();
void delete_screen_sub_ghz_frequency_analyzer_page();
void tick_screen_sub_ghz_frequency_analyzer_page();

void create_screen_by_id(enum ScreensEnum screenId);
void delete_screen_by_id(enum ScreensEnum screenId);
void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/