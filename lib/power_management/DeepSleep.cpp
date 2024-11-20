#include "../../include/pins.h"
#include "Arduino.h"

#if defined(STANDBY_BTN) && defined(WAKEUP_PIN)

#define GPIO_BITMASK(GPIO) (1ULL << GPIO)

static void IRAM_ATTR standby() {
  digitalWrite(15, LOW);  // Power off CC1101 and LED
  esp_sleep_enable_ext1_wakeup(GPIO_BITMASK(WAKEUP_PIN), ESP_EXT1_WAKEUP_ANY_LOW);
  esp_deep_sleep_start();
}
#endif

#if defined(STANDBY_BTN) && defined(WAKEUP_PIN)
void enable_deep_sleep() {
  pinMode(STANDBY_BTN, INPUT);
  attachInterrupt(STANDBY_BTN, standby, FALLING);
}
#endif