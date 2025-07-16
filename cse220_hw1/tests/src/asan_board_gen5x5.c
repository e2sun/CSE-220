#include <string.h>
#include "hw1.h"

int main() {
    const int rows = 5;
    const int cols = 5;
    const char *final_board = "oxoooxooxooxxxoxooxxoxoox";
    generate_medium(final_board, rows, cols);
}
