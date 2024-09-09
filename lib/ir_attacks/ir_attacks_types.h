#ifndef IR_ATTACK_TASK_PARAMS_H
#define IR_ATTACK_TASK_PARAMS_H

#include "GFXForms.hpp"
#include "pages/IR/IRRecordSignalPage.hpp"
class IrFramework;

typedef struct {
    IrFramework *ir_framework;
    IRRecordSignalPage *page;
}IrAttackTaskParams;

#endif