#include <gtest/gtest.h>
#include <cmath>

#include "../src/Node.h"

TEST(Node_Test, GetDistance) {
    // test1
    Node test1A(0, 1, 4);
    Node test1B(1, 2, 3);
    EXPECT_EQ(test1A.GetDistance(test1B), (float)sqrt(2));

    // test2
    Node test2A(0, 1, 4);
    Node test2B(1, 3, 5);
    EXPECT_EQ(test2A.GetDistance(test2B), (float)sqrt(5));
    
    // test3
    Node test3A(0, 6, 5);
    Node test3B(1, 3, 5);
    EXPECT_EQ(test3A.GetDistance(test3B), (float)sqrt(9));
}
