#ifndef __TEST_IMPLEMENTATION__
// test declaration (first pass)

#define EXPECT_EQ(a, b) if (!(a == b)) return false;
#define EXPECT_LT(a, b) if (!(a < b)) return false;
#define EXPECT_GT(a, b) if (!(a > b)) return false;

#undef TEST_CASE
#define TEST_CASE(test_name, test_code) \
bool test_ ## test_name () { \
    test_code \
    return true; \
}

#else

// test setup (second pass)

#undef TEST_CASE
#define TEST_CASE(test_name, test_code) \
    { #test_name, test_ ## test_name },

#endif
