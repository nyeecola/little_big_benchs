#include <stdio.h>
#include <vector>

#include "util.h"
#include "test_util.h"
#include "test_cases.cpp"

#define __TEST_IMPLEMENTATION__
#include "test_util.h"

typedef bool (*TestFuncPtr)();

struct TestCase {
    const char *name;
    TestFuncPtr func;
};

TestCase test_cases[] = {
    #include "test_cases.cpp"
};

#define PASS "\x1b[32mpass\x1b[0m"
#define FAIL "\x1b[31mfail\x1b[0m"

int main(int argc, char **argv) {
    fprintf(stderr, "\n" PRINT_BORDER "\n");
    fprintf(stderr, "Running tests...\n");

    int num_tests = sizeof(test_cases)/sizeof(*test_cases);
    int num_passes = 0, num_fails = 0;

    for (int i = 0; i < num_tests; i++) {
        bool result = test_cases[i].func();
        num_passes += result;
        num_fails += !result;

        fprintf(stderr, "Test #%d (" CYAN("%s") "): %s\n", i+1, test_cases[i].name, result ? PASS : FAIL);
    }
    fprintf(stderr, PRINT_BORDER "\n");
    fprintf(stderr, "Finished: %d " GREEN("passed") " %d " RED("failed") "\n", num_passes, num_fails);
    fprintf(stderr, PRINT_BORDER "\n\n");

    return 0;
}

