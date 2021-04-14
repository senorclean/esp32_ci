cmake_minimum_required(VERSION 3.5)
project(esp32 C CXX)

set(OUTPUT_FILE ${CMAKE_PROJECT_NAME}.elf)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Convenience variables
set(PROJECT_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/..)
set(LIB_RTOS_DIR ${PROJECT_ROOT_DIR}/lib/rtos)
set(OUTPUT_DIR ${PROJECT_ROOT_DIR}/build/build)
set(SIZE xtensa-esp32-elf-size)
set(NM xtensa-esp32-elf-nm)


### ESP-IDF setup according to their documentation

# Include for ESP-IDF build system functions
include($ENV{IDF_PATH}/tools/cmake/idf.cmake)
# Create idf::esp32 and idf::freertos static libraries
idf_build_process(esp32
                # try and trim the build; additional components
                # will be included as needed based on dependency tree
                #
                # although esptool_py does not generate static library,
                # processing the component is needed for flashing related
                # targets and file generation
                COMPONENTS esp32 freertos esptool_py
                SDKCONFIG ${CMAKE_CURRENT_LIST_DIR}/sdkconfig
                SDKCONFIG_DEFAULTS ${CMAKE_CURRENT_LIST_DIR}/sdkconfig_defaults
                BUILD_DIR ${CMAKE_BINARY_DIR})


# Include relevant directories for header files                
include_directories(
  ${PROJECT_ROOT_DIR}
  $ENV{IDF_PATH}/components
)

set(OPT_FLAGS "-g3 -O0")

# Unused but sometimes useful flags
# -Wundef
# -Wpadded

set(LANG_INDEPENDENT_FLAGS "\
  -Werror \
  -Wall \
  -Wextra \
  -Wshadow \
  -Wdouble-promotion \
  -Wformat=2 \
  -Wformat-truncation \
  -Wconversion \
  -Wno-unused-parameter \
  -ffunction-sections \
  -fdata-sections \
  -fno-common \
  -fno-builtin \
")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OPT_FLAGS} ${LANG_INDEPENDENT_FLAGS} -std=gnu99")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OPT_FLAGS} ${LANG_INDEPENDENT_FLAGS} -std=gnu++11 -fno-rtti")
set(CMAKE_C_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} -Wl,--gc-sections")
set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -Wl,-Map=esp32.map,--gc-sections,--demangle")

# Add any source files that will be compiled into final binary
set(USER_SRCS ${PROJECT_ROOT_DIR}/src/main.cpp)
set(USER_SRCS ${USER_SRCS} ${LIB_RTOS_DIR}/rtos.cpp)
set(USER_SRCS ${USER_SRCS} ${LIB_RTOS_DIR}/hal.cpp)

add_executable(${OUTPUT_FILE} ${USER_SRCS})

# Link the static libraries to the executable
target_link_libraries(${OUTPUT_FILE} idf::esp32 idf::freertos idf::spi_flash)

# Attach additional targets to the executable file for flashing,
# linker script generation, partition_table generation, etc.
idf_build_executable(${OUTPUT_FILE})

# Extra commands that are run after the binary is built to show the binary size
# and generate function mapping by both size and location in memory
add_custom_command(TARGET ${OUTPUT_FILE} POST_BUILD
  COMMAND ${SIZE} --format=berkeley ${OUTPUT_DIR}/${OUTPUT_FILE}
  COMMAND ${NM} --print-size --size-sort ${OUTPUT_DIR}/${OUTPUT_FILE} > functions_by_size.txt
  COMMAND ${NM} --print-size --numeric-sort ${OUTPUT_DIR}/${OUTPUT_FILE} > functions_by_addr.txt
)
