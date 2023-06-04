#ifndef __TIMER_H__
#define __TIMER_H__

#include <fstream>
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

class Timer {
private:
    bool is_timer_started = false;
    ofstream un_export_file;
    fstream start_file, finis_file;
    void gpioSetup();
    void gpioBreakup();
public:
    Timer();
    ~Timer();
    bool isReady();
    void trigger();
};

#endif