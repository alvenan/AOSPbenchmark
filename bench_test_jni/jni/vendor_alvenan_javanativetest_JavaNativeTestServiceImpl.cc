#include "vendor_alvenan_javanativetestservice_JavaNativeTestServiceImpl.h"
#include <timer_lib>

static Timer timer;

JNIEXPORT jboolean JNICALL Java_vendor_alvenan_javanativetestservice_JavaNativeTestServiceImpl_nativeGetTimerBegin
  (JNIEnv *, jclass){
    timer.getTimerBegin();
  }

JNIEXPORT void JNICALL Java_vendor_alvenan_javanativetestservice_JavaNativeTestServiceImpl_nativeSetTimer
  (JNIEnv *, jclass){
    timer.setTimer();
  }

JNIEXPORT void JNICALL Java_vendor_alvenan_javanativetestservice_JavaNativeTestServiceImpl_nativeTestExec
  (JNIEnv *, jclass){

  }
