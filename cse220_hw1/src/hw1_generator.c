#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "hw1.h"

int main(int argc, char **argv)
{
    assert(argc == 4);
    char *initial_state;
    
    printf("Initial state: %s\n", argv[3]);
    initial_state = generate_medium(argv[3], (int)strtoul(argv[1], NULL, 10), (int)strtoul(argv[2], NULL, 10));
    printf("Result: %s\n", initial_state);
    return 0;
}
