# pocket-tank firmware — Waveshare ESP32-P4-WIFI6-Touch-LCD-4B (P4-only; the
# 4-inch 720x720 ST7703 panel, target esp32p4)
cmake_minimum_required(VERSION 3.16)
include($ENV{IDF_PATH}/tools/cmake/project.cmake)

set(SDKCONFIG_DEFAULTS "${CMAKE_CURRENT_LIST_DIR}/sdkconfig.defaults")

project(pocket_tank)
