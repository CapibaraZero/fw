#include "SubGHZ.hpp"
#include "subghz_tasks_type.h"
#include "fm.hpp"
#include <vector>
#include "../UI/navigation/SubGHZ/SubGHZNavigation.hpp"

#define TIME_BETWEEN_SCAN 400

void frequency_analyzer(void *pv) {
    SubGHZTaskParameters *params = (SubGHZTaskParameters *)pv;
    while (true) {
        for (size_t freq = 139.0; freq < 1020.0; freq++)
        {
            SignalStrength result = params->subghz->scan_frequency(freq);
            if (result.rssi > -74) {
                set_subghz_freqeuncy(freq);
                set_subghz_rssi(result.rssi);
            }
        }
    }
}

std::vector<byte> raw_signal;

void raw_record_task(void *pv) {
    SubGHZTaskParameters *params = (SubGHZTaskParameters *)pv;
    Serial.println(params->rssi_threshold);
    while (true)
    {    
        if(params->subghz->scan_frequency().rssi >= params->rssi_threshold) {
            params->subghz->rec_signal(&raw_signal);
        }
    }
}