extern bool wifi_scan_finished;
extern vector<WifiNetwork> networks;
void wifi_scan_task(void *pv);
void wifi_sniff_task(void *pv);
void wifi_sniff_bssid(void *pv);