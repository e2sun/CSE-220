#include "tests_utils.h"

void expect_no_asan_errors(int status) {
    EXPECT_EQ(0, WEXITSTATUS(status));
}

int run_using_asan(const char *test_name) {
	    char executable[100];
    (void)sprintf(executable, "./build/%s", test_name);
    assert(access(executable, F_OK) == 0);
    char cmd[500];
    (void)sprintf(cmd, "%s", executable);
	return system(cmd);
}

void assert_arrays_equal(char exp_array[MAX_ROWS][MAX_COLS], char act_array[MAX_ROWS][MAX_COLS]) {
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
			if (exp_array[i][j] != act_array[i][j])
				ERROR("Mismatch at row %d, col %d: expected %c, got %c", i, j, exp_array[i][j], act_array[i][j]);
            ASSERT_EQ(exp_array[i][j], act_array[i][j]);
        }
    }
}
