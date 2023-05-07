#include <chrono>
#include <thread>
#include "timer.h"

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

static const string start_pin = "20"; //IN
static const string finis_pin = "21"; //OFF

static const string gpio_driver_path = "/sys/class/gpio";

Timer::Timer(){
    gpioSetup();
}

Timer::~Timer(){ 
    gpioBreakup();
}

bool Timer::getTimerBegin() {
    start_file >> is_timer_started;
    return is_timer_started;
}

void Timer::setTimerEnd() {
    finis_file << "1";
    sleep_for(milliseconds(200));
    finis_file << "0";
}

void Timer::gpioSetup() {

    //Export Timer GPIOs
    export_file.open(gpio_driver_path + "/export");
    if(!export_file.is_open())
        cout << "Error on file " << gpio_driver_path << "/export" << endl;

    else {
        export_file << start_pin << endl;
        export_file << finis_pin << endl;
        export_file.close();
    }

    //Set GPIO Directions
    start_file.open(gpio_driver_path + "/gpio" + start_pin + "/direction");
    if(!start_file.is_open())
        cout << "Error on file " << gpio_driver_path << "/gpio" << start_pin << "/direction" << endl;
    else {
        start_file << "in" << endl;
        start_file.close();
    }
    finis_file.open(gpio_driver_path + "/gpio" + finis_pin + "/direction");
    if(!finis_file.is_open())
        cout << "Error on file " << gpio_driver_path << "/gpio" << finis_pin << "/direction" << endl;
    else {
        finis_file << "out" << endl;
        finis_file.close();
    }

    //Open the files to be checked
    start_file.open(gpio_driver_path + "/gpio" + start_pin + "/value");
    if(!start_file.is_open())
        cout << "Error on file " << gpio_driver_path << "/gpio" << start_pin << "/value" << endl;

    finis_file.open(gpio_driver_path + "/gpio" + finis_pin + "/value");
    if(!finis_file.is_open())
        cout << "Error on file " << gpio_driver_path << "/gpio" << finis_pin << "/value" << endl;
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