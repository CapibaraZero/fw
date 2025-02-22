#include "ArduinoJson.h"
#include "config_struct.h"
#include "posixsd.hpp"

#define SUBGHZ_CONFIG_FILE "/subghz/config.json"

#define FREQ_CHECK(x) \
  (x >= 300 && x <= 348) || (x >= 387 && x <= 464) || (x >= 779 && x <= 928)

#define DEFAULT_FREQUENCY 433.92
#define DEFAULT_BANDWIDTH 650.0
#define DEFAULT_DEVIATION 47.60
#define DEFAULT_MODULATION 0  // ASK
#define DEFAULT_RSSI_THRESHOLD -90

static void param_check(float value, const char *name, float initial_range,
                        float end_range, float default_value, float *var) {
  if (value >= initial_range && value <= end_range) {
    *var = value;
  } else {
    Serial.printf("Invalid value for %s. Using default value %f\n", name,
                  default_value);
  }
}

static void param_check_int(float value, const char *name, float initial_range,
                            float end_range, float default_value, int *var) {
  if (value >= initial_range && value <= end_range) {
    *var = value;
  } else {
    Serial.printf("Invalid value for %s. Using default value %f\n", name,
                  default_value);
  }
}

#define CONFIG_SIZE 300

bool parse_lora_freq_analyzer() {
  File subghz_config_file = SD.open("/subghz/config.json", "r");
  Serial.println("Loading Subghz configuration2");

  if (!subghz_config_file.available()) {
    Serial.println("Error: Subghz configuration file not exists");
    return false;
  }
  JsonDocument doc;
  DeserializationError error = deserializeJson(doc, subghz_config_file);
  if (error) {
    Serial.printf("Error: %s", error.c_str());
    Serial.println(
        "Error during deserialization of configuration. Using default "
        "configuration");
    return false;
  }
  JsonObject freq_analyzer_config = doc["frequency_analyzer"];
  subghz_config_file.close();

  return freq_analyzer_config["lora"];
}

SubGHZRAWRecorderConfig parse_raw_record_config() {
  SubGHZRAWRecorderConfig params;
  params.freq = DEFAULT_FREQUENCY;
  params.bw = DEFAULT_BANDWIDTH;
  params.deviation = DEFAULT_DEVIATION;
  params.modulation = DEFAULT_MODULATION;
  params.rssi_threshold = -80;

  File subghz_config_file = SD.open("/subghz/config.json", "r");
  Serial.println("Loading Subghz configuration2");

  if (!subghz_config_file.available()) {
    Serial.println("Error: Subghz configuration file not exists");
    return params;
  }
  JsonDocument doc;
  DeserializationError error = deserializeJson(doc, subghz_config_file);
  if (error) {
    Serial.printf("Error: %s", error.c_str());
    Serial.println(
        "Error during deserialization of configuration. Using default "
        "configuration");
    return params;
  }
  JsonObject raw_record_config = doc["raw_record"].as<JsonObject>();
  float raw_record_config_frequency = raw_record_config["frequency"];
  float raw_record_config_bandwidth = raw_record_config["bandwidth"];
  float raw_record_config_deviation = raw_record_config["deviation"];
  int raw_record_config_modulation = raw_record_config["modulation"];
  float raw_record_config_rssi_threshold = raw_record_config["rssi_threshold"];

  Serial.printf("Frequency: %f\n", raw_record_config_frequency);
  Serial.printf("Bandwidth: %f\n", raw_record_config_bandwidth);
  Serial.printf("Deviation: %f\n", raw_record_config_deviation);
  Serial.printf("Modulation: %d\n", raw_record_config_modulation);
  Serial.printf("RSSI threshold: %f\n", raw_record_config_rssi_threshold);

  if (raw_record_config["frequency"].isNull()) {
    Serial.printf("Frequency is null. Using default frequency: %f\n",
                  DEFAULT_FREQUENCY);
  } else {
    if (FREQ_CHECK(raw_record_config["frequency"].as<int>()))
      params.freq = raw_record_config_frequency;
    else
      Serial.printf("Invalid frequency value %f. Using %f MHz",
                    raw_record_config["frequency"], DEFAULT_FREQUENCY);
  }

  if (raw_record_config["bandwidth"].isNull()) {
    Serial.printf("Bandwidth is null. Using default bandwidth: %f\n",
                  DEFAULT_BANDWIDTH);
  } else {
    param_check(raw_record_config_bandwidth, "Bandwidth", 58.03, 812.50,
                DEFAULT_BANDWIDTH, &params.bw);
  }

  if (raw_record_config["deviation"].isNull()) {
    Serial.printf("Deviation is null. Using default deviation: %f\n",
                  DEFAULT_DEVIATION);
  } else {
    param_check(raw_record_config_deviation, "Deviation", 1.58, 380.85,
                DEFAULT_DEVIATION, &params.deviation);
  }

  if (raw_record_config["modulation"].isNull()) {
    Serial.printf("Modulation is null. Using default modulation: %d\n",
                  DEFAULT_MODULATION);
  } else {
    param_check_int(raw_record_config_modulation, "Modulation", 0, 4,
                    DEFAULT_MODULATION, &params.modulation);
  }

  if (raw_record_config["rssi_threshold"].isNull())
    Serial.printf("RSSI threshold is null. Using default value %f\n",
                  DEFAULT_RSSI_THRESHOLD);
  else {
    if (raw_record_config["rssi_threshold"].as<int>() > 0)
      Serial.printf(
          "RSSI threshold can't be positive. Using default value %f\n",
          DEFAULT_RSSI_THRESHOLD);
    else
      params.rssi_threshold = raw_record_config["rssi_threshold"];
  }

  Serial.printf("Frequency: %f\n", params.freq);
  Serial.printf("Bandwidth: %f\n", params.bw);
  Serial.printf("Deviation: %f\n", params.deviation);
  Serial.printf("Modulation: %d\n", params.modulation);
  Serial.printf("RSSI Threshold: %f\n", params.rssi_threshold);
  subghz_config_file.close();

  return params;
}

SubGHZCapture parse_json_subghz_capture(std::string path) {
  File file = open(path.c_str(), "r");
  JsonDocument doc;
  SubGHZCapture capture;
  DeserializationError error = deserializeJson(doc, file);
  if (error) {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
    return capture;
  }
  file.close();
  capture = {.freq = doc["frequency"],
             .bw = doc["bandwidth"],
             .deviation = doc["deviation"],
             .modulation = doc["modulation"],
             .len = doc["data_length"]};
  capture.data = new uint8_t[capture.len];
  // TODO: Try to do in a more efficient way
  for (int i = 0; i < capture.len; i++) {
    capture.data[i] = doc["data"][i];
  }
  return capture;
}