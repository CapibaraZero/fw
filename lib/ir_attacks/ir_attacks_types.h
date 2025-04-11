#ifndef IR_ATTACK_TASK_PARAMS_H
#define IR_ATTACK_TASK_PARAMS_H

#include "ArduinoJson.h"

class IrFramework;

typedef struct {
  IrFramework *ir_framework;
  JsonDocument *signal;
} IrAttackTaskParams;

#endif