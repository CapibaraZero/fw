#include "../UI/navigation/IR/IRNavigation.hpp"
#include "IrFramework.hpp"
#include "ir_attacks_types.h"

void ir_record_signal_task(void *pv) {
  IrAttackTaskParams *params = static_cast<IrAttackTaskParams *>(pv);
  IrFramework *ir_framework = params->ir_framework;
  while (!ir_framework->read_signal()) {
    NOP();
  }
  RecordedSignal data = ir_framework->get_decoded_signal();
  Serial.println("Signal decoded successfully");
  Serial.println(data.protocol);
  params->page->set_signal(ir_framework->enum_to_str(data.protocol),
                           data.address, data.command, data.raw_len);
  vTaskDelete(NULL);
}

extern RecordedSignal json_to_signal(JsonDocument signal);

void ir_list_emit(void *pv) {
  IrAttackTaskParams *params = static_cast<IrAttackTaskParams *>(pv);
  IrFramework *ir_framework = params->ir_framework;
  JsonDocument *signals = params->signal;
  size_t index = 0;
  for (JsonDocument signal : signals->as<JsonArray>()) {
    float progress = (100 * index++) / signals->size();
    params->progress_page->set_progress(progress);
    RecordedSignal parsed_signal = json_to_signal(signal);
    ir_framework->send_protocol_signal(parsed_signal);
  }
  go_back_to_ir_browser();
  delete signals;  // Delete old JSON signal since it's not used anymore
  vTaskDelete(NULL);
}