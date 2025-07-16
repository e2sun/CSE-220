cmake_minimum_required(VERSION 3.10)
project(hw0_main LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)
include_directories(include)
add_executable(${PROJECT_NAME} src/hw0_main.c)
target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Wextra -Wshadow -Wpedantic -Wdouble-promotion -Wformat=2 -Wundef -Werror)
target_link_libraries(${PROJECT_NAME} PUBLIC m)
