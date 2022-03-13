#ifndef __TEST_IMPLEMENTATION__
DECLARE_VEC(int);
struct ABC {
    float x, y, z;
    const char *name;
    int history[20];
};
DECLARE_VEC(ABC);
#endif

TEST_CASE(vector_add_elements,
    VEC_INIT(v, int);
    VEC_APPEND(v, 5);
    EXPECT_EQ(VEC_I(v, 0), 5);
    EXPECT_EQ(v.size, 1);
    VEC_DESTROY(v);
)

TEST_CASE(vector_add_elements2,
    VEC_INIT(v, int);
    VEC_APPEND(v, 5);
    VEC_APPEND(v, 25);
    VEC_APPEND(v, 35);
    VEC_APPEND(v, 45);
    EXPECT_EQ(VEC_I(v, 0), 5);
    EXPECT_EQ(VEC_I(v, 1), 25);
    EXPECT_EQ(VEC_I(v, 2), 35);
    EXPECT_EQ(VEC_I(v, 3), 45);
    EXPECT_EQ(v.size, 4);
    VEC_DESTROY(v);
)

TEST_CASE(vector_remove_elements,
    VEC_INIT(v, int);
    VEC_APPEND(v, 5);
    VEC_APPEND(v, 25);
    VEC_APPEND(v, 45);
    VEC_DELETE(v, 2);
    EXPECT_EQ(v.size, 2);
    EXPECT_EQ(VEC_I(v, 0), 5);
    EXPECT_EQ(VEC_I(v, 1), 25);
    VEC_DESTROY(v);
)

TEST_CASE(vector_remove_elements2,
    VEC_INIT(v, int);
    VEC_APPEND(v, 5);
    VEC_APPEND(v, 25);
    VEC_APPEND(v, 45);
    VEC_DELETE(v, 1);
    EXPECT_EQ(v.size, 2);
    EXPECT_EQ(VEC_I(v, 0), 5);
    EXPECT_EQ(VEC_I(v, 1), 45);
    VEC_DESTROY(v);
)

TEST_CASE(vector_remove_elements3,
    VEC_INIT(v, int);
    VEC_APPEND(v, 5);
    VEC_APPEND(v, 25);
    VEC_APPEND(v, 45);
    VEC_DELETE(v, 0);
    EXPECT_EQ(v.size, 2);
    EXPECT_EQ(VEC_I(v, 0), 25);
    EXPECT_EQ(VEC_I(v, 1), 45);
    VEC_DESTROY(v);
)

TEST_CASE(vector_remove_elements4,
    VEC_INIT(v, int);
    VEC_APPEND(v, 5);
    VEC_APPEND(v, 25);
    VEC_APPEND(v, 45);
    VEC_DELETE(v, 0);
    VEC_DELETE(v, 1);
    VEC_DELETE(v, 2);
    EXPECT_EQ(v.size, 0);
    VEC_DESTROY(v);
)

TEST_CASE(vector_remove_elements5,
    VEC_INIT(v, int);
    VEC_APPEND(v, 5);
    VEC_APPEND(v, 25);
    VEC_APPEND(v, 45);
    VEC_DELETE(v, 0);
    VEC_DELETE(v, 2);
    EXPECT_EQ(v.size, 1);
    EXPECT_EQ(VEC_I(v, 0), 25);
    VEC_DESTROY(v);
)

TEST_CASE(vector_append_many_elements,
    VEC_INIT(v, int);
    int n = 1000000000;
    for (int i = 0; i < n; i++) {
        VEC_APPEND(v, i+10);
    }
    EXPECT_EQ(v.size, n);
    VEC_DESTROY(v);
)

TEST_CASE(vector_append_and_remove_many_elements,
    VEC_INIT(v, int);
    int n = 100000;
    for (int i = 0; i < n; i++) {
        VEC_APPEND(v, i+10);
    }
    for (int i = n/2; i > n/3; i--) {
        VEC_DELETE(v, i);
    }
    EXPECT_EQ(v.size, n - ((n/2) - (n/3)));
    VEC_DESTROY(v);
)

TEST_CASE(vector_initialize_with_a_few_elements,
    VEC_INIT_N(v, 4, int, 5, 25, 35, 45);
    EXPECT_EQ(VEC_I(v, 0), 5);
    EXPECT_EQ(VEC_I(v, 1), 25);
    EXPECT_EQ(VEC_I(v, 2), 35);
    EXPECT_EQ(VEC_I(v, 3), 45);
    EXPECT_EQ(v.size, 4);
    VEC_DESTROY(v);
)

TEST_CASE(vector_initialize_with_many_elements,
    VEC_INIT_N(v, 400, int, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 45, 5, 25, 35, 33, 5, 25, 35, 45);
    EXPECT_EQ(VEC_I(v, 0), 5);
    EXPECT_EQ(VEC_I(v, 1), 25);
    EXPECT_EQ(VEC_I(v, 2), 35);
    EXPECT_EQ(VEC_I(v, 3), 45);
    EXPECT_EQ(VEC_I(v, 395), 33);
    EXPECT_EQ(v.size, 400);
    VEC_DESTROY(v);
)

TEST_CASE(vector_change_elements,
    VEC_INIT_N(v, 4, int, 5, 25, 35, 45);
    EXPECT_EQ(VEC_I(v, 0), 5);
    EXPECT_EQ(VEC_I(v, 1), 25);
    EXPECT_EQ(VEC_I(v, 2), 35);
    EXPECT_EQ(VEC_I(v, 3), 45);
    VEC_I(v, 1) = 14;
    VEC_I(v, 3) = 24;
    EXPECT_EQ(VEC_I(v, 1), 14);
    EXPECT_EQ(VEC_I(v, 3), 24);
    EXPECT_EQ(v.size, 4);
    VEC_DESTROY(v);
)


