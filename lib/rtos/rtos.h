// Copyright 2021 <Some Dude>

#pragma once

extern "C" {
#include <stdio.h>
}
#include "lib/rtos/hal.h"

namespace rtos {

/**
 * @brief Implementation-agnostic RTOS wrapper
 *
 * Any class that implements the interface defined in RtosWrapperBase can be used in this class
 *
 */
class RtosWrapper {
 public:
  explicit RtosWrapper(RtosWrapperBase* rtos);

  /**
   * @brief Wrapper for the FreeRTOS vTaskDelay function
   *
   * @param[in] xTicksToDelay: the number of ticks to delay
   */
  void vTaskDelay(const uint32_t xTicksToDelay);

  ~RtosWrapper() {}

 private:
  RtosWrapperBase* m_rtos;
};

}  // namespace rtos
