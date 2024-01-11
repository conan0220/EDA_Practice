#pragma once

#include <iostream>
#include <vector>

class FileTxt {
public:
    FileTxt(const std::string& filePath);
    ~FileTxt();

private:
    std::string filePath_ = "";
    std::vector<std::string> content_;
};