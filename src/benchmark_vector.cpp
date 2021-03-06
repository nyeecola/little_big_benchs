#ifndef __TEST_IMPLEMENTATION__
DECLARE_VEC(int);
struct ABC {
    float x, y, z;
    const char *name;
    int history[20];
};
DECLARE_VEC(ABC);
#endif

// C++ vector

BENCHMARK(cpp_add_elements_to_vector, PARAMETERS(1000, 100000),
    std::vector<int> v;
    ESCAPE(v.data());
    for (int i = 0; i < input; i++) {
        v.push_back(5);
        CLOBBER();
    }
)

BENCHMARK(cpp_create_small_vectors, PARAMETERS(1000, 100000),
    for (int i = 0; i < input; i++) {
        std::vector<int> v = { 1, 2, 3, 5, 8, 13 };
        ESCAPE(v.data());
        CLOBBER();
    }
)

BENCHMARK(cpp_create_large_vectors, PARAMETERS(80, 8000),
    for (int i = 0; i < input; i++) {
        std::vector<ABC> v = { { 1, 2, 3 }, { 1, 2, 3 }, { 1, 2, 3 }, { 1, 2, 3 }, { 1, 2, 3 }, { 1, 2, 3 }, { 1, 2, 3 }, { 1, 2, 3 }, { 1, 2, 3 }, { 1, 2, 3 } };
        ESCAPE(v.data());
        CLOBBER();
    }
)

// Custom vector implementation

BENCHMARK(custom_add_elements_to_vector, PARAMETERS(1000, 100000),
    VEC_INIT(v, int);
    ESCAPE(v.data);
    for (int i = 0; i < input; i++) {
        VEC_APPEND(v, 5);
        CLOBBER();
    }
    VEC_DESTROY(v);
)

BENCHMARK(custom_create_small_vectors, PARAMETERS(1000, 100000),
    for (int i = 0; i < input; i++) {
        VEC_INIT_N(v, 6, int, 1, 2, 3, 5, 8, 13);
        ESCAPE(v.data);
        CLOBBER();
        VEC_DESTROY(v);
    }
)

BENCHMARK(custom_create_large_vectors, PARAMETERS(80, 8000),
    for (int i = 0; i < input; i++) {
        VEC_INIT_N(v, 10, ABC, { 1, 2, 3 }, { 1, 2, 3 }, { 1, 2, 3 }, { 1, 2, 3 }, { 1, 2, 3 }, { 1, 2, 3 }, { 1, 2, 3 }, { 1, 2, 3 }, { 1, 2, 3 }, { 1, 2, 3 });
        ESCAPE(v.data);
        CLOBBER();
        VEC_DESTROY(v);
    }
)
