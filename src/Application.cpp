#include "Application.h"
#include "FileTxt.h"
#include "Matrix.hpp"

#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>

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
        ExecuteProblemThree();
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

void Application::ExecuteProblemThree() {
    // LoadFile
    std::string filePath = "";
    std::cout << "filePath: ";
    std::cin >> filePath;
    FileTxt fileTxt("res/problem3/" + filePath);

    std::vector<std::pair<size_t, int>> dict =  LoadDatas(fileTxt);
    QuickSortDict(dict, 0, dict.size()-1);

    int targetNumber;
    std::cout << "Find? ";
    std::cin >> targetNumber;
    std::vector<std::pair<size_t, int>> targetNumberElements = FindElements(dict, targetNumber);
    std::ofstream outputFile("res/problem3/output/" + filePath);

    if (targetNumberElements.size() != 0) {
        outputFile << "Find:" << std::endl;
        for (const std::pair<size_t, int>& element : targetNumberElements) {
            outputFile << "A" << element.first << " " << element.second << std::endl;
        }
    }
    else {
        outputFile << "Cannot Find " << targetNumber << std::endl;
    }
    outputFile << std::endl;
    for (const std::pair<size_t, int>& element : dict) {
        outputFile << "A" << element.first << " " << element.second << std::endl;
    }

    outputFile.close();

}

std::vector<std::pair<size_t, int>> Application::LoadDatas(const FileTxt& fileTxt) {
    // Load datas
    std::vector<std::pair<size_t, int>> datas;
    for (int i = 0; i < fileTxt.GetContent_().size(); i++) {
        std::vector<std::string> tempLine = fileTxt.SplitSpecificLine(" ", i);
        datas.push_back(std::pair<size_t, int>(std::stoi(tempLine[0].substr(1, tempLine[0].size()-1)), std::stoi(tempLine[1])));
    }

    return datas;
}

void Application::QuickSortDict(std::vector<std::pair<size_t, int>>& dict, size_t begin, size_t end) {
    if (begin >= end) {
        return;
    }

    size_t left = begin;
    size_t right = end;
    int pivot = dict[(left + right) / 2].second;

    while (left <= right) {
        while (dict[left].second < pivot) left++;
        while (dict[right].second > pivot) right--;

        if (left <= right) {
            std::swap(dict[left], dict[right]);
            left++;
            right--;
        }
    }

    if (begin < right) QuickSortDict(dict, begin, right);
    if (left < end) QuickSortDict(dict, left, end);
}

int Application::BinarySearch(const std::vector<std::pair<size_t, int>>& dict, int value, size_t low, size_t high) {
    while (low <= high) {
        size_t mid = low + (high - low) / 2;
        if (dict[mid].second == value) {
            return mid;
        } else if (dict[mid].second < value) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

std::vector<std::pair<size_t, int>> Application::FindElements(const std::vector<std::pair<size_t, int>>& dict, int value) {
    std::vector<std::pair<size_t, int>> result;
    int index = BinarySearch(dict, value, 0, dict.size() - 1);

    if (index != -1) {
        int left = index;
        while (left >= 0 && dict[left].second == value) {
            result.push_back(dict[left]);
            --left;
        }

        int right = index + 1;
        while (right < dict.size() && dict[right].second == value) {
            result.push_back(dict[right]);
            ++right;
        }
    }

    return result;
}