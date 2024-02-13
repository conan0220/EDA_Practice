#include "Application.h"
#include "FileTxt.h"
#include "Matrix.hpp"
#include "Node.h"
#include "TimeTracker.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <list>

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
        ExecuteProblemFour();
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
    int size = fileTxt.GetContent_().size();
    for (int i = 0; i < size; i++) {
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

void Application::ExecuteProblemFour() {
    std::string filePath;
    std::cout << "filePath: ";
    std::cin >> filePath;
    FileTxt inputFile("res/problem4/" + filePath);

    TimeTracker timeTracker;

    std::vector<Node> nodes = GetNodesFromFile(inputFile);

    std::vector<Line> lines = GetLines(nodes);
    std::sort(lines.begin(), lines.end(), [](const Line& line1, const Line& line2) {
        return line1.length < line2.length;
    }); // sort lines

    SpanningTree minimumSpanningTree(GetMinimumSpanningTree(lines));

    std::ofstream outputFile("res/problem4/output/" + filePath);
    for (const Line& line : minimumSpanningTree.GetLines_()) {
        outputFile << "(N" << line.node1.GetN_() << ",N" << line.node2.GetN_() << ") Length = " << line.length << std::endl;
    }
    outputFile << "Total Wire Length = " << minimumSpanningTree.TotalLength();
}

std::vector<Node> Application::GetNodesFromFile(const FileTxt& inputFile) {
    std::vector<Node> nodes;
    std::vector<std::string> content = inputFile.GetContent_();
    int i = 0;
    for (const std::string& line : content) {
        unsigned N = ++i;
        float x;
        float y;
        std::vector<std::string> temp = FileTxt::SplitString(",", FileTxt::SplitString("(", line)[1]);
        x = std::stof(temp[0]);
        y = std::stof(FileTxt::SplitString(")", temp[1])[0]);
        Node node = Node(N, x, y);
        nodes.push_back(node);
    }

    return nodes;
}

std::vector<Line> Application::GetLines(std::vector<Node> nodes) {
    std::vector<Line> lines;
    unsigned nodesSize = nodes.size();
    for (int i = 0; i < nodesSize; i++) {
        for (int j = i+1; j < nodesSize; j++) {
            lines.push_back(Line(nodes[i], nodes[j]));
        }
    }
    return lines;
}

StateOfLineInSpanningTree SpanningTree::StateOfLineInSpanningTree(const Line& line) const {
    bool isNode1InSpanningTree = false;
    bool isNode2InSpanningTree = false;

    for (const Line& line_ : lines_) {
        if (line.node1 == line_.node1 or line.node1 == line_.node2) {
            isNode1InSpanningTree = true;
        }
        if (line.node2 == line_.node1 or line.node2 == line_.node2) {
            isNode2InSpanningTree = true;
        }
        if (isNode1InSpanningTree and isNode2InSpanningTree) {
            return TWO_NODE_EXIT;
        }
    }
    if (!isNode1InSpanningTree and !isNode2InSpanningTree) {
        return ZERO_NODE_EXIT;
    }

    return ONE_NODE_EXIT;
}

SpanningTree Application::GetMinimumSpanningTree(const std::vector<Line>& lines) const {
    std::list<SpanningTree> trees;
    for (const Line& line : lines) {
        size_t numberOfTreesThatOneNodeExit = 0;
        SpanningTree* firstTreeThatOneNodeExit = nullptr;
        SpanningTree* secondTreeThatOneNodeExit = nullptr;
        StateOfLineInSpanningTree state;
        size_t indexOfSecondTreeThatOneNodeExit = 0;
        for (SpanningTree& tree : trees) {
            state = tree.StateOfLineInSpanningTree(line);
            if (state == TWO_NODE_EXIT) {
                break;
            }
            else if (state == ONE_NODE_EXIT) {
                numberOfTreesThatOneNodeExit++;
                if (numberOfTreesThatOneNodeExit == 1) {
                    firstTreeThatOneNodeExit = &tree;
                }
                else if (numberOfTreesThatOneNodeExit == 2) {
                    secondTreeThatOneNodeExit = &tree;
                    break;
                }
            }
            indexOfSecondTreeThatOneNodeExit++;
        }
        if (numberOfTreesThatOneNodeExit == 1) {    // add new line to tree
            firstTreeThatOneNodeExit->AddNewLine(line);
        }
        else if (numberOfTreesThatOneNodeExit == 2) {   // merge two tree with line
            firstTreeThatOneNodeExit->AddNewLine(line);
            firstTreeThatOneNodeExit->Merge(*secondTreeThatOneNodeExit);
            auto it = trees.begin();
            std::advance(it, indexOfSecondTreeThatOneNodeExit);
            trees.erase(it);
        }
        else if (state == TWO_NODE_EXIT) {
            continue;
        }
        else {
            trees.push_back(SpanningTree(line));
        }
    }

    return trees.front();
}

void SpanningTree::Merge(const SpanningTree& other) {
    for (const Line& line : other.GetLines_()) {
        lines_.push_back(line);
    }
}

float SpanningTree::TotalLength() const {
    float total = 0;
    for (const Line& line : lines_) {
        total += line.length;
    }
    return total;
}
