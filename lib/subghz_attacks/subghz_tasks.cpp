#include <vector>

#include "../UI/navigation/SubGHZ/SubGHZNavigation.hpp"
#include "SubGHZ.hpp"
#include "fm.hpp"
#include "subghz_tasks_type.h"

#define TIME_BETWEEN_SCAN 400

#define RSSI_LIMIT -78

void frequency_analyzer(void *pv) {
  SubGHZTaskParameters *params = (SubGHZTaskParameters *)pv;
  while (true) {
    for (float freq = 139.0; freq < 1020.0; freq++) {
#ifdef CC1101_SUBGHZ
      if (!(((freq >= 300.0) && (freq <= 348.0)) ||
            ((freq >= 387.0) && (freq <= 464.0)) ||
            ((freq >= 779.0) && (freq <= 928.0)))) {
        continue;
      }
#endif
      SignalStrength result = params->subghz->scan_frequency(freq);
      if (result.rssi > RSSI_LIMIT) {
        set_subghz_freqeuncy(freq);
        set_subghz_rssi(result.rssi);
      }
      delay(100);
    }
  }
}

std::vector<byte> raw_signal;

void raw_record_task(void *pv) {
  SubGHZTaskParameters *params = (SubGHZTaskParameters *)pv;
  Serial.println(params->rssi_threshold);
  while (true) {
    if (params->subghz->scan_frequency().rssi >= params->rssi_threshold) {
      params->subghz->rec_signal(&raw_signal);
    }
  }
}