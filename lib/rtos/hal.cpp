// Copyright 2021 <Some Dude>

#include "lib/rtos/hal.h"

extern "C" {
#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
}

namespace rtos {

void RtosWrapperHAL::TaskDelay(const uint32_t xTicksToDelay) { vTaskDelay(xTicksToDelay); }

}  // namespace rtos
