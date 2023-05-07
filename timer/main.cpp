#include "timer.h"
#include <chrono>
#include <thread>

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

int main(int argv, char *argc[]){
    Timer *timer = new Timer;
    
    while (timer->getTimerBegin());
    
    cout << "Começou a contar" << endl;
    sleep_for(seconds((int) argc[0]));
    timer->setTimerEnd();

    return 0;
}