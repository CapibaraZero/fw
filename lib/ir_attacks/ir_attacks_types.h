#ifndef IR_ATTACK_TASK_PARAMS_H
#define IR_ATTACK_TASK_PARAMS_H

#include "ArduinoJson.h"
#include "GFXForms.hpp"
#include "pages/IR/IRListsProgress.hpp"
#include "pages/IR/IRRecordSignalPage.hpp"
class IrFramework;

typedef struct {
  IrFramework *ir_framework;
  JsonDocument *signal;
} IrAttackTaskParams;

#endif