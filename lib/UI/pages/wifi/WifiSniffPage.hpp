#include "../Page.hpp"
#include "GFXForms.hpp"
#include "Grid.hpp"
#include "List.hpp"
#include "Text.hpp"

#ifndef WIFI_SNIFF_PAGE_H
#define WIFI_SNIFF_PAGE_H

class WifiSniffPage : public Page {
 private:
  // GFXForms *_screen;
  Text *text;
  Text *packet_count;
  List *save;

 public:
  WifiSniffPage(uint8_t _position_limit, uint8_t _lower_limit,
                uint8_t _position_increment, GFXForms *screen)
      : Page(_position_limit, _lower_limit, _position_increment, screen) {
        };
  ~WifiSniffPage();
  void display();
  void update_packet_count(int count);
};

#endif