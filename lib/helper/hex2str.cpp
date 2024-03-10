#include <Arduino.h>
#include <stdint.h>

String hextostr(uint8_t *data, uint8_t len, char separator) {
  String str = "";
  for (size_t i = 0; i < len; i++) {
    str += String(data[i], HEX) + separator;
  }
  return str;
}