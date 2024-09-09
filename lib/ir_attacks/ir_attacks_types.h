#ifndef IR_ATTACK_TASK_PARAMS_H
#define IR_ATTACK_TASK_PARAMS_H

#include "GFXForms.hpp"
#include "pages/IR/IRRecordSignalPage.hpp"
#include "pages/IR/IRListsProgress.hpp"
#include "ArduinoJson.h"
class IrFramework;

typedef struct {
    IrFramework *ir_framework;
    JsonDocument *signal;
    IRRecordSignalPage *page;
    IRListsProgress *progress_page;
}IrAttackTaskParams;

#endif