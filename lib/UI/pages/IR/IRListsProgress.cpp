#include "IRListsProgress.hpp"

#include "../../navigation/IR/IRNavigation.hpp"
#include "style.h"

IRListsProgress::~IRListsProgress() {
  delete progress;
  delete stop;
}

void IRListsProgress::display() {
  grid = new Grid(screen, 2, 1);
  progress = new Text(screen, ST77XX_WHITE, "Progress: 0%");
  stop = new List(screen, "Stop", 2, ST77XX_WHITE, 20, ST77XX_BLACK,
                  stop_list_sender);
  grid->add(progress);
  grid->add(stop);
  grid->set_pos(0, 10);
  grid->set_space_between(10);
  grid->set_padding(0, 20);
  grid->display();
  grid->set_selected(1, true);
}

void IRListsProgress::right() {
  if (position_limit <= 4) return;
  if (current_position >= 0 && current_position < position_limit) {
    grid->set_selected(current_position, false);
    current_position++;
  }
  grid->set_selected(current_position, true);
}

void IRListsProgress::left() {
  if (position_limit <= 4) return;
  if (current_position > 0 && current_position <= position_limit) {
    grid->set_selected(current_position, false);
    current_position--;
  }
  grid->set_selected(current_position, true);
}