#include "Application.h"

#include <iostream>
#include <string>

#include "FileTxt.h"
#include "Matrix.hpp"

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
        ExecuteProblemOne();
    }
    else if (problem_ == TWO) {
        ExecuteProblemTwo();
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

void Application::ExecuteProblemOne() {
    size_t positiveInteger = 0;
    size_t sum = 0;
    std::cout << "Enter a positive integer: ";
    std::cin >> positiveInteger;
    for (int i = 1; i <= positiveInteger; i++) {
        sum += (isPrime(i) ? i : 0);
    }
    std::cout << sum << std::endl;
}

bool Application::isPrime(const size_t& positiveInteger) {
    if (positiveInteger == 1) {
        return false;
    }
    for (int i = 2; i < positiveInteger; i++) {
        if (positiveInteger % i == 0) {
            return false;
        }
    }
    return true;
}

void Application::ExecuteProblemTwo() {
    std::string filePath = "";
    std::cout << "filePath: ";
    std::cin >> filePath;
    filePath = "res/" + filePath;
    FileTxt fileTxt(filePath);
    if (fileTxt.GetContent_()[0] == "Matrix_Transpose") {
        std::vector<std::vector<double>> ATemp;
        std::vector<std::string> row;
        for (int i = 2; i < fileTxt.GetContent_().size() - 1; i++) {
            row = fileTxt.SplitSpecificLine(" ", i);
            row.pop_back();
            std::vector<double> temp;
            for (const std::string& element : row) {
                temp.push_back(std::stod(element));
            }
            ATemp.push_back(temp);
        }
        Matrix<double> A(ATemp);
        A.FlipMatrixRowColumn().Print();
    }
    else if (fileTxt.GetContent_()[0] == "Matrix_Multiplication") {
        std::vector<std::vector<double>> ATemp;
        std::vector<std::vector<double>> BTemp;
        std::vector<std::string> row;
        int i = 2;
        for (i = 2; i < fileTxt.GetContent_().size() - 1; i++) {
            if (fileTxt.GetContent_()[i].find("Name") == std::string::npos) {
                row = fileTxt.SplitSpecificLine(" ", i);
                row.pop_back();
                std::vector<double> temp;
                for (const std::string& element : row) {
                    temp.push_back(std::stod(element));
                }
                ATemp.push_back(temp);
            }
            else {
                break;
            }
        }
        Matrix<double> A(ATemp);
        for (++i; i < fileTxt.GetContent_().size() - 1; i++) {
            row = fileTxt.SplitSpecificLine(" ", i);
            row.pop_back();
            std::vector<double> temp;
            for (const std::string& element : row) {
                temp.push_back(std::stod(element));
            }
            BTemp.push_back(temp);
        }
        Matrix<double> B(BTemp);
        A.Multiplication(B).Print();
    }
}