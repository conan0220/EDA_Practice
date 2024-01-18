#pragma once

#include "FileTxt.h"

#include <map>
#include <vector>

enum Problem {
    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE
};

class Application {
public:
    Application();
    ~Application();

private:
    void SelectProblem();
    void ExecuteSelectedProblem();

    void ExecuteProblemOne();
    bool isPrime(const size_t& positiveInteger);

    void ExecuteProblemTwo();

    void ExecuteProblemThree();
    std::vector<std::pair<size_t, int>> LoadDatas(const FileTxt& fileTxt);
    void QuickSortDict(std::vector<std::pair<size_t, int>>& dict, size_t begin, size_t end);
    int BinarySearch(const std::vector<std::pair<size_t, int>>& dict, int value, size_t low, size_t high);
    std::vector<std::pair<size_t, int>> FindElements(const std::vector<std::pair<size_t, int>>& dict, int value);


    Problem problem_;
};
