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

    Problem problem_;
};
