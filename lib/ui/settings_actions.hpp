/*
 * This file is part of the Capibara zero (https://github.com/CapibaraZero/fw or
 * https://capibarazero.github.io/). Copyright (c) 2025 Andrea Canale.
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

#ifndef SETTINGS_ACTIONS_H
#define SETTINGS_ACTIONS_H

#include "lvgl.h"

#ifdef __cplusplus
extern "C" {
#endif

    void action_go_to_settings(lv_event_t *e);
    void action_esp_deep_sleep(lv_event_t *e);

    void action_esp_reboot(lv_event_t *e);
#ifdef __cplusplus
}
#endif

#endif
