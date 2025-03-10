#include "lvgl.h"
#include "screens.h"
#include "ui.h"
#include "string"
#include "ui_helper.hpp"
#include "Arduino.h"
#include "posixsd.hpp"
#include "sdcard_helper.hpp"
#include "parser.hpp"
#include "usb_hid/USBHid.hpp"
#include <list>
#include <vector>
#include "../../include/debug.h"

extern objects_t objects;

std::vector<std::string> files;
extern FILE *yyin;
extern USBHid hid;  // From DuckyESP

void action_go_to_main_page(lv_event_t *e)
{
    hid.end();
#ifndef ESP32S3_DEVKITC_BOARD
    Serial.begin(115200);
#endif

    create_screen_main();
    loadScreen(SCREEN_ID_MAIN);
}

void parse_badusb_file(lv_event_t *e)
{
    const char *path = (const char *)e->user_data;
    FILE *file = fopen(((String)"/sd/ducky/" + path).c_str(), "r");
    if (!file) {
    #ifdef ESP32S3_DEVKITC_BOARD
      LOG_ERROR("Failed to open file");
    #endif
      return;
    }
    yyin = file;
    yyparse();
    fclose(file);
}

void create_screen_file_explorer_dinamically()
{
    // Create initial page
    lv_obj_t *main_obj = lv_obj_create(0);
    objects.file_explorer = main_obj;
    lv_obj_set_pos(main_obj, 0, 0);
    lv_obj_set_size(main_obj, 320, 170);

    // Create container widget with Flex column property
    lv_obj_t *container_obj = lv_obj_create(main_obj);
    lv_obj_set_pos(container_obj, 0, 19);
    lv_obj_set_size(container_obj, 320, 151);
    lv_obj_set_style_pad_left(container_obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(container_obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(container_obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(container_obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(container_obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(container_obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(container_obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_layout(container_obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_flex_flow(container_obj, LV_FLEX_FLOW_COLUMN, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Create buttons for all files
    for (size_t i = 0; i < files.size(); i++)
    {
        create_btn(files[i].c_str(), container_obj, parse_badusb_file, (void *)files[i].c_str());
    }
    

    // Create return
    create_btn("Go back", container_obj, action_go_to_main_page, (void *)0);
    tick_screen_file_explorer();
}

extern "C" void action_go_to_filebrowser(lv_event_t *e)
{
    auto files_list = list_dir(open("/ducky", "r"));    // TODO: Make list_dir return a vector
    files = std::vector<std::string>(files_list.begin(), files_list.end());

#ifdef ESP32S3_DEVKITC_BOARD
    Serial.end();
#endif

    create_screen_file_explorer_dinamically();
    loadScreen(SCREEN_ID_FILE_EXPLORER);
}
