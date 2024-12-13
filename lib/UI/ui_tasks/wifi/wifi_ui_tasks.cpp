#include <Arduino.h>

#include "../../navigation/wifi/wifi_navigation.hpp"
#include "wifi_tasks.hpp"
#include "wifi_ui_tasks_types.h"

// Simple lock for sniff GUI task
static bool sniff_progress_lock = false;

bool get_sniffer_lock() { return sniff_progress_lock; }

void update_wifi_sniff_packets(void *pv) {
  WiFiUITaskParameters *params = static_cast<WiFiUITaskParameters *>(pv);
  while (params->wifi_attack->sniffer_running()) {
    sniff_progress_lock = true;
    update_packets_count(params->wifi_attack->get_sniffed_packets());
    sniff_progress_lock = false;
    delay(1000);
  }
  vTaskDelete(NULL);
}

void update_wifi_scan_progress(void *pv) {
  WiFiUITaskParameters *params = static_cast<WiFiUITaskParameters *>(pv);
  const double progress_step = 100.0 / 13.0;
  const double lower_limit = 100 + progress_step - 1;  // While limit
  double progress = progress_step;
  int ch = 1;
  while (progress < lower_limit)  // Until 100%
  {
    set_progress((char *)(String(progress) + String("%")).c_str());
    set_wifi_channel_text((char *)(String("Channel: ") + String(ch)).c_str());
    ch++;
    progress += progress_step;  // 13 ch scan
    delay(3000);                // ch change time
  }
  while (params->wifi_attack->sniffer_running()) {
    delay(1);
  }
  params->gui->reset();
  vector<WifiNetwork> networks = params->wifi_attack->get_networks();
  init_wifi_networks_gui(&networks);
  vTaskDelete(NULL);
}