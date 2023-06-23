#ifndef __TIMER_H__
#define __TIMER_H__

#include <fstream>

using namespace std;

class Timer {
private:
    bool is_timer_started = false;
    ofstream un_export_file;
    fstream reset_file, isready_file, trigger_file;
    void gpioSetup();
    void gpioBreakup();
public:
    Timer();
    ~Timer();
    bool isReady();
    void trigger();
    void reset();
};

#endif