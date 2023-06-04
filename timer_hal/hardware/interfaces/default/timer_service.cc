#include "timer_service.h"

namespace aidl::vendor::alvenan::timer {

ScopedAStatus TimerService::isReady(bool* _aidl_return){
    if(t.isReady())
        ALOG(LOG_INFO, "TimerService", "Timer is ready!");
    else
        ALOG(LOG_INFO, "TimerService", "Timer is NOT ready!");
    *_aidl_return = t.isReady();
    return ScopedAStatus::ok();
}

ScopedAStatus TimerService::trigger(){
    t.trigger(); 
    return ScopedAStatus::ok();
}

};