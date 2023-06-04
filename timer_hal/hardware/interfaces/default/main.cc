#include "timer_service.h"

using namespace aidl::vendor::alvenan::timer;
using ndk::SharedRefBase;

int main() {

    ALOG(LOG_INFO, "TimerService", "Starting service");
        
    ABinderProcess_setThreadPoolMaxThreadCount(0);
    shared_ptr<TimerService> timer_service = SharedRefBase::make<TimerService>();

    const string instance = string() + ITimer::descriptor + "/default";
    binder_status_t status = AServiceManager_addService(timer_service->asBinder().get(),instance.c_str());
    if(status != STATUS_OK) {
        ALOG(LOG_ERROR, "TimerService", "Service not registred with error code %d", status);    
        return EXIT_FAILURE;
    }

    ALOG(LOG_INFO, "TimerService", "Serviço iniciado com nome %s", instance.c_str());
    ABinderProcess_joinThreadPool();

    ALOG(LOG_ERROR, "TimerService", "Something wrong is not right with the service!");    
    return EXIT_FAILURE;
}