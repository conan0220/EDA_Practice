#pragma once

#include "FileTxt.h"
#include "Node.h"

#include <map>
#include <vector>

enum Problem {
    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE
};

struct Line {
    Node node1;
    Node node2;
    float length;

    Line(const Node& node1, const Node& node2)
        : node1(node1), node2(node2) {
        length = node1.GetDistance(node2);
    }

    bool operator==(const Line& other) const {
        return this->node1 == other.node1 && this->node2 == other.node2 || this->node1 == other.node2 && this->node2 == other.node1;
    }
};

enum StateOfLineInSpanningTree {
    ZERO_NODE_EXIT,
    ONE_NODE_EXIT,
    TWO_NODE_EXIT
};
class SpanningTree {
public:
    SpanningTree(const Line& line) { lines_.push_back(line); }
    SpanningTree(const SpanningTree& other) { lines_ = other.GetLines_(); }
    ~SpanningTree() {}

    inline const std::vector<Line>& GetLines_() const { return lines_; }
    inline void AddNewLine(const Line& line) { lines_.push_back(line); }
    StateOfLineInSpanningTree StateOfLineInSpanningTree(const Line& line) const;
    void Merge(const SpanningTree& other);

    bool operator==(const SpanningTree& other) const {
        for (int i = 0; i < lines_.size(); i++) {
            if (lines_[i] == other.GetLines_()[i]) 
                return false;
        }
        return true;
    }

private:
    std::vector<Line> lines_;
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

    void ExecuteProblemFour();
    std::vector<Node> GetNodesFromFile(const FileTxt& inputFile);
    std::vector<Line> GetLines(std::vector<Node> nodes);
    SpanningTree GetMinimumSpanningTree(const std::vector<Line>& lines) const;


    Problem problem_;
};
