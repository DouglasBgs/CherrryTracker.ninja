cmake_minimum_required(VERSION 3.23)
project(CherrryTracker_ninja)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(esp32)
include_directories(esp32cam)
include_directories(esp32cam/v2)

add_executable(CherrryTracker_ninja
        esp32/esp32.ino
        esp32cam/v2/camera_pins.h
        esp32cam/v2/v2.ino
        esp32cam/esp32cam.ino)
