#include "GFXForms.hpp"
#include "Grid.hpp"
#include "List.hpp"
#include "../Page.hpp"
#include "Text.hpp"

#ifndef BLE_SNIFF_PAGE_H
#define BLE_SNIFF_PAGE_H

class BLESniffPage : public Page {
 private:
  // GFXForms *_screen;
  Text *text;
  Text *packet_count;
  List *save;
  Grid *details_grid;

 public:
  BLESniffPage(GFXForms *_screen);
  ~BLESniffPage();
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
