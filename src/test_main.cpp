#include <stdio.h>
#include <vector>

#include "test_util.cpp"
#include "test_cases.cpp"

#define __TEST_IMPLEMENTATION__
#include "test_util.cpp"

typedef bool (*test_func_ptr_t)();

struct test_case_t {
    const char *name;
    test_func_ptr_t func;
};

test_case_t test_func_ptrs[] = {
    #include "test_cases.cpp"
};

#define PASS "\x1b[32mpass\x1b[0m"
#define FAIL "\x1b[31mfail\x1b[0m"

int main(int argc, char **argv) {
    fprintf(stderr, "\n================================================\n");
    fprintf(stderr, "Running tests...\n");

    int num_tests = sizeof(test_func_ptrs)/sizeof(*test_func_ptrs);
    int num_passes = 0, num_fails = 0;

    for (int i = 0; i < num_tests; i++) {
        bool result = test_func_ptrs[i].func();
        num_passes += result;
        num_fails += !result;

        fprintf(stderr, "Test #%d (\x1b[36m%s\x1b[0m): %s\n", i+1, test_func_ptrs[i].name, result ? PASS : FAIL);
    }
    fprintf(stderr, "================================================\n");
    fprintf(stderr, "Finished: %d \x1b[32mpassed\x1b[0m, %d \x1b[31mfailed\x1b[0m\n", num_passes, num_fails);
    fprintf(stderr, "================================================\n");

    return 0;
}

