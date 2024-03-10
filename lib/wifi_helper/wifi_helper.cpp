#include <WiFi.h>

void init_ap() { WiFi.mode(WIFI_AP); }

void init_ap(const char *ssid, const char *pwd, IPAddress apIP,
             IPAddress subnet) {
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid);
  WiFi.softAPConfig(apIP, apIP, subnet);
}
