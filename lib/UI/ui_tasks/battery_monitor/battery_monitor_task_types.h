#include <mutex>

#ifndef BATTERY_MONITOR_TASK_TYPES_H
#define BATTERY_MONITOR_TASK_TYPES_H

typedef struct {
  bool visible = false;
  bool lock = false;
} BatteryMonitorTaskParams;

#endif