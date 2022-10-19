cmake_minimum_required(VERSION 3.4)
project(CharacterRecognition)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)

set(PROJECT_HEADERS
  src/olcPixelGameEngine.h
  src/data.h
  src/CR.h
  src/calc.h
)

set(PROJECT_SOURCES
  src/main.cpp
  src/data.cpp
  src/CR.cpp
  src/calc.cpp
)

add_executable(CharacterRecognition ${PROJECT_HEADERS} ${PROJECT_SOURCES})

set(LIBRARIES X11 GL pthread png freetype)
target_link_libraries(CharacterRecognition ${LIBRARIES})

set(CMAKE_CXX_FLAGS "-I/usr/include/freetype2")

add_custom_target(Run COMMAND CharacterRecognition COMMENT "Running the program" VERBATIM)
