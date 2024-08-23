/*
 * This file is part of the Capibara zero (https://github.com/CapibaraZero/fw or
 * https://capibarazero.github.io/). Copyright (c) 2024 Andrea Canale.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "gui.hpp"

#include <list>

#include "../../include/device_info.h"
#include "GFXForms.hpp"
#include "i18n.hpp"
#include "i18n/main_page_keys.h"
#include "style.h"
#include "./ui_tasks/battery_monitor/battery_monitor_task.hpp"

void Gui::init_gui() {
  Serial.println("Init"); // For some really strange reason this is needed to avoid UI glitches
  if(main_page == nullptr) {
  #ifdef CONFIG_IDF_TARGET_ESP32S2
    main_page = new MainPage(5, 0, 4, screen, this);
  #else
    main_page = new MainPage(6, 0, 4, screen, this);
  #endif
    main_page->display();
    battery_monitor_task_params.page = main_page;
    xTaskCreate(battery_monitor_task, "battery_monitor_ui", 2000, &battery_monitor_task_params, tskIDLE_PRIORITY, NULL);
  }else {
    main_page->display();
    delete current_page;
    current_page = nullptr;
  }
  battery_monitor_task_params.visible = true;
}

void Gui::click_element() {
  if(current_page != nullptr)
    current_page->click();
  else
    main_page->click();
}

void Gui::up() {
  if(current_page != nullptr)
    current_page->up();
  else
    main_page->up();
}

void Gui::down() {
  if(current_page != nullptr)
    current_page->down();
  else
    main_page->down();
}

void Gui::left() {
  if(current_page != nullptr)
    current_page->left();
  else
    main_page->left();
}

void Gui::right() {
  if(current_page != nullptr)
    current_page->right();
  else
    main_page->right();
}

void Gui::set_current_page(Page *page, bool display) {
  while(battery_monitor_task_params.lock) {
    NOP();  // Wait
  }
  battery_monitor_task_params.visible = false;
  delete current_page;
  current_page = page;
  if(display) 
    page->display();
}