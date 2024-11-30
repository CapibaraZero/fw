#include "ArduinoJson.h"
#include "IrFramework.hpp"
#include "pages/IR/IRListsProgress.hpp"
#include "pages/IR/IRRecordSignalPage.hpp"

TaskHandle_t ir_record_signal(IRRecordSignalPage *page, IrFramework *framework);
void ir_send_signal(IrFramework *framework, JsonDocument *signal_doc,
                    IRListsProgress *progress_page = NULL,
                    TaskHandle_t *list_handler = NULL);