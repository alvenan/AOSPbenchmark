#include "timer_service.h"

namespace aidl::vendor::alvenan::timer {

ScopedAStatus TimerService::isReady(bool* _aidl_return){
    *_aidl_return = t.isReady();
    return ScopedAStatus::ok();
}

ScopedAStatus TimerService::trigger(){
    t.trigger(); 
    return ScopedAStatus::ok();
}

ScopedAStatus TimerService::reset(){
    t.reset(); 
    return ScopedAStatus::ok();
}

};