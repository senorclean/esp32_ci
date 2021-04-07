#!/bin/bash

shopt -s expand_aliases

target_inc_files=$(find inc/ -maxdepth 1 -type f)
target_src_files=$(find src/ -maxdepth 1 -type f)
target_lib_rtos_files=$(find lib/rtos/ -maxdepth 1 -type f)
test_inc_files=$(find tests/inc/ -maxdepth 1 -type f)
test_src_files=$(find tests/src/ -maxdepth 1 -type f)
test_mock_files=$(find tests/mocks/ -maxdepth 1 -type f)

# run cpplint on relevant directories
if ! (cpplint --quiet \
  $target_inc_files \
  $target_src_files \
  $target_lib_rtos_files \
  $test_inc_files \
  $test_src_files \
  $test_mock_files) ; then
  echo "Linter failed"
  exit 1
fi

echo "Linter was successful"

# run clang-format on relevant directories
if ! (clang-format -n -Werror \
  $target_inc_files \
  $target_src_files \
  $target_lib_rtos_files \
  $test_inc_files \
  $test_src_files \
  $test_mock_files) ; then
  echo "Formatter failed"
  exit 1
fi

echo "Formatter was successful"
