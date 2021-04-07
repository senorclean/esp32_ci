// Copyright 2021 <Some Dude>

#pragma once

#include <gmock/gmock.h>
#include <string>

#include "lib/rtos/base.h"

class MockRtosHAL : public RtosWrapperBase {
 public:
  MOCK_METHOD(void, TaskDelay, (uint32_t xTicksToDelay), (override));
};
