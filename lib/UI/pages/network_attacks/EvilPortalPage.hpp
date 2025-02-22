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

 public:
  EvilPortalPage(uint8_t _position_limit, uint8_t _lower_limit,
                 uint8_t _position_increment, GFXForms *screen)
      : Page(_position_limit, _lower_limit, _position_increment, screen) {
        };
  ~EvilPortalPage();
  void display();
  void update_requests_count(int count);
  void set_portal_ip(String ip);
};

#endif
