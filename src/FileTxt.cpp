#include "FileTxt.h"

#include <fstream>  
#include <iostream>
#include <string>


/**
 * @brief Constructor for the FileTxt class.
 * 
 * Initializes a FileTxt object by loading the contents of a text file into the 'content_' member variable.
 * 
 * @param filePath The path of the file to be read.
 * 
 * The constructor sets the 'filePath_' member to the provided file path, then attempts to open the file.
 * It reads the file line by line, adding each line to the 'content_' vector.
 * The file is closed after reading its contents.
 */
FileTxt::FileTxt(const std::string& filePath)
    : filePath_(filePath) {
    std::ifstream file(filePath);

    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filePath);
    }
    else {
        std::string line = "";
        while (std::getline(file, line)) {
            content_.push_back(line);
        }
    }

    file.close();
}

FileTxt::~FileTxt() {

}

/**
 * @brief Prints the contents of the file.
 * 
 * Iterates through each line stored in the 'content_' member variable, 
 * which is a collection of std::string, and prints each line to the standard output.
 */
void FileTxt::Print() const {
    for (const std::string& line : content_) {
        std::cout << line << std::endl;
    }
}

/**
 * @brief Splits each line of file content based on a specified pattern and returns the non-empty segments.
 * 
 * This function processes each line in the 'content_' member (which contains the file's lines) 
 * and splits them based on the provided pattern. It collects non-empty segments into a vector 
 * and returns it.
 * 
 * @param pattern The string used as a pattern for splitting the lines.
 * @return std::vector<std::string> A vector containing the non-empty split segments of the file's content.
 * 
 * The function iterates over each line, using two pointers: 'begin' and 'end'.
 * 'begin' marks the start of a segment, and 'end' marks the end (the occurrence of the pattern).
 * Segments between 'begin' and 'end' (excluding the pattern) are added to 'result' if they are non-empty.
 * The search for the pattern resumes from the position right after the last found occurrence.
 * After the loop, any remaining part of the line from 'begin' to the end is added to 'result'.
 */
std::vector<std::string> FileTxt::Split(const std::string& pattern) const {
    std::vector<std::string> result;
    std::string::size_type begin, end;
    
    for (const std::string& line : content_) {
        begin = 0;
        end = line.find(pattern);
        while (end != std::string::npos) {
            if (end - begin != 0) {
                result.push_back(line.substr(begin, end-begin));
            }
            begin = end + pattern.length();
            end = line.find(pattern, begin);
        }

        if (begin < line.length()) {
            result.push_back(line.substr(begin));
        }
    }
    
    return result;
}

std::vector<std::string> FileTxt::SplitSpecificLine(const std::string& pattern, const size_t& lineIndex) const {
    std::vector<std::string> result;
    std::string::size_type begin, end;

    std::string line = content_[lineIndex];
    begin = 0;
    end = line.find(pattern);
    while (end != std::string::npos) {
        if (end - begin != 0) {
            result.push_back(line.substr(begin, end - begin));
        }
        begin = end + pattern.length();
        end = line.find(pattern, begin);
    }

    if (begin < line.length()) {
        result.push_back(line.substr(begin));
    }

    return result;
}