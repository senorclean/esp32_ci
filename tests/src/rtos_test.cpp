// Copyright 2021 <Some Dude>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <ostream>

#include "lib/rtos/rtos.h"
#include "mocks/rtos_hal.h"

using ::testing::_;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgPointee;

/**
 * @brief A suite of tests aimed at testing the RTOS wrapper
 *
 */
class RtosTests : public testing::Test {
 public:
  MockRtosHAL* mock_rtos_hal;
  rtos::RtosWrapper* rtos_dev;

 protected:
  void SetUp() override {
    mock_rtos_hal = new MockRtosHAL;
    rtos_dev = new rtos::RtosWrapper(mock_rtos_hal);
  }

  void TearDown() override { delete rtos_dev; }
};

/**
 * @brief Run RandomTest
 *
 * This test is just here to verify that the mock HAL interface is called when it is used in place
 * of the target implementation. The function tested here is vTaskDelay
 *
 */
TEST_F(RtosTests, RandomTest) {
  // setup

  // expect
  // initialization
  EXPECT_CALL(*mock_rtos_hal, TaskDelay(1000)).Times(1);

  rtos_dev->vTaskDelay(1000);

  // assert
}
