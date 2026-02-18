cmake_minimum_required(VERSION 4.2.0)
project(WallpaperCarouselPicker VERSION 1.0.0 LANGUAGES C CXX)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenCV CONFIG REQUIRED)

add_executable(WallpaperPicker
  ${CMAKE_SOURCE_DIR}/src/main.cpp
  ${CMAKE_SOURCE_DIR}/src/wpicker.cpp
)

target_compile_options(WallpaperPicker PRIVATE -Wall -Wextra -Werror -Wpedantic)
target_include_directories(WallpaperPicker PRIVATE "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(WallpaperPicker PRIVATE ${OpenCV_LIBS})
