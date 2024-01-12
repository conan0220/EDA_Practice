#pragma once

#include <iostream>
#include <vector>

class FileTxt {
public:
    FileTxt(const std::string& filePath);
    ~FileTxt();

    void Print() const;

    std::vector<std::string> Split(const std::string& pattern) const;

    std::vector<std::string> GetContent_() const { return content_; }

private:
    std::string filePath_ = "";
    std::vector<std::string> content_;
};