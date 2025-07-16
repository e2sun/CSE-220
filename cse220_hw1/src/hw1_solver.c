#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "hw1.h"

int main(int argc, char **argv)
{
    assert(argc == 4);
    int num_x, num_o;
    
    printf("Initial state: %s\n", argv[3]);
    int result = solve(argv[3], (int)strtoul(argv[1], NULL, 10), (int)strtoul(argv[2], NULL, 10), &num_x, &num_o);
    printf("Result: %d\n", result);
    return 0;
}
