#include "ui.h"
#include "wifi_actions.hpp"
#include "ble_actions.hpp"

extern bool wifi_sniffer_running;

extern "C" void action_wifi_stop_sniffer(lv_event_t *e)
{
    if(wifi_sniffer_running) {
        wifi_stop_sniffer();
    } else {
        stop_ble_sniffer();
    }
    action_go_to_main_page(e);
}