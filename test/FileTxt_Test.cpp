#include <gtest/gtest.h>

#include "../src/FileTxt.h"

TEST(FileTxt_Test, Split) {
    // test1
    FileTxt test1("res/FileTxt_Test1.txt");
    std::vector<std::string> result = test1.Split(" ");
    std::vector<std::string> answer = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" };
    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(answer[i], result[i]);
    }
}