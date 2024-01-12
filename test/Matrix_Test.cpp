#include <gtest/gtest.h>

#include "../src/Matrix.hpp"

TEST(Matrix_Test, Constructor) {
    
    // test1
    int answer1[3][3] = {
        { 1, 2, 3 },
        { 4, 5, 6 },
        { 7, 8, 9 }
    };
    Matrix<int> test1(*answer1, 3, 3);
    for (int i = 0; i < test1.GetMatrix_().size(); i++) {
        for (int j = 0; j < test1[0].size(); j++) {
            EXPECT_EQ(answer1[i][j], test1[i][j]);
        }
    }

    // test2
    std::vector<std::vector<int>> answer2 = {
        { 1, 2, 3 },
        { 4, 5, 6 },
        { 7, 8, 9 }
    };
    Matrix<int> test2(answer2);
    for (int i = 0; i < test2.GetMatrix_().size(); i++) {
        for (int j = 0; j < test2[0].size(); j++) {
            EXPECT_EQ(answer2[i][j], test2[i][j]);
        }
    }
}