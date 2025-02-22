#include "../Page.hpp"
#include "GFXForms.hpp"
#include "Grid.hpp"
#include "List.hpp"
#include "Text.hpp"

#ifndef DHCPGLUTTON_PAGE_H
#define DHCPGLUTTON_PAGE_H

class DHCPGluttonPage : public Page {
 private:
  Text *text;
  Text *client_count;
  List *save;

 public:
  DHCPGluttonPage(uint8_t _position_limit, uint8_t _lower_limit,
                  uint8_t _position_increment, GFXForms *screen)
      : Page(_position_limit, _lower_limit, _position_increment, screen) {
        };
  ~DHCPGluttonPage();
  void display();
  void update_packet_count(int count);
};

#endif
