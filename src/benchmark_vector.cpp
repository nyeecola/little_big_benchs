BENCHMARK(add_elements_to_vector, PARAMETERS(1000, 100000),
    std::vector<int> v;
    ESCAPE(v.data());
    for (int i = 0; i < input; i++) {
        v.push_back(5);
        CLOBBER();
    }
)

BENCHMARK(create_small_vectors, PARAMETERS(1000, 100000),
    for (int i = 0; i < input; i++) {
        std::vector<int> v = { 1, 2, 3, 5, 8, 13 };
        ESCAPE(v.data());
        CLOBBER();
    }
)
