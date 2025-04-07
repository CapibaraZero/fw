#include "../UI/navigation/IR/IRNavigation.hpp"
#include "IrFramework.hpp"
#include "ir_attacks_types.h"
#include "vars.h"
#include "ir_actions.hpp"

void ir_record_signal_task(void *pv) {
  IrAttackTaskParams *params = static_cast<IrAttackTaskParams *>(pv);
  IrFramework *ir_framework = params->ir_framework;
  while (!ir_framework->read_signal()) {
    delay(1); // Avoid watchdog WDT
  }
  RecordedSignal data = ir_framework->get_decoded_signal();
  Serial.println("Signal decoded successfully");
  Serial.println(data.protocol);

  set_var_ir_protocol(("Protocol: " + ir_framework->enum_to_str(data.protocol)).c_str());
  set_var_ir_addr(("Address: " + String(data.address, HEX)).c_str());
  set_var_ir_cmd(("CMD: " + String(data.command, HEX)).c_str());
  set_var_ir_len(("Length: " + String(data.raw_len)).c_str());

  set_var_ir_retry(false);  // Show retry and save button
  set_var_ir_save(false);
  // params->page->set_signal(ir_framework->enum_to_str(data.protocol),
  //                          data.address, data.command, data.raw_len);
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
    set_var_ir_emulate_progress(("Progress: " + String(progress)).c_str());
    RecordedSignal parsed_signal = json_to_signal(signal);
    ir_framework->send_protocol_signal(parsed_signal);
  }

  action_go_to_ir_page(NULL);
  // go_back_to_ir_browser();
  delete signals;  // Delete old JSON signal since it's not used anymore
  vTaskDelete(NULL);
}