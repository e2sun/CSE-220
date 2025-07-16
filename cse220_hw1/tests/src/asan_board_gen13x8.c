#include <string.h>
#include "hw1.h"

//extern char board[MAX_ROWS][MAX_COLS];

int main() {
    const int rows = 8;
    const int cols = 13;
    const char *final_board = "xoooxxooxoooxooxoooxxooxxxxxoxxoooxxooxooxxooxooxoooxooxxxoxxooxxxoxoooxoxxxoooxooxxxoxooxooxxxoxoooxxox";
    generate_medium(final_board, rows, cols);
}
