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
  src/wav_sample_loader.cpp
  src/sample_based_synth.cpp
)

set(EMULATOR_HEADERS
  src/synth_emulator.h
  src/midi_input.h
  src/audio_output.h
  src/console_ui.h
  src/soundfont_loader.h
  src/melotron_synth.h
  src/wav_sample_loader.h
  src/sample_based_synth.h
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

# Testing
enable_testing()

# Check if GoogleTest is available
find_package(GTest QUIET)

if(GTEST_FOUND)
  # Create library for testable components
  add_library(mwave_core STATIC
    src/soundfont_loader.cpp
    src/melotron_synth.cpp
    src/audio_output.cpp
    src/wav_sample_loader.cpp
    src/sample_based_synth.cpp
  )

  target_compile_features(mwave_core PRIVATE cxx_std_17)
  target_include_directories(mwave_core PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/firmware/include
  )

  # Test executables
  add_executable(test_sf2_extraction tests/test_sf2_extraction.cpp)
  target_link_libraries(test_sf2_extraction mwave_core GTest::GTest GTest::Main)
  target_compile_features(test_sf2_extraction PRIVATE cxx_std_17)
  target_include_directories(test_sf2_extraction PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/firmware/include
  )

  add_executable(test_pitch_shifting tests/test_pitch_shifting.cpp)
  target_link_libraries(test_pitch_shifting mwave_core GTest::GTest GTest::Main)
  target_compile_features(test_pitch_shifting PRIVATE cxx_std_17)
  target_include_directories(test_pitch_shifting PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/firmware/include
  )

  add_executable(test_loop_handling tests/test_loop_handling.cpp)
  target_link_libraries(test_loop_handling mwave_core GTest::GTest GTest::Main)
  target_compile_features(test_loop_handling PRIVATE cxx_std_17)
  target_include_directories(test_loop_handling PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/firmware/include
  )

  add_executable(test_wav_samples tests/test_wav_samples.cpp)
  target_link_libraries(test_wav_samples mwave_core GTest::GTest GTest::Main)
  target_compile_features(test_wav_samples PRIVATE cxx_std_17)
  target_include_directories(test_wav_samples PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/firmware/include
  )

  add_test(NAME SF2Extraction COMMAND test_sf2_extraction)
  add_test(NAME PitchShifting COMMAND test_pitch_shifting)
  add_test(NAME LoopHandling COMMAND test_loop_handling)
  add_test(NAME WavSamples COMMAND test_wav_samples)

  message(STATUS "GoogleTest found - tests enabled")
else()
  message(STATUS "GoogleTest not found - tests disabled (install libgtest-dev to enable)")
endif()
