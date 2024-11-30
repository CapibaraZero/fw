#ifdef ESP32S3_DEVKITC_BOARD
#define SERIAL_DEVICE Serial0
#else
#define SERIAL_DEVICE Serial
#endif

#define LOG_ERROR(reason) SERIAL_DEVICE.printf("\e[31m%s\e[0m", reason)
#define LOG_SUCCESS(reason) SERIAL_DEVICE.printf("\e[32m%s\e[0m", reason)
#define LOG_INFO(reason) SERIAL_DEVICE.printf("%s", reason)