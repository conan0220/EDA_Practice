#include "TimeTracker.h"

TimeTracker::TimeTracker() {
    start_time_ = clock();
}

TimeTracker::~TimeTracker() {
    clock_t end_time = clock();
    double time_elapsed = double(end_time - start_time_) / CLOCKS_PER_SEC * 1000;
    std::cout << "TimeTracker destroyed after " << time_elapsed << " ms." << std::endl;
}