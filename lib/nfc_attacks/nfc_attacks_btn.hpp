#include "nfc_attacks.hpp"

void mifare_polling(Gui *gui, NFCAttacks *attacks);
void felica_polling(Gui *gui, NFCAttacks *attacks);
void dump_iso14443a(Gui *gui, NFCAttacks *attacks);
void dump_felica(Gui *gui, NFCAttacks *attacks);
void write_tag(Gui *gui, NFCAttacks *attacks, NFCTag *tag);
void write_felica_tag(Gui *gui, NFCAttacks *attacks, NFCTag *tag);
void write_sectors(Gui *gui, NFCAttacks *attacks, const char *path);
void format_iso14443a(Gui *gui, NFCAttacks *attacks);
void format_felica(Gui *gui, NFCAttacks *attacks);
void bruteforce_tag(Gui *gui, NFCAttacks *attacks);
void reset_uid(void);  // From nfc_tasks.cpp
void reset_felica(void);
void destroy_tasks();