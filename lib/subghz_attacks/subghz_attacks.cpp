#include "../UI/navigation/SubGHZ/SubGHZNavigation.hpp"
#include "config_parser.hpp"
#include "fm.hpp"
#include "posixsd.hpp"
#include "subghz_tasks.hpp"

TaskHandle_t subghz_task_handle = NULL;
static SubGHZTaskParameters *params = NULL;

void frequency_analyzer_attack(SubGHZ *subghz, Gui *gui) {
  params = (SubGHZTaskParameters *)malloc(sizeof(SubGHZTaskParameters));
  params->subghz = subghz;
  params->gui = gui;
  if (parse_lora_freq_analyzer())
    subghz->set_modulation(2);
  else
    subghz->init_receive();
  xTaskCreate(frequency_analyzer, "subghz_frequency_analyzer", 8192, params, 5,
              &subghz_task_handle);
}

void stop_subghz_attack() {
  vTaskDelete(subghz_task_handle);
  subghz_task_handle = NULL;
  free(params);
}

void raw_record_attack(SubGHZ *subghz, Gui *gui) {
  Serial.println("raw_record_attack");
  params = (SubGHZTaskParameters *)malloc(sizeof(SubGHZTaskParameters));
  SubGHZRAWRecorderConfig config = parse_raw_record_config();
  params->subghz = subghz;
  params->gui = gui;
  params->rssi_threshold = config.rssi_threshold;
  subghz->init_receive();
  subghz->set_modulation(config.modulation);
  subghz->set_freq_mod(config.freq, config.bw, config.deviation);
  set_subghz_raw_record_freq(config.freq);
  xTaskCreate(raw_record_task, "subghz_raw_record_task", 8192, params, 5,
              &subghz_task_handle);
}

void start_subghz_emulation_attack(SubGHZ *subghz, Gui *gui,
                                   std::string capture_path) {
  Serial.println("start_emulation_attack");
  params = (SubGHZTaskParameters *)malloc(sizeof(SubGHZTaskParameters));
  params->subghz = subghz;
  params->gui = gui;
  SubGHZCapture signal = parse_json_subghz_capture(capture_path);
  set_subghz_sender_freq(signal.freq);
  set_subghz_sender_deviation(signal.deviation);
  set_subghz_sender_bandwidth(signal.bw);
  set_subghz_sender_modulation(signal.modulation);
  Modulation signal_params = {
      .mode = signal.modulation,
      .deviation = signal.deviation,
      .bandwidth = signal.bw,
  };
  subghz->send_signal(signal.freq, signal_params, signal.data, signal.len);
}