#pragma once

#include <log/log.h>
#include <android/binder_process.h>
#include <android/binder_manager.h>
#include <aidl/vendor/alvenan/timer/BnTimer.h>
#include <timer_lib.h>

using namespace aidl::vendor::alvenan::timer;
using namespace std;
using ndk::ScopedAStatus;

namespace aidl::vendor::alvenan::timer {

class TimerService : public BnTimer {
    private:
        Timer t;
    public:
        ScopedAStatus isReady(bool* _aidl_return) override;
        ScopedAStatus trigger()  override;
        ScopedAStatus reset()  override;
};

}