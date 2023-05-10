#ifndef __TIMER_H__
#define __TIMER_H__

#include <iostream>
#include <fstream>

using namespace std;

class Timer {
private:
    bool is_timer_started = false;
    ofstream export_file, unexport_file;
    fstream start_file, finis_file;
    void gpioSetup();
    void gpioBreakup();
public:
    Timer();
    ~Timer();
    bool getTimerBegin();
    void setTimerEnd();
};

void keyboardExit(int signum, Timer *t);

#endif