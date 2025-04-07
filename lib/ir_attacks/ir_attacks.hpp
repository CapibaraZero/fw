#include "ArduinoJson.h"
#include "IrFramework.hpp"
#include "pages/IR/IRListsProgress.hpp"
#include "pages/IR/IRRecordSignalPage.hpp"

TaskHandle_t ir_record_signal(IrFramework *framework);
void ir_send_signal(IrFramework *framework, JsonDocument *signal_doc, TaskHandle_t *list_handler = NULL);