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

#include <lvgl.h>

#include "screens.h"
#include "ui.h"
#include "wifi_attacks_btn.hpp"
#include "actions/tasks/wifi/wifi_ui_tasks.hpp"
#include "network_attacks.hpp"
#include "network_attacks_btn.hpp"
#include "evilportal.hpp"
#include "vars.h"
#include "Arduino.h"
#include "posixsd.hpp"

bool wifi_sniffer_running = false;
extern bool ble_sniffer_running;

extern "C" void action_go_to_main_page(lv_event_t *e)
{
    create_screen_main();
    loadScreen(SCREEN_ID_MAIN);
}

extern "C" void action_go_to_wifi_page(lv_event_t *e)
{
    create_screen_wi_fi_page();
    loadScreen(SCREEN_ID_WI_FI_PAGE);
}

static WifiAttack attack;
static NetworkAttacks net_attacks;

extern "C" void action_go_to_wifi_scan(lv_event_t *e)
{
    create_screen_wi_fi_scan_page();
    loadScreen(SCREEN_ID_WI_FI_SCAN_PAGE);
    scan_wifi(&attack);
}

static size_t position = 0;

extern "C" void action_next_wifi_network(lv_event_t *e)
{
    Serial.println("Scroll");
    next_network(&position);
}

extern "C" void action_go_to_net_selection(lv_event_t *e)
{
    create_screen_wi_fi_net_selection();
    loadScreen(SCREEN_ID_WI_FI_NET_SELECTION);
}

extern "C" void action_save_wifi_scan_to_sd(lv_event_t *e)
{
    attack.save_scan();      // TODO: Create a task for this to create better UX
    attack.clean_networks(); // Clean previous scan
    create_screen_wi_fi_page();
    loadScreen(SCREEN_ID_WI_FI_PAGE);
}

extern "C" void action_wifi_start_bssid_sniffer(lv_event_t *e)
{
    wifi_sniffer_running = true;
    create_screen_sniffer();
    loadScreen(SCREEN_ID_SNIFFER);
    WifiNetwork *net = get_current_network(position);
    sniff_bssid(&attack, net);
}

extern "C" void action_go_to_wifi_sniffer(lv_event_t *e)
{
    wifi_sniffer_running = true;
    create_screen_sniffer();
    loadScreen(SCREEN_ID_SNIFFER);
    sniff_wifi(&attack);
}

void show_invalid_config()
{
    create_screen_invalid_config();
    loadScreen(SCREEN_ID_INVALID_CONFIG);
}

extern "C" void action_go_to_evilportal(lv_event_t *e)
{
    start_evilportal(&net_attacks);
    create_screen_evil_portal();
    loadScreen(SCREEN_ID_EVIL_PORTAL);
}

extern "C" void action_wifi_stop_evilportal(lv_event_t *e)
{
    kill_evilportal(&net_attacks);
    action_go_to_wifi_page(e);
}

extern "C" void action_go_to_dhcpglutton(lv_event_t *e)
{
    if (!exists("/dhcp_glutton/config.json"))
    {
        show_invalid_config();
    }
    else
    {
        start_dhcpglutton(&net_attacks);
        // delay(2000);
        create_screen_dhcp_glutton();
        loadScreen(SCREEN_ID_DHCP_GLUTTON);
        // delay(2000);
    }
}

extern "C" void action_dhcpglutton_stop(lv_event_t *e)
{
    kill_dhcpglutton();
    action_go_to_wifi_page(e);
}

void wifi_stop_sniffer()
{
    // TODO: Implement action wifi_stop_sniffer here
    attack.stop_sniff();
    stop_wifi_sniffer_updater();
    attack.clean_networks();
    wifi_sniffer_running = false;
}