#include <stdint.h>
#include "wifi_attack.hpp"


void update_wifi_sniff_packets(void *pv);
void update_wifi_scan_progress(void *pv);
bool get_sniffer_lock();
void next_network(size_t *pos);
WifiNetwork *get_current_network(size_t pos);