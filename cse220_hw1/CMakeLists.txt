# cmake -S . -B build
# cmake --build build
# setarch `uname -m` -R ./build/solver_unit_tests_asan

cmake_minimum_required(VERSION 3.10)
project(hw1 LANGUAGES C CXX)
option(BUILD_CODEGRADE_TESTS "Build test suites into separate executables" OFF)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)
include_directories(include)

add_executable(hw1_game src/hw1.c src/hw1_game.c)
target_compile_options(hw1_game PUBLIC -Wall -Wextra -Wshadow -Wpedantic -Wdouble-promotion -Wformat=2 -Wundef -Werror)
target_link_libraries(hw1_game PUBLIC m)

if (NOT BUILD_CODEGRADE_TESTS)  
  add_executable(hw1_solver src/hw1.c src/hw1_solver.c)
  target_compile_options(hw1_solver PUBLIC -Wall -Wextra -Wshadow -Wpedantic -Wdouble-promotion -Wformat=2 -Wundef -Werror)
  target_link_libraries(hw1_solver PUBLIC m)

  add_executable(hw1_generator src/hw1.c src/hw1_generator.c)
  target_compile_options(hw1_generator PUBLIC -Wall -Wextra -Wshadow -Wpedantic -Wdouble-promotion -Wformat=2 -Wundef -Werror)
  target_link_libraries(hw1_generator PUBLIC m)
endif()

set(TEST_SUITES "solver_unit_tests" "solver_unit_tests_asan" "generator_unit_tests_asan")
set(HIDDEN_TEST_SUITES "solver_unit_tests" "generator_unit_tests" "generator_hidden_tests")

if (BUILD_CODEGRADE_TESTS)
  foreach(TEST_SUITE IN LISTS TEST_SUITES)
  add_executable(${TEST_SUITE} tests/src/${TEST_SUITE}.cpp tests/src/tests_utils.cpp src/hw1.c)
  target_compile_options(${TEST_SUITE} PUBLIC -g -Wall -Wextra -Wshadow -Wpedantic -Wdouble-promotion -Wformat=2 -Wundef -Werror)
  target_include_directories(${TEST_SUITE} PUBLIC include tests/include)
  target_link_libraries(${TEST_SUITE} PUBLIC gtest gtest_main pthread m)
  endforeach()

  foreach(TEST_SUITE IN LISTS HIDDEN_TEST_SUITES)
  add_executable(hidden_${TEST_SUITE} tests/hidden/src/${TEST_SUITE}.cpp tests/src/tests_utils.cpp src/hw1.c)
  target_compile_options(hidden_${TEST_SUITE} PUBLIC -g -Wall -Wextra -Wshadow -Wpedantic -Wdouble-promotion -Wformat=2 -Wundef -Werror)
  target_include_directories(hidden_${TEST_SUITE} PUBLIC include tests/include)
  target_link_libraries(hidden_${TEST_SUITE} PUBLIC gtest gtest_main pthread m)
  endforeach()  
else()
    # Build a single executable with all the tests. Used during development only, not on CodeGrade.
    add_executable(run_all_tests tests/src/solver_unit_tests.cpp tests/src/generator_unit_tests.cpp tests/src/generator_unit_tests_asan.cpp tests/src/solver_unit_tests_asan.cpp tests/src/tests_utils.cpp src/hw1.c)
    target_compile_options(run_all_tests PUBLIC -g -Wall -Wextra -Wshadow -Wpedantic -Wdouble-promotion -Wformat=2 -Wundef -Werror)
    target_include_directories(run_all_tests PUBLIC include tests/include)
    target_link_libraries(run_all_tests PUBLIC gtest gtest_main pthread m)
endif()

# Build standalone executables to test functions with AddressSanitizer.
file(GLOB SOURCES tests/src/asan_*.c)
message(STATUS "SOURCES: ${SOURCES}")
foreach(FILE IN LISTS SOURCES)
  get_filename_component(MyExeTarget ${FILE} NAME_WE)
  add_executable(${MyExeTarget} ${FILE} src/hw1.c)
  target_compile_options(${MyExeTarget} PUBLIC -g -fsanitize=address -fsanitize=leak -fsanitize=undefined -Wall -Wextra -Wshadow -Wpedantic -Wdouble-promotion -Wformat=2 -Wundef -Werror)
  target_link_options(${MyExeTarget} PUBLIC -fsanitize=address -fsanitize=leak -fsanitize=undefined)
  target_link_libraries(${MyExeTarget} PUBLIC m asan )
  target_include_directories(${MyExeTarget} PUBLIC include tests/include)
endforeach()

# add_executable(run_all_tests tests/src/solver_unit_tests.cpp tests/hidden/src/solver_unit_tests.cpp tests/src/tests_utils.cpp src/hw1.c)
# target_compile_options(run_all_tests PUBLIC -g -g -fsanitize=address -fsanitize=leak -fsanitize=undefined -Wall -Wextra -Wshadow -Wpedantic -Wdouble-promotion -Wformat=2 -Wundef -Werror)
# target_include_directories(run_all_tests PUBLIC include tests/include)
# target_link_options(run_all_tests PUBLIC -fsanitize=address -fsanitize=leak -fsanitize=undefined)
# target_link_libraries(run_all_tests PUBLIC gtest gtest_main pthread m asan)