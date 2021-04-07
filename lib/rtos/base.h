// Copyright 2021 <Some Dude>

#pragma once

#include <stdint.h>

namespace rtos {

/**
 * @brief Abstract interface class that will be used as a base for the RTOS HAL
 *
 */
class RtosWrapperBase {
 public:
  /**
   * @brief Interface function for wrapping the FreeRTOS vTaskDelay function
   *
   * @param[in] xTicksToDelay: the number of ticks to delay
   */
  virtual void TaskDelay(const uint32_t xTicksToDelay) = 0;

  virtual ~RtosWrapperBase() {}
};

}  // namespace rtos
