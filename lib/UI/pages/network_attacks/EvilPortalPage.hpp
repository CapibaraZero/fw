#include "../Page.hpp"
#include "GFXForms.hpp"
#include "Grid.hpp"
#include "List.hpp"
#include "Text.hpp"

#ifndef EVILPORTAL_PAGE_H
#define EVILPORTAL_PAGE_H

class EvilPortalPage : public Page {
 private:
  Text *text;
  Text *client_count;
  Text *portal_ip;
  List *save;
  Grid *details_grid;

 public:
  EvilPortalPage(GFXForms *_screen);
  ~EvilPortalPage();
  void display() { details_grid->display(); }
  void update_requests_count(int count);
  void set_portal_ip(String ip);
  void up() {};
  void down() {};
  void left() {};
  void right() {};
};

#endif
