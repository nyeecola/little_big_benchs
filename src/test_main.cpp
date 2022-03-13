#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <vector>

#include "vector.h"
#include "util.h"

struct TestCaseResult {
    bool passed;
    const char *error_str;
};

typedef TestCaseResult (*TestFuncPtr)();

struct TestCase {
    const char *name;
    TestFuncPtr func;
};

#include "test_util.h"
#include "test_cases.cpp"

#define __TEST_IMPLEMENTATION__
#include "test_util.h"

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
        TestCaseResult result = test_cases[i].func();
        num_passes += result.passed;
        num_fails += !result.passed;

        fprintf(stderr, "Test #%d (" CYAN("%s") "): %s\n", i+1, test_cases[i].name, result.passed ? PASS : FAIL);
        if (!result.passed) {
            fprintf(stderr, "\t-> %s\n", result.error_str);
        }
    }
    fprintf(stderr, PRINT_BORDER "\n");
    fprintf(stderr, "Finished: %d " GREEN("passed") " %d " RED("failed") "\n", num_passes, num_fails);
    fprintf(stderr, PRINT_BORDER "\n\n");

    return num_fails ? -1 : 0;
}

