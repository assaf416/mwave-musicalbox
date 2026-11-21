# Firmware build configuration for MWAVE devices
# STM32H7 series ARM Cortex-M4

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

# Compiler settings
set(COMPILER_PREFIX arm-none-eabi)
set(CMAKE_C_COMPILER ${COMPILER_PREFIX}-gcc)
set(CMAKE_CXX_COMPILER ${COMPILER_PREFIX}-g++)
set(CMAKE_ASM_COMPILER ${COMPILER_PREFIX}-gcc)

# Firmware source files
set(FIRMWARE_SOURCES
  src/main.c
  src/audio_engine.c
  src/midi_parser.c
  src/instruments/piano.c
  src/instruments/epiano.c
  src/instruments/organ.c
  src/instruments/melotron.c
  src/instruments/synth.c
  src/effects/reverb.c
  src/effects/chorus.c
  src/effects/phaser.c
  src/ui/display_driver.c
  src/ui/touchscreen.c
  src/hardware/dac.c
  src/hardware/adc.c
  src/hardware/uart.c
)

set(FIRMWARE_HEADERS
  include/audio_engine.h
  include/midi_parser.h
  include/instruments.h
  include/effects.h
)

# Compiler flags
set(CPU_FLAGS "-mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CPU_FLAGS} -Wall -Wextra -g3 -O2 -ffunction-sections -fdata-sections")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CPU_FLAGS} -Wall -Wextra -g3 -O2 -ffunction-sections -fdata-sections")

# Linker script
set(LINKER_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/linker_script.ld")

# Executable
add_executable(mwave_firmware.elf ${FIRMWARE_SOURCES})

# Link options
set(LINKER_FLAGS "-Wl,--gc-sections -Wl,-Map=mwave_firmware.map -T${LINKER_SCRIPT}")
set_target_properties(mwave_firmware.elf PROPERTIES LINK_FLAGS "${LINKER_FLAGS}")

# Include directories
target_include_directories(mwave_firmware.elf PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/libs/CMSIS/include
  ${CMAKE_CURRENT_SOURCE_DIR}/libs/STM32H7xx_HAL_Driver/Inc
)

# Binary output
add_custom_command(TARGET mwave_firmware.elf POST_BUILD
  COMMAND ${COMPILER_PREFIX}-objcopy -O binary mwave_firmware.elf mwave_firmware.bin
  COMMAND ${COMPILER_PREFIX}-size mwave_firmware.elf
)

# Flash target
add_custom_target(flash
  COMMAND st-flash write mwave_firmware.bin 0x08000000
  DEPENDS mwave_firmware.elf
)

message(STATUS "Firmware target: mwave_firmware.elf")
message(STATUS "Binary output: mwave_firmware.bin")
