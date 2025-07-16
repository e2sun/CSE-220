#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "gtest/gtest.h"
#include "tests_utils.h"

extern "C" {
#include "hw1.h"
}

extern char board[MAX_ROWS][MAX_COLS];

class solver_tests_asan : public testing::Test { 
    void SetUp() override {
        
    }
};

TEST_F(solver_tests_asan, asan_board4x4) {
    expect_no_asan_errors(run_using_asan("asan_board4x4"));
}

TEST_F(solver_tests_asan, asan_board20x20) {
    expect_no_asan_errors(run_using_asan("asan_board20x20"));
}

TEST_F(solver_tests_asan, asan_board12x7) {
    expect_no_asan_errors(run_using_asan("asan_board12x7"));
}