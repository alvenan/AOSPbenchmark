package vendor.alvenan.javanativetestservice;

import android.content.Context;

class JavaNativeTestServiceImpl extends IJavaNativeTestService.Stub {
    public static final String JAVANATIVETEST_PERM = 
        "vendor.alvenan.javanativetestservice.permission.JAVANATIVETEST";

    private final Context mContext;

    static {
        System.loadLibrary("javanativetestservice_jni");
    }

    public JavaNativeTestServiceImpl(Context context) {
        mContext = context;
    }

    public boolean getTimerBegin() {
        mContext.enforceCallingOrSelfPermission(JAVANATIVETEST_PERM, null);
        return nativeGetTimerBegin();
    }
    
    public void setTimer() {
        mContext.enforceCallingOrSelfPermission(JAVANATIVETEST_PERM, null);
        nativeSetTimer();
    }

    public void testExec() {
        mContext.enforceCallingOrSelfPermission(JAVANATIVETEST_PERM, null);
        nativeTestExec();
    }

    private static native boolean nativeGetTimerBegin();
    private static native void nativeSetTimer();
    private static native void nativeTestExec();
}