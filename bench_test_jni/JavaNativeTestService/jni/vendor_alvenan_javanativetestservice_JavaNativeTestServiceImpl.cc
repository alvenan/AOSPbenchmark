#include "vendor_alvenan_javanativetestservice_JavaNativeTestServiceImpl.h"
#include <log/log.h>

JNIEXPORT void JNICALL Java_vendor_alvenan_javanativetestservice_JavaNativeTestServiceImpl_nativeAlgorithmExec
  (JNIEnv *, jclass){
    ALOG(LOG_INFO, "JavaNativeTestServiceJNI", "Entered in the algorithm function successfully via JNI!");
  }
