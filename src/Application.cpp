#include "Application.h"

#include <iostream>

Application::Application() {
    SelectProblem();
    ExecuteSelectedProblem();
}

Application::~Application() {

}

void Application::SelectProblem() {
    unsigned problemINT = 0;
    std::cout << "Problem (e.x 1, 2, 3 ...): ";
    std::cin >> problemINT;
    problem_ = (Problem)--problemINT;
}

void Application::ExecuteSelectedProblem() {
    if (problem_ == ONE) {

    }
    else if (problem_ == TWO) {

    }
    else if (problem_ == THREE) {

    }
    else if (problem_ == FOUR) {

    }
    else if (problem_ == FIVE) {

    }
    else {
        std::cerr << "The problem doesn't exist." << std::endl;
        SelectProblem();
        ExecuteSelectedProblem();
    }
}