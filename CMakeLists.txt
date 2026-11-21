cmake_minimum_required(VERSION 3.16)
project(mwave_musical_box)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Options
option(BUILD_FIRMWARE "Build device firmware" OFF)
option(BUILD_EMULATOR "Build desktop emulator" ON)
option(BUILD_TESTS "Build test suite" OFF)

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror=format-security -D_FORTIFY_SOURCE=2")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror=format-security -D_FORTIFY_SOURCE=2")

# Include cmake files
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Subdirectories
if(BUILD_FIRMWARE)
  add_subdirectory(firmware)
endif()

if(BUILD_EMULATOR)
  add_subdirectory(emulator)
endif()

if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()

# Print configuration
message(STATUS "MWAVE Musical Box Build Configuration:")
message(STATUS "  Firmware: ${BUILD_FIRMWARE}")
message(STATUS "  Emulator: ${BUILD_EMULATOR}")
message(STATUS "  Tests:    ${BUILD_TESTS}")
