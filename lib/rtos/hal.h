// Copyright 2021 <Some Dude>

#pragma once

#include "lib/rtos/base.h"

namespace rtos {

/**
 * @brief The RTOS HAL implementation that will run on the target
 *
 */
class RtosWrapperHAL : public RtosWrapperBase {
 public:
  RtosWrapperHAL() {}

  /**
   * @brief Wrapper for the FreeRTOS vTaskDelay function
   *
   * @param[in] xTicksToDelay: the number of ticks to delay
   */
  void TaskDelay(const uint32_t xTicksToDelay);

  ~RtosWrapperHAL() {}
};

}  // namespace rtos
