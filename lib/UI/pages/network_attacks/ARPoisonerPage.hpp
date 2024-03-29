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
  Grid *details_grid;

 public:
  ARPoisonerPage(GFXForms *_screen);
  ~ARPoisonerPage();
  void display() { details_grid->display(); }
  void up() {};
  void down() {};
  void left() {};
  void right() {};
};

#endif
