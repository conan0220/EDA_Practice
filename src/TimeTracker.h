#pragma once

#include <iostream>
#include <ctime>

// A class to track the execution time of a code block.
// The TimeTracker class allows measuring the execution time of a block of code by capturing the
// start time when an instance is created, and the end time when the instance is destroyed.
// The elapsed time is then calculated as the difference between the start and end times.
// 
// Example usage:
//      {
//          TimeTracker timer;
//          // Code block to be timed
//      }
// 
// When the TimeTracker instance goes out of scope and is destroyed, the elapsed time is printed
// to the console in milliseconds.
class TimeTracker {
public:
    TimeTracker();

    ~TimeTracker();

private:
    clock_t start_time_;
};