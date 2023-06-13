#include <jni.h>
#include <log/log.h>
#include <algorithms.h>

extern "C" JNIEXPORT void JNICALL
Java_vendor_alvenan_javanativetestapp_JavaNativeTestAppImpl_algorithmExec (
        JNIEnv*, jobject) {
    ALOG(LOG_INFO, "JavaNativeTestApp: C++", "Hello from C++");
    ALOG(LOG_INFO, "JavaNativeTestApp: C++", "%s", testfunc().c_str());

}