// Copyright 2021 <Some Dude>

#include "lib/rtos/rtos.h"
#include <tuple>

namespace rtos {

RtosWrapper::RtosWrapper(RtosWrapperBase* rtos) { m_rtos = rtos; }

void RtosWrapper::vTaskDelay(const uint32_t xTicksToDelay) {
  m_rtos->TaskDelay(xTicksToDelay);
}

}  // namespace rtos
