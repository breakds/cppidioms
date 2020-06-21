cmake_minimum_required(VERSION 3.10)

project(cppidioms_x11 VERSION 0.1.0)

# C++ Language specific properties

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${PROJECT_SOURCE_DIR})
add_compile_options(-Wall -Werror)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SPDLOG REQUIRED spdlog)

add_executable(simple_window simple_window.cc)
target_link_libraries(
  simple_window
  ${SPDLOG_LIBRARIES}
  X11)
