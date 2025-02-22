#include "posixsd.hpp"
#include "wifi_attack.hpp"
#include "wifi_sniff_task_types.h"

void wifi_scan_task(void *pv) {
  WifiAttack *attack = static_cast<WifiAttack *>(pv);
  attack->scan();
  vTaskDelete(NULL);
}

void wifi_sniff_task(void *pv) {
  WifiAttack *attack = static_cast<WifiAttack *>(pv);
  attack->sniff(1000, get_current_fs());
  while (attack->sniffer_running()) {
    NOP();
  }
  vTaskDelete(NULL);
}

void wifi_sniff_bssid(void *pv) {
  BSSIDSniff *params = (BSSIDSniff *)pv;
  params->attack->sniff_bssid(params->bssid, params->ch, get_current_fs());
  while (params->attack->sniffer_running()) {
    NOP();
  }
  vTaskDelete(NULL);
}