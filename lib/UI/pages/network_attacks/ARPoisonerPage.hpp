#include "../Page.hpp"
#include "GFXForms.hpp"
#include "Grid.hpp"
#include "List.hpp"
#include "Text.hpp"

#ifndef ARPOISONER_PAGE_H
#define ARPOISONER_PAGE_H

class ARPoisonerPage : public Page {
 private:
  Text *text;
  List *stop;

 public:
  ARPoisonerPage(uint8_t _position_limit, uint8_t _lower_limit,
                 uint8_t _position_increment, GFXForms *screen)
      : Page(_position_limit, _lower_limit, _position_increment, screen) {
        };
  ~ARPoisonerPage();
  void display();
};

#endif
