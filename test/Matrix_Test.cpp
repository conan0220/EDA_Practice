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

TEST(Matrix_Test, FlipMatrixRowColumn) {
    // test1
    std::vector<std::vector<int>> input1 = {
        { 1, 2, 3 },
        { 4, 5, 6 },
        { 7, 8, 9 }
    };
    std::vector<std::vector<int>> answer1 = {
        { 1, 4, 7 },
        { 2, 5, 8 },
        { 3, 6, 9 }  
    };
    Matrix<int> test1(input1);
    Matrix<int> result1 = test1.FlipMatrixRowColumn();
    for (int i = 0; i < answer1.size(); i++) {
        for (int j = 0; j < answer1[0].size(); j++) {
            EXPECT_EQ(answer1[i][j], result1[i][j]);
        }
    }

    // test2
    std::vector<std::vector<int>> input2 = {
        { 1, 2, 3 },
        { 4, 5, 6 }
    };
    std::vector<std::vector<int>> answer2 = {
        { 1, 4 },
        { 2, 5 },
        { 3, 6 }  
    };
    Matrix<int> test2(input2);
    Matrix<int> result2 = test2.FlipMatrixRowColumn();
    for (int i = 0; i < answer2.size(); i++) {
        for (int j = 0; j < answer2[0].size(); j++) {
            EXPECT_EQ(answer2[i][j], result2[i][j]);
        }
    }
}

TEST(Matrix_Test, OperatorEquel) {
    // test1
    std::vector<std::vector<int>> answer1 = {
        { 1, 2, 3 },
        { 4, 5, 6 },
        { 7, 8, 9 }
    };
    Matrix<int> test1(answer1);
    EXPECT_EQ(true, test1 == answer1);
}

TEST(Matrix_Test, IsMatrixLegal) {
    // test1
    std::vector<std::vector<int>> input1 = {};
    EXPECT_EQ(false, Matrix<int>::IsMatrixLegal(input1));

    // test2
    std::vector<std::vector<int>> input2 = {
        { 1, 2, 3, 4 },
        { 5, 6, 7 }
    };
    EXPECT_EQ(false, Matrix<int>::IsMatrixLegal(input2));

    // test3
    std::vector<std::vector<int>> input3 = {
        { 1, 2, 3 },
        { 4, 5, 6 },
        { 7, 8, 9 }
    };
    EXPECT_EQ(true, Matrix<int>::IsMatrixLegal(input3));

}

TEST(Matrix_Test, Multiplication) {
    // test1
    Matrix<double> A1({
        { 1, 0, 2 },
        { -1, 3, 1 }
    });
    Matrix<double> B1({
        { 3, 1 },
        { 2, 1 },
        { 1, 0 }
    });
    Matrix<double> answer1({
        { 5, 1 },
        { 4, 2 }
    });
    Matrix<double> result1 = A1.Multiplication(B1);
    for (int i = 0; i < answer1.GetMatrix_().size(); i++) {
        for (int j = 0; j < answer1[0].size(); j++) {
            EXPECT_EQ(answer1[i][j], result1[i][j]);
        }
    }

    // test2
    Matrix<double> A2({
        { 1, 2 },
        { 2, 3 },
        { 3, 4 },
        { 4, 1 }
    });
    Matrix<double> B2({
        { 2, 3, 1, 4 },
        { 5, 7, 2, 3 }
    });
    Matrix<double> answer2({
        { 12, 17, 5, 10 },
        { 19, 27, 8, 17 },
        { 26, 37, 11, 24 },
        { 13, 19, 6, 19 }
    });
    Matrix<double> result2 = A2.Multiplication(B2);
    for (int i = 0; i < answer2.GetMatrix_().size(); i++) {
        for (int j = 0; j < answer2[0].size(); j++) {
            EXPECT_EQ(answer2[i][j], result2[i][j]);
        }
    }
}