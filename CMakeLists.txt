cmake_minimum_required(VERSION 3.4)
project(ImageRecognition)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)

set(PROJECT_HEADERS
  src/olcPixelGameEngine.h
  src/data.h
)

set(PROJECT_SOURCES
  src/main.cpp
  src/data.cpp
)

add_executable(ImageRecognition ${PROJECT_HEADERS} ${PROJECT_SOURCES})

set(LIBRARIES X11 GL pthread png freetype)
target_link_libraries(ImageRecognition ${LIBRARIES})

set(CMAKE_CXX_FLAGS "-I/usr/include/freetype2")

add_custom_target(Run COMMAND ImageRecognition COMMENT "Running the program" VERBATIM)
