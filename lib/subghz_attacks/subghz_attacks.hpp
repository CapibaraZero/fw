#include "SubGHZ.hpp"
#include "gui.hpp"

void frequency_analyzer_attack(SubGHZ *subghz, Gui *gui);
void stop_subghz_attack();
void raw_record_attack(SubGHZ *subghz, Gui *gui);
void stop_raw_record_attack(SubGHZ *subghz);
void start_subghz_emulation_attack(SubGHZ *subghz, Gui *gui,
                                   std::string capture_path);