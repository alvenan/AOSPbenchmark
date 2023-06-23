#include <iostream>
#include <chrono>
#include <thread>
#include "timer_lib.h"

#define ON 1
#define OFF 0

using std::this_thread::sleep_for;
using std::chrono::milliseconds;

static const int reset_pin = 16; //IN
static const int isready_pin = 20; //IN
static const int trigger_pin = 21; //OUT

static const string gpio_driver_path = "/sys/class/gpio";
static const string export_path= gpio_driver_path + "/export";
static const string unexport_path= gpio_driver_path + "/unexport";
static const string reset_path = gpio_driver_path + "/gpio" + to_string(reset_pin);
static const string isready_path = gpio_driver_path + "/gpio" + to_string(isready_pin);
static const string trigger_path = gpio_driver_path + "/gpio" + to_string(trigger_pin);


Timer::Timer(){
    gpioSetup();
}

Timer::~Timer(){ 
    // gpioBreakup();
}

bool Timer::isReady() {
    isready_file.open(isready_path + "/value");
    if(!isready_file.is_open())
        cout << "Error on file " << isready_path << "/value" << endl;
    else{
        isready_file >> is_timer_started;
        isready_file.close();
        return !is_timer_started;
    }
    return true;
}

void Timer::trigger() {
    trigger_file.open(trigger_path + "/value");
    if(!trigger_file.is_open())
        cout << "Error on file " << trigger_path << "/value" << endl;
    else {
        trigger_file << ON << endl;
        sleep_for(milliseconds(200));
        trigger_file << OFF << endl;
        trigger_file.close();
    }
}

void Timer::reset() {
    reset_file.open(reset_path + "/value");
    if(!reset_file.is_open())
        cout << "Error on file " << reset_path << "/value" << endl;
    else {
        reset_file << ON << endl;
        sleep_for(milliseconds(200));
        reset_file << OFF << endl;
        reset_file.close();
    }
}
void Timer::gpioSetup() {
    //Export Timer GPIOs
    un_export_file.open(export_path);
    if(!un_export_file.is_open())
        cout << "Error on file " << export_path << endl;
    else {
        un_export_file << isready_pin << endl;
        un_export_file << trigger_pin << endl;
        un_export_file << reset_pin << endl;
        un_export_file.close();
    }

    //Set GPIO Directions
    isready_file.open(isready_path + "/direction");
    if(!isready_file.is_open())
        cout << "Error on file " << isready_path << "/direction" << endl;
    else {
        isready_file << "in" << endl;
        isready_file.close();
    }
    trigger_file.open(trigger_path + "/direction");
    if(!trigger_file.is_open())
        cout << "Error on file " << trigger_path << "/direction" << endl;
    else {
        trigger_file << "out" << endl;
        trigger_file.close();
    }
    reset_file.open(reset_path + "/direction");
    if(!reset_file.is_open())
        cout << "Error on file " << reset_path << "/direction" << endl;
    else {
        reset_file << "out" << endl;
        reset_file.close();
    }
}

void Timer::gpioBreakup() {
    //Unexport Timer GPIOs
    un_export_file.open(unexport_path);
    if(!un_export_file.is_open())
        cout << "Error on file " << unexport_path << endl;
    else {
        un_export_file << isready_pin << endl;
        un_export_file << trigger_pin << endl;
        un_export_file << reset_pin << endl;
        un_export_file.close();
    }  
}