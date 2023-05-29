#include <iostream>
#include <chrono>
#include <thread>
#include <signal.h>
#include "timer_lib.h"

#define ON 1
#define OFF 0

using namespace std::this_thread;
using namespace std::chrono;

static const int start_pin = 20; //IN
static const int finis_pin = 21; //OUT

static const string gpio_driver_path = "/sys/class/gpio";
static const string export_path= gpio_driver_path + "/export";
static const string unexport_path= gpio_driver_path + "/unexport";
static const string start_path = gpio_driver_path + "/gpio" + to_string(start_pin);
static const string finis_path = gpio_driver_path + "/gpio" + to_string(finis_pin);


Timer::Timer(){
    gpioSetup();
}

Timer::~Timer(){ 
    gpioBreakup();
}

bool Timer::isReady() {
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

void Timer::trigger() {
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
    un_export_file.open(export_path);
    if(!un_export_file.is_open())
        cout << "Error on file " << export_path << endl;
    else {
        un_export_file << start_pin << endl;
        un_export_file << finis_pin << endl;
        un_export_file.close();
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
    un_export_file.open(unexport_path);
    if(!un_export_file.is_open())
        cout << "Error on file " << unexport_path << endl;

    else {
        un_export_file << start_pin << endl;
        un_export_file << finis_pin << endl;
        un_export_file.close();
    }  
}