#include "FileTxt.h"

#include <fstream>  
#include <iostream>
#include <string>

FileTxt::FileTxt(const std::string& filePath)
    : filePath_(filePath) {
    std::ifstream file(filePath);
    std::string line = "";
    while (std::getline(file, line)) {
        content_.push_back(line);
    }
    file.close();
}

FileTxt::~FileTxt() {

}