# Emulator build configuration
find_package(Qt5 COMPONENTS Core Gui Widgets Multimedia REQUIRED)
find_package(SDL2 REQUIRED)

# Audio library
find_package(PortAudio QUIET)
if(NOT PortAudio_FOUND)
  message(WARNING "PortAudio not found, using SDL2 for audio")
endif()

# Source files
set(EMULATOR_SOURCES
  src/main.cpp
  src/synth_emulator.cpp
  src/midi_input.cpp
  src/audio_output.cpp
  src/ui_window.cpp
)

set(EMULATOR_HEADERS
  src/synth_emulator.h
  src/midi_input.h
  src/audio_output.h
  src/ui_window.h
)

# Qt5 MOC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Executable
add_executable(mwave_emulator ${EMULATOR_SOURCES} ${EMULATOR_HEADERS})

# Link libraries
target_link_libraries(mwave_emulator
  Qt5::Core
  Qt5::Gui
  Qt5::Widgets
  Qt5::Multimedia
  SDL2::SDL2
)

# Include directories
target_include_directories(mwave_emulator PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  ${CMAKE_SOURCE_DIR}/firmware/include
)

# Installation
install(TARGETS mwave_emulator DESTINATION bin)
