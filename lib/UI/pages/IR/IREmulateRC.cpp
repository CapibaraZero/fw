#include "IREmulateRC.hpp"

#include "../../navigation/IR/IRNavigation.hpp"
#include "style.h"

IREmulateRC::~IREmulateRC() { delete go_back; }

void IREmulateRC::display(const char* cmd[], size_t count) {
  grid = new Grid(screen, 2, 4);
  for (size_t i = 0; i < count; i++) {
    grid->add(new RectText(screen, cmd[i], HOME_TEXT_SIZE, HOME_TEXT_COLOR,
                           HOME_ICON_HEIGHT, HOME_ICON_RADIUS, HOME_ICON_COLOR,
                           emulate_ir_rc));
  }
  go_back = new List(screen, "Go back", 2, ST77XX_WHITE, 20, ST77XX_BLACK,
                     goto_ir_gui);
  grid->add(go_back);
  grid->set_pos(0, 10);
  grid->set_space_between(10);
  grid->set_padding(0, 20);
  grid->display();
  grid->set_selected(0, true);
}

void IREmulateRC::right() {
  if (position_limit <= 4) return;
  if (current_position >= 0 && current_position < position_limit) {
    grid->set_selected(current_position, false);
    current_position++;
  }
  grid->set_selected(current_position, true);
}

void IREmulateRC::left() {
  if (position_limit <= 4) return;
  if (current_position > 0 && current_position <= position_limit) {
    grid->set_selected(current_position, false);
    current_position--;
  }
  grid->set_selected(current_position, true);
}

void IREmulateRC::display() {}