#include "wifi_scanner.hpp"

vector<WifiNetwork> wifi_scan() {
    int n = WiFi.scanNetworks();
    vector<WifiNetwork> networks_found = vector<WifiNetwork>();
    for (int i = 0; i < n; i++) {
	WifiNetwork network = WifiNetwork(WiFi.SSID(i), WiFi.RSSI(i), WiFi.BSSID(i), WiFi.channel(i), WiFi.encryptionType(i)); 
	networks_found.push_back(network);
    }

    return networks_found;
}
