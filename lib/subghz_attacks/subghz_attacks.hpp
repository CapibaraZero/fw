#include "SubGHZ.hpp"

void frequency_analyzer_attack(SubGHZ *subghz);
void stop_subghz_attack();
void raw_record_attack(SubGHZ *subghz);
void stop_raw_record_attack(SubGHZ *subghz);
void start_subghz_emulation_attack(SubGHZ *subghz,
                                   std::string capture_path);