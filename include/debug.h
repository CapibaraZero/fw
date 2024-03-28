#ifdef ARDUINO_NANO_ESP32
#define SERIAL_DEVICE Serial
#else
#define SERIAL_DEVICE Serial0
#endif

#define LOG_ERROR(reason) SERIAL_DEVICE.printf("\e[31m%s\e[0m", reason)
#define LOG_SUCCESS(reason) SERIAL_DEVICE.printf("\e[32m%s\e[0m", reason)
#define LOG_INFO(reason) SERIAL_DEVICE.printf("%s", reason)