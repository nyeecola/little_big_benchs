#ifndef __TEST_IMPLEMENTATION__
// test declaration (first pass)

#define STRINGIFY2(a) #a
#define STRINGIFY(a) STRINGIFY2(a)
#define LINE_AS_STR STRINGIFY(__LINE__)

#define EXPECT_EQ(a, b) if (!(a == b)) return { false, __FILE__ ":" LINE_AS_STR ": EXPECT_EQ(" #a", " #b") failed" };
#define EXPECT_LT(a, b) if (!(a < b)) return { false, __FILE__ ":" LINE_AS_STR ": EXPECT_LT(" #a", " #b") failed" };
#define EXPECT_GT(a, b) if (!(a > b)) return { false, __FILE__ ":" LINE_AS_STR ": EXPECT_GT(" #a", " #b") failed" };

#undef TEST_CASE
#define TEST_CASE(test_name, ...) \
TestCaseResult test_ ## test_name () { \
    __VA_ARGS__ \
    return { true, "" }; \
}

#else
// test setup (second pass)

#undef TEST_CASE
#define TEST_CASE(test_name, ...) \
    { #test_name, test_ ## test_name },

#endif
