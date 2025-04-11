#include "ui.h"
#include "subghz_attacks.hpp"
#include "SubGHZ.hpp"
#include "../../include/pins.h"

SubGHZ *subghz_attacks = nullptr;

extern "C" void action_go_to_subghz(lv_event_t *e)
{
#ifndef CC1101_SUBGHZ
    subghz_attacks = new SubGHZ(SD_CARD_SCK, SX1276_MISO, SD_CARD_MOSI, SX1276_NSS,
                                SX1276_DIO1, SX1276_DIO2);
#else
    subghz_attacks = new SubGHZ(SD_CARD_SCK, CC1101_MISO, SD_CARD_MOSI, CC1101_CS,
                                CC1101_IO0, CC1101_IO2);
#endif
    create_screen_sub_ghz_page();
    loadScreen(SCREEN_ID_SUB_GHZ_PAGE);
}

extern "C" void action_subghz_start_frequency_analyzer(lv_event_t *e)
{
    frequency_analyzer_attack(subghz_attacks);
    create_screen_sub_ghz_frequency_analyzer_page();
    loadScreen(SCREEN_ID_SUB_GHZ_FREQUENCY_ANALYZER_PAGE);
}

extern "C" void action_stop_subghz_frequency_analyzer(lv_event_t *e)
{
    stop_subghz_attack();
    subghz_attacks->stop_receive();
    create_screen_main();
    loadScreen(SCREEN_ID_MAIN);
}

extern "C" void action_subghz_start_record_raw(lv_event_t *e)
{
    Serial.println("NOT IMPLEMENTED"); // Need to be fixed
}

extern "C" void action_subghz_start_sender(lv_event_t *e)
{
    Serial.println("NOT IMPLEMENTED"); // Need to be fixed
}

extern "C" char * get_subghz_chip_revision() {
#ifndef CC1101_SUBGHZ
    subghz_attacks = new SubGHZ(SD_CARD_SCK, SX1276_MISO, SD_CARD_MOSI, SX1276_NSS,
                               SX1276_DIO1, SX1276_DIO2);
#else
    subghz_attacks = new SubGHZ(SD_CARD_SCK, CC1101_MISO, SD_CARD_MOSI, CC1101_CS,
                               CC1101_IO0, CC1101_IO2);
#endif
    uint16_t version = subghz_attacks->get_chip_version();
    Serial.println(version);

    char *buffer = (char *)malloc(sizeof(char) * 3);
    sprintf(buffer, "%d", version);
    delete subghz_attacks;
    return buffer;
}