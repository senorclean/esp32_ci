cmake_minimum_required(VERSION 3.6)
project (esp32_test C CXX ASM)

set(OUTPUT_FILE ${CMAKE_PROJECT_NAME}.out)

set(OPT_FLAGS "-g3 -O0")

set(PROJECT_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../..)
set(TESTS_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/..)
set(LIB_RTOS_DIR ${PROJECT_ROOT_DIR}/lib/rtos)

# compilation flags
set(CMAKE_C_FLAGS "${OPT_FLAGS} fpermissive -fno-builtin -Wall -fdata-sections -ffunction-sections -fno-strict-aliasing -fshort-enums")
set(CMAKE_CXX_FLAGS "${OPT_FLAGS} -fpermissive -fno-rtti -fno-builtin -Wall -std=c++11 -fdata-sections -ffunction-sections")

find_package(PkgConfig)
pkg_check_modules(GTEST "gtest" REQUIRED)
pkg_check_modules(GMOCK "gmock" REQUIRED)

# test files
set (USER_SRCS ${TESTS_ROOT_DIR}/src/main_test.cpp)
set (USER_SRCS ${USER_SRCS} "${TESTS_ROOT_DIR}/src/rtos_test.cpp")

# files from the real application
set (USER_SRCS ${USER_SRCS} "${LIB_RTOS_DIR}/rtos.cpp")

# testing definition to ignore some aspects of real application that we can't compile on host
# add_definitions(
#                 -DTESTING
#                 )

include_directories(
  ${PROJECT_ROOT_DIR}
  ${TESTS_ROOT_DIR}
)

add_executable(${OUTPUT_FILE} ${USER_SRCS})

target_link_libraries(${OUTPUT_FILE} c ${GTEST_LIBRARIES} ${GMOCK_LIBRARIES} pthread)

add_custom_target(so_fresh_and_so_clean
  COMMAND rm CMakeCache.txt
  COMMAND rm -r CMakeFiles
  COMMAND rm cmake_install.cmake
  COMMENT "Cleaning build directory"
)
