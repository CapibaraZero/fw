#include <Arduino.h>
#include "hex2str.hpp"
#include "wifi_tasks.hpp"
#include "actions/tasks/wifi/wifi_ui_tasks_types.h"
#include "vars.h"
#include "ui.h"

// Simple lock for sniff GUI task
static bool sniff_progress_lock = false;

bool get_sniffer_lock() { return sniff_progress_lock; }

void update_wifi_sniff_packets(void *pv) {
  WiFiUITaskParameters *params = static_cast<WiFiUITaskParameters *>(pv);
  while (params->wifi_attack->sniffer_running()) {
    sniff_progress_lock = true;
    set_var_captured_packets(("Captured packets: " + (String)params->wifi_attack->get_sniffed_packets()).c_str());
    sniff_progress_lock = false;
    delay(1000);
  }
  vTaskDelete(NULL);
}

vector<WifiNetwork> networks;

void next_network(size_t *pos) {
  if(++(*pos) >= networks.size()) {
    *pos = 0;
  }
  WifiNetwork net = networks.at(*pos);
  set_var_wifi_current_ssid(("SSID: " + net.get_ssid()).c_str());
  set_var_wifi_current_bssid(("BSSID: " + hextostr(net.get_bssid(), 6)).c_str());
  set_var_wifi_current_channel(("Channel: " + (String)net.get_channel()).c_str());
  set_var_wifi_current_rssi(("RSSI: " + (String)net.get_rssi()).c_str());
}

WifiNetwork *get_current_network(size_t pos) {
  return &networks.at(pos);
}

void update_wifi_scan_progress(void *pv) {
  WiFiUITaskParameters *params = static_cast<WiFiUITaskParameters *>(pv);
  const double progress_step = 100.0 / 13.0;
  const double lower_limit = 100 + progress_step - 1;  // While limit
  double progress = progress_step;
  int ch = 1;
  delay(6000);  // Wait for stack initialization(5000 WIFI_OFF + 500 WIFI_STA + some tollerance)
  set_var_wifi_scan_info("Wifi Scan in progress...");
  while (progress < lower_limit)  // Until 100%
  {
    set_var_wifi_scan_current_progress((String(progress) + String("%")).c_str());
    set_var_wifi_scan_current_channel((String("Channel: ") + String(ch)).c_str());
    ch++;
    progress += progress_step;  // 13 ch scan
    delay(1000);                // ch change time(300 + 700 to make sure that scan is really finished)
  }
  while (params->wifi_attack->sniffer_running()) {
    delay(1);
  }
  networks = params->wifi_attack->get_networks();
  create_screen_wi_fi_net_view();
  loadScreen(SCREEN_ID_WI_FI_NET_VIEW);
  size_t pos = networks.size();
  next_network(&pos);
  vTaskDelete(NULL);
}