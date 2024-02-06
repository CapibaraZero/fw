#include "GFXForms.hpp"
#include "Grid.hpp"
#include "List.hpp"
#include "../Page.hpp"
#include "Text.hpp"

#ifndef DHCPGLUTTON_PAGE_H
#define DHCPGLUTTON_PAGE_H

class DHCPGluttonPage : public Page {
 private:
  Text *text;
  Text *client_count;
  List *save;
  Grid *details_grid;

 public:
  DHCPGluttonPage(GFXForms *_screen);
  ~DHCPGluttonPage();
  void display() {
    details_grid->display();
  }
  void update_packet_count(int count);
  void up() {
  };
  void down() {
  };
  void left(){};
  void right(){};
};

#endif
