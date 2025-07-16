#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "gtest/gtest.h"
#include "tests_utils.h"

extern "C" {
#include "hw1.h"
}

class generator_tests_asan : public testing::Test { 
    void SetUp() override {
        
    }
};

TEST_F(generator_tests_asan, asan_board20x20) {
    expect_no_asan_errors(run_using_asan("asan_board_gen20x20"));
}

TEST_F(generator_tests_asan, asan_board5x5) {
    expect_no_asan_errors(run_using_asan("asan_board_gen5x5"));
}

TEST_F(generator_tests_asan, asan_board13x8) {
    expect_no_asan_errors(run_using_asan("asan_board_gen13x8"));
}