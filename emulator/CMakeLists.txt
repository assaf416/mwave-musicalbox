# Emulator build configuration - Console-based (no Qt5 dependency)

# Source files
set(EMULATOR_SOURCES
  src/main.cpp
  src/synth_emulator.cpp
  src/midi_input.cpp
  src/audio_output.cpp
  src/console_ui.cpp
  src/soundfont_loader.cpp
  src/melotron_synth.cpp
)

set(EMULATOR_HEADERS
  src/synth_emulator.h
  src/midi_input.h
  src/audio_output.h
  src/console_ui.h
  src/soundfont_loader.h
  src/melotron_synth.h
)

# Executable
add_executable(mwave_emulator ${EMULATOR_SOURCES} ${EMULATOR_HEADERS})

# C++17 standard
target_compile_features(mwave_emulator PRIVATE cxx_std_17)

# Include directories
target_include_directories(mwave_emulator PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  ${CMAKE_SOURCE_DIR}/firmware/include
)

# Optional: Try to link with PortAudio if available
find_library(PORTAUDIO_LIB portaudio QUIET)
if(PORTAUDIO_LIB)
  target_link_libraries(mwave_emulator ${PORTAUDIO_LIB})
  target_compile_definitions(mwave_emulator PRIVATE HAVE_PORTAUDIO)
  message(STATUS "PortAudio found: ${PORTAUDIO_LIB}")
else()
  message(STATUS "PortAudio not found - emulator will run in demo mode")
endif()

# Installation
install(TARGETS mwave_emulator DESTINATION bin)
