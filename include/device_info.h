#define VERSION "0.5.1"  // Current FW version

/* Device that we are building */
#ifdef CONFIG_IDF_TARGET_ESP32
#define DEVICE "ESP32"
#elif CONFIG_IDF_TARGET_ESP32S2
#define DEVICE "ESP32-S2"
#elif CONFIG_IDF_TARGET_ESP32S3
#define DEVICE "ESP32-S3"
#endif