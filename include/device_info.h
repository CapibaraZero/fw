#define VERSION "0.5.2"  // Current FW version

/* Device that we are building */
#ifdef CONFIG_IDF_TARGET_ESP32
#define DEVICE "ESP32"
#elif CONFIG_IDF_TARGET_ESP32S2
#define DEVICE "ESP32-S2"
#elif CONFIG_IDF_TARGET_ESP32S3
#define DEVICE "ESP32-S3"
#elif CONFIG_IDF_TARGET_ESP32C3
#define DEVICE "ESP32-C3"
#endif

#ifdef ESP32S3_DEVKITC_BOARD
#define BOARD_NAME "ESP32-S3 DevKitC"
#elif ARDUINO_NANO_ESP32
#define BOARD_NAME "Arduino Nano ESP32"
#elif LILYGO_T_EMBED_CC1101
#define BOARD_NAME "LilyGo T-Embed CC1101"
#elif ARDUINO_AirM2M_CORE_ESP32C3
#define BOARD_NAME "AirM2M_CORE_ESP32C3"
#else
#define BOARD_NAME "Unknown"
#endif