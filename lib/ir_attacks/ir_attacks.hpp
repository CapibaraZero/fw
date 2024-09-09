#include "IrFramework.hpp"
#include "ArduinoJson.h"

void ir_record_signal(IRRecordSignalPage *page, IrFramework *framework);
void ir_send_signal(IrFramework *framework, const char *signal_path);
void ir_send_signal(IrFramework *framework, JsonDocument signal_doc);