#include <chrono>
#include <thread>
#include "timer.h"


#define ON 1
#define OFF 0

using namespace std::this_thread;
using namespace std::chrono;

static const int start_pin = 20; //IN
static const int finis_pin = 21; //OUT

static const string gpio_driver_path = "/sys/class/gpio";
static const string export_path= gpio_driver_path + "/export";
static const string start_path = gpio_driver_path + "/gpio" + to_string(start_pin);
static const string finis_path = gpio_driver_path + "/gpio" + to_string(finis_pin);


Timer::Timer(){
    gpioSetup();
}

Timer::~Timer(){ 
    gpioBreakup();
}

bool Timer::getTimerBegin() {

    start_file.open(start_path + "/value");
    if(!start_file.is_open())
        cout << "Error on file " << start_path << "/value" << endl;
    else{
        start_file >> is_timer_started;
        start_file.close();
        return !is_timer_started;
    }
    return true;
}

void Timer::setTimerEnd() {

    finis_file.open(finis_path + "/value");
    if(!finis_file.is_open())
        cout << "Error on file " << finis_path << "/value" << endl;
    else {
        finis_file << ON << endl;
        sleep_for(milliseconds(200));
        finis_file << OFF << endl;
        finis_file.close();
    }
}

void Timer::gpioSetup() {

    //Export Timer GPIOs
    export_file.open(export_path);
    if(!export_file.is_open())
        cout << "Error on file " << export_path << endl;
    else {
        export_file << start_pin << endl;
        export_file << finis_pin << endl;
        export_file.close();
    }

    //Set GPIO Directions
    start_file.open(start_path + "/direction");
    if(!start_file.is_open())
        cout << "Error on file " << start_path << "/direction" << endl;
    else {
        start_file << "in" << endl;
        start_file.close();
    }
    finis_file.open(finis_path + "/direction");
    if(!finis_file.is_open())
        cout << "Error on file " << finis_path << "/direction" << endl;
    else {
        finis_file << "out" << endl;
        finis_file.close();
    }
}

void Timer::gpioBreakup() {
    //Unexport Timer GPIOs
    unexport_file.open(gpio_driver_path + "/unexport");
    if(!unexport_file.is_open())
        cout << "Error on file " << gpio_driver_path << "/unexport" << endl;

    else {
        unexport_file << start_pin << endl;
        unexport_file << finis_pin << endl;
        export_file.close();
    }  
}

void keyboardExit(int signum, Timer *t) {

    static Timer *aux = t;
    if(signum == SIGINT) {
        delete aux;
        exit(signum);
    }
}