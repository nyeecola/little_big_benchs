TEST_CASE(add_element_to_vector,
    std::vector<int> v;
    v.push_back(5);
    EXPECT_EQ(v[0], 5);
)

TEST_CASE(add_element_to_vector2,
    std::vector<int> v;
    v.push_back(5);
    v.push_back(25);
    EXPECT_EQ(v[0], 5);
    EXPECT_EQ(v[1], 25);
)

