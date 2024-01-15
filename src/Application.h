#pragma once

#include "FileTxt.h"

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
    Problem problem_;
};
