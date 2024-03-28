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

#include <ESPAsyncWebServer.h>

#include "Arduino.h"

int captured_requests = 0;

void captive_portal_callback(AsyncWebServerRequest *request) {
  for (size_t i = 0; i < request->args(); i++) {
#ifdef ARDUINO_NANO_ESP32
    Serial.printf("%s: %s\n", request->argName(i), request->arg(i));
#else
    Serial0.printf("%s: %s\n", request->argName(i), request->arg(i));
#endif
    request->send(200);
    captured_requests++;
  }
}

int get_captured_requests() { return captured_requests; }

void reset_captured_requests() { captured_requests = 0; }