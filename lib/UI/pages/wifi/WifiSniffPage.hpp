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
  Grid *details_grid;

 public:
  WifiSniffPage(GFXForms *_screen);
  ~WifiSniffPage();
  void display() { details_grid->display(); }
  void update_packet_count(int count);
  void up() {};
  void down() {};
  void left() {};
  void right() {};
};

#endif