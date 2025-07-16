#include <string.h>
#include "hw1.h"

//extern char board[MAX_ROWS][MAX_COLS];

int main() {
    const int rows = 20;
    const int cols = 20;
    const char *final_board = "oxoxxxoxxoxoooxooxxxxoooxoooxoxoooxxxoxoxoxxoxxooxoxoxxoooxxxxoxxxoxxxoxxxoooxoxoxoooxxoooxoooxxoxooooxxxooxoxooxoxoxooxooxooxoxoxoxooxoxxxoxoxxxooxxxooxxooxxoxoxooxoxoooxxoxxxooxoxooxxooxxxoxoxooxooooxxxoxxooxxxoooxoxxoxooxxxooxoooxxoxoxoxooxoooxoooxxoxxxoxxoxoxoxxoxxxooxoooxoxooxxooxoxoxxoxoxxoxxxxooxoxxxoooxxxooxxoxxoxxooxoxoxooxxoooxoxxxoxoxoxoxoxxooxoxooxxoxxoooxoxoooxooxxoxooxxoxoxooxxoxoxox";
    generate_medium(final_board, rows, cols);
}
