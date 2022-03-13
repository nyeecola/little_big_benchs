#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <vector>

#include "vector.h"
#include "util.h"
#include "benchmark_util.h"
#include "benchmark_cases.cpp"

#define __TEST_IMPLEMENTATION__
#include "benchmark_util.h"

typedef void (*BenchmarkFuncPtr)(int);

#define MAX_INVOCATIONS 10
struct BenchmarkCase {
    const char *name;
    int parameters[MAX_INVOCATIONS];
    BenchmarkFuncPtr func;
};

/* Note: This MUST be sorted in descending order of magnitude */
typedef enum {
    SECOND,
    MILLISECOND,
    MICROSECOND,
    NANOSECOND,

    MAX_TIME_UNITS
} TimeUnit;

struct BenchmarkResult {
    double time;
    TimeUnit unit;
};

BenchmarkCase benchmark_cases[] = {
    #include "benchmark_cases.cpp"
};

const char* time_unit_names[MAX_TIME_UNITS] = {
    "s",
    "ms",
    "us",
    "ns",
};

BenchmarkResult get_readable_benchmark_time(clock_t clocks) {
    BenchmarkResult res = { clocks / (double) CLOCKS_PER_SEC, SECOND };
#if 0
    for (int i = 0; i < MAX_TIME_UNITS; i++) {
        if (res.time < 0.001) {
            res.time *= 1000;
            res.unit = static_cast<TimeUnit>(((int)res.unit) + 1);
            assert(res.unit >= 0 && res.unit < MAX_TIME_UNITS);
        }
    }
#else
    res.time *= 1000 * 1000;
    res.unit = MICROSECOND;
#endif
    return res;
}

#define NUM_BENCHMARK_REPLAYS 4000
int main(int argc, char **argv) {
    fprintf(stderr, "\n" PRINT_BORDER "\n");
    fprintf(stderr, "Running benchmarks...\n");

    int num_tests = sizeof(benchmark_cases)/sizeof(*benchmark_cases);
    int num_passes = 0, num_fails = 0;

    int num_test_variants = 0;
    for (int i = 0; i < num_tests; i++) {
        for (int j = 0; benchmark_cases[i].parameters[j] > 0; j++) {
            ++num_test_variants;

            char formatted_str[256] = {0};
            snprintf(formatted_str, 256, "Test #%d (" CYAN("%s") ", " CYAN("%d")  "): ", num_test_variants,
                     benchmark_cases[i].name, benchmark_cases[i].parameters[j]);
            fprintf(stderr, "%-70s", formatted_str);
            fflush(stderr);

            clock_t total_time = 0;
            for (int k = 0; k < NUM_BENCHMARK_REPLAYS; k++) {
                clock_t begin = clock();
                benchmark_cases[i].func(benchmark_cases[i].parameters[j]);
                clock_t end = clock();
                total_time += end - begin;
            }
            BenchmarkResult dt = get_readable_benchmark_time(total_time / NUM_BENCHMARK_REPLAYS);

            fprintf(stderr, YELLOW("%10.0lf") " %s\n", dt.time, time_unit_names[dt.unit]);
        }
    }
    fprintf(stderr, PRINT_BORDER "\n\n");


    return 0;
}

