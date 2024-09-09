#include "IrFramework.hpp"
#include "ir_attacks_task.hpp"
#include "ir_attacks_types.h"
#include "posixsd.hpp"
#include "ArduinoJson.h"

#include "FreeRTOS.h"
#include "freertos/task.h"

void ir_record_signal(IRRecordSignalPage *page, IrFramework *framework) {
    IrAttackTaskParams params = {
        .ir_framework = framework,
        .page = page
    };
    xTaskCreate(ir_record_signal_task, "ir_record_signal_task", 8000, &params, 5, NULL);
}

RecordedSignal json_to_signal(JsonDocument signal) {
    RecordedSignal parsed_signal;
    parsed_signal.protocol = signal["protocol"];
    JsonArray raw_data = signal["raw_data"];
    uint16_t len = signal["raw_len"];
    parsed_signal.address = signal["address"];
    parsed_signal.command = signal["command"];
    parsed_signal.decodedRawData = signal["decoded_raw_data"];
    parsed_signal.numberOfBits = signal["number_of_bits"];
    parsed_signal.flags = signal["flags"];
    /* Only PulseWidth/PulseDistance and Unknown require decodedRawDataArray, so memory for others protocols */
    if(parsed_signal.protocol >= 0 && parsed_signal.protocol <= 2) {
        for (size_t i = 0; i < len; i++)
        {
            parsed_signal.decodedRawDataArray[i] = raw_data[i];
        }
    }
    parsed_signal.raw_len = len;
    return parsed_signal;
}

void ir_send_signal(IrFramework *framework, const char *signal_path) {
    File signal_file = open(signal_path, "r");
    JsonDocument signal_doc;
    deserializeJson(signal_doc, signal_file);
    if(signal_doc.is<JsonArray>()) {
        Serial.println("JsonArray");
        for(JsonDocument signal : signal_doc.as<JsonArray>()) {
            RecordedSignal parsed_signal = json_to_signal(signal);
            
            framework->send_protocol_signal(parsed_signal);
        }
    } else {
        RecordedSignal parsed_signal = json_to_signal(signal_doc);
        framework->send_protocol_signal(parsed_signal);
    }
}

void ir_send_signal(IrFramework *framework, JsonDocument signal_doc) {
    RecordedSignal parsed_signal = json_to_signal(signal_doc);
    framework->send_protocol_signal(parsed_signal);
}