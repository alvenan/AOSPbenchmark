#ifndef __TIMER_H__
#define __TIMER_H__

#include <iostream>
#include <fstream>

class Timer {
private:
    bool is_timer_started = false;
    std::ofstream export_file, unexport_file;
    std::fstream start_file, finis_file;
    void gpioSetup();
    void gpioBreakup();
public:
    Timer();
    ~Timer();
    bool getTimerBegin();
    void setTimerEnd();
};

#endif