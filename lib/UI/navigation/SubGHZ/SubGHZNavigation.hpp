
#ifndef SUBGHZ_NAVIGATION_H
#define SUBGHZ_NAVIGATION_H

#include "gui.hpp"

void goto_subghz_gui();
void init_subghz_navigation(Gui *_gui);
void stop_frequency_analyzer();
void stop_subghz_raw_record();
void start_subghz_emulation(int pos);
void goto_home_from_subghz();
void subghz_sender_file_browser();
void start_raw_record();
void start_frequency_analyzer();
void set_subghz_freqeuncy(float freq);
void set_subghz_rssi(int rssi);
void set_subghz_raw_record_freq(float freq);
void set_subghz_raw_record_rssi(float rssi);

void set_subghz_sender_freq(float freq);
void set_subghz_sender_bandwidth(float bandwidth);
void set_subghz_sender_deviation(float deviation);
void set_subghz_sender_modulation(int modulation);

#endif
