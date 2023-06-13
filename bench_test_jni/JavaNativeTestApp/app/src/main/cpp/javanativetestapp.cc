#include <jni.h>
#include <log/log.h>

extern "C" JNIEXPORT void JNICALL
Java_vendor_alvenan_javanativetestapp_JavaNativeTestAppImpl_algorithmExec (
        JNIEnv*, jobject) {
    ALOG(LOG_INFO, "JavaNativeTestApp", "Hello from C++");
}