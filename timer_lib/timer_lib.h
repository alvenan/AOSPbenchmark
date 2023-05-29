#ifndef __TIMER_H__
#define __TIMER_H__

#include <fstream>

using namespace std;

class Timer {
private:
    bool is_timer_started = false;
    ofstream export_file, unexport_file;
    fstream start_file, finis_file;
    void gpioSetup();
    void gpioBreakup();
    static void keyboardExit(int signum, Timer *t);
public:
    Timer();
    ~Timer();
    bool getTimerBegin();
    void setTimer();
};

#endif