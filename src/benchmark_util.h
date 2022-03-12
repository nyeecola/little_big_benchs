#ifndef __TEST_IMPLEMENTATION__
// benchmark declaration (first pass)

// Used to trick the compiler into not moving the given pointer
static void ESCAPE (void *p) {
    asm volatile("" : : "g"(p) : "memory");
}

// Used to fake read/write memory
static void CLOBBER () {
    asm volatile("" : : : "memory");
}

#undef BENCHMARK
#define BENCHMARK(name, escaped_parameters, ...) \
void benchmark_ ## name (int input) { \
    __VA_ARGS__ \
}

#else
// benchmark setup (second pass)

#define PARAMETERS(...) {__VA_ARGS__}
#undef BENCHMARK
#define BENCHMARK(name, parameters, ...) \
    { #name, parameters, benchmark_ ## name },

#endif
