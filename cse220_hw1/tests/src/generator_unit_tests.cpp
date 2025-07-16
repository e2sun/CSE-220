#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "gtest/gtest.h"
#include "tests_utils.h"

extern "C" {
#include "hw1.h"
}


class generator_tests : public testing::Test { 
    void SetUp() override {
        
    }
};

// Small square board
TEST_F(generator_tests, board4x4) {
    const int rows = 4;
    const int cols = 4;
    int act_num_x = -1, act_num_o = -1;
    const char *final_board = "xooxooxoxxxoooxx";
    char *initial_state = NULL;
    initial_state = generate_medium(final_board, rows, cols);
    if (!initial_state)
        FAIL();
    int act_result = solve(initial_state, rows, cols, &act_num_x, &act_num_o);
    EXPECT_EQ(1, act_result);
    int needed_val;
    char temp_store;
    for(int chars = 0; chars < rows*cols; chars++)
    {
        if(initial_state[chars] != '-')
        {
            temp_store = initial_state[chars];
            initial_state[chars] = '-';
            needed_val = solve(initial_state, rows, cols, &act_num_x, &act_num_o);
            EXPECT_EQ(0, needed_val);
            initial_state[chars] = temp_store;
        }
    }
}

//S-Med square board
TEST_F(generator_tests, board8x8) {
    const int rows = 8;
    const int cols = 8;
    int act_num_x = -1, act_num_o = -1;
    const char *final_board = "oxoxoxxoooxxxoxxxoooxoxoooxxxoooxxoxoxxxxoxooxooooxoxxoxxoxoxoxx";
    char *initial_state = NULL;
    initial_state = generate_medium(final_board, rows, cols);
    if (!initial_state)
        FAIL();
    int act_result = solve(initial_state, rows, cols, &act_num_x, &act_num_o);
    EXPECT_EQ(1, act_result);
    int needed_val;
    char temp_store;
    for(int chars = 0; chars < rows*cols; chars++)
    {
        if(initial_state[chars] != '-')
        {
            temp_store = initial_state[chars];
            initial_state[chars] = '-';
            needed_val = solve(initial_state, rows, cols, &act_num_x, &act_num_o);
            EXPECT_EQ(0, needed_val);
            initial_state[chars] = temp_store;
        }
    }
}

// Med square board
TEST_F(generator_tests, board12x12) {
    const int rows = 12;
    const int cols = 12;
    int act_num_x = -1, act_num_o = -1;
    const char *final_board = "xooxxxoooxxoxoxxooxooxxxxxooxxoxxooooxoxoxoooxxoxxoxoxooxooxooxoooxxooxoxoooxxooxxxoxxxooxxxooxoxooxxxooxxoxoxoxooxxoooxoxooxoooxxxoxxxoxxooxooo";
    char *initial_state = NULL;
    initial_state = generate_medium(final_board, rows, cols);
    if (!initial_state)
        FAIL();
    int act_result = solve(initial_state, rows, cols, &act_num_x, &act_num_o);
    EXPECT_EQ(1, act_result);
    int needed_val;
    char temp_store;
    for(int chars = 0; chars < rows*cols; chars++)
    {
        if(initial_state[chars] != '-')
        {
            temp_store = initial_state[chars];
            initial_state[chars] = '-';
            needed_val = solve(initial_state, rows, cols, &act_num_x, &act_num_o);
            EXPECT_EQ(0, needed_val);
            initial_state[chars] = temp_store;
        }
    }
}

// Large square board
TEST_F(generator_tests, board20x20) {
    const int rows = 20;
    const int cols = 20;
    int act_num_x = -1, act_num_o = -1;
    const char *final_board = "oxoxxxoxxoxoooxooxxxxoooxoooxoxoooxxxoxoxoxxoxxooxoxoxxoooxxxxoxxxoxxxoxxxoooxoxoxoooxxoooxoooxxoxooooxxxooxoxooxoxoxooxooxooxoxoxoxooxoxxxoxoxxxooxxxooxxooxxoxoxooxoxoooxxoxxxooxoxooxxooxxxoxoxooxooooxxxoxxooxxxoooxoxxoxooxxxooxoooxxoxoxoxooxoooxoooxxoxxxoxxoxoxoxxoxxxooxoooxoxooxxooxoxoxxoxoxxoxxxxooxoxxxoooxxxooxxoxxoxxooxoxoxooxxoooxoxxxoxoxoxoxoxxooxoxooxxoxxoooxoxoooxooxxoxooxxoxoxooxxoxoxox";
    char *initial_state = NULL;
    initial_state = generate_medium(final_board, rows, cols);
    if (!initial_state)
        FAIL();
    int act_result = solve(initial_state, rows, cols, &act_num_x, &act_num_o);
    EXPECT_EQ(1, act_result);
    int needed_val;
    char temp_store;
    for(int chars = 0; chars < rows*cols; chars++)
    {
        if(initial_state[chars] != '-')
        {
            temp_store = initial_state[chars];
            initial_state[chars] = '-';
            needed_val = solve(initial_state, rows, cols, &act_num_x, &act_num_o);
            EXPECT_EQ(0, needed_val);
            initial_state[chars] = temp_store;
        }
    }
}

// Non-square board
TEST_F(generator_tests, board6x5) {
    const int rows = 6;
    const int cols = 5;
    int act_num_x = -1, act_num_o = -1;
    const char *final_board = "ooxoxxoxxoxxxooxooxooxxoxxxxoo";
    char *initial_state = NULL;
    initial_state = generate_medium(final_board, rows, cols);
    if (!initial_state)
        FAIL();
    int act_result = solve(initial_state, rows, cols, &act_num_x, &act_num_o);
    EXPECT_EQ(1, act_result);
    int needed_val;
    char temp_store;
    for(int chars = 0; chars < rows*cols; chars++)
    {
        if(initial_state[chars] != '-')
        {
            temp_store = initial_state[chars];
            initial_state[chars] = '-';
            needed_val = solve(initial_state, rows, cols, &act_num_x, &act_num_o);
            EXPECT_EQ(0, needed_val);
            initial_state[chars] = temp_store;
        }
    }
}

// Wide board
TEST_F(generator_tests, board8x14) {
    const int rows = 8;
    const int cols = 14;
    int act_num_x = -1, act_num_o = -1;
    const char *final_board = "xxooxoxoxoxoooxoooxxxoooxoxxoxxxoxxxoxxxoxxxoooxooxooxxxoooxxoxoxoxoxoxxxooxxxoooxooooxxxooxoxoxxxxoxoooxoxxxoxo";
    char *initial_state = NULL;
    initial_state = generate_medium(final_board, rows, cols);
    if (!initial_state)
        FAIL();
    int act_result = solve(initial_state, rows, cols, &act_num_x, &act_num_o);
    EXPECT_EQ(1, act_result);
    int needed_val;
    char temp_store;
    for(int chars = 0; chars < rows*cols; chars++)
    {
        if(initial_state[chars] != '-')
        {
            temp_store = initial_state[chars];
            initial_state[chars] = '-';
            needed_val = solve(initial_state, rows, cols, &act_num_x, &act_num_o);
            EXPECT_EQ(0, needed_val);
            initial_state[chars] = temp_store;
        }
    }
}

// Narrow board
TEST_F(generator_tests, board11x7) {
    const int rows = 11;
    const int cols = 7;
    int act_num_x = -1, act_num_o = -1;
    const char *final_board = "xoxxoxxoxxxoooxoooxxxoooxoooxxoxoxxooxoooxooxxxoxxoxooxooxoxooxoxoxxxooxxooox";
    char *initial_state = NULL;
    initial_state = generate_medium(final_board, rows, cols);
    if (!initial_state)
        FAIL();
    int act_result = solve(initial_state, rows, cols, &act_num_x, &act_num_o);
    EXPECT_EQ(1, act_result);
    int needed_val;
    char temp_store;
    for(int chars = 0; chars < rows*cols; chars++)
    {
        if(initial_state[chars] != '-')
        {
            temp_store = initial_state[chars];
            initial_state[chars] = '-';
            needed_val = solve(initial_state, rows, cols, &act_num_x, &act_num_o);
            EXPECT_EQ(0, needed_val);
            initial_state[chars] = temp_store;
        }
    }
}