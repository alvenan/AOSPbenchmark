#include "vendor_alvenan_javanativetestservice_JavaNativeTestServiceImpl.h"
#include <timer_lib.h>

static Timer timer;

JNIEXPORT jboolean JNICALL Java_vendor_alvenan_javanativetestservice_JavaNativeTestServiceImpl_nativeTimerIsReady
  (JNIEnv *, jclass){
    return timer.isReady();
  }

JNIEXPORT void JNICALL Java_vendor_alvenan_javanativetestservice_JavaNativeTestServiceImpl_nativeTimerTrigger
  (JNIEnv *, jclass){
    timer.trigger();
  }

JNIEXPORT void JNICALL Java_vendor_alvenan_javanativetestservice_JavaNativeTestServiceImpl_nativeAlgorithmExec
  (JNIEnv *, jclass){
    //TODO
  }
