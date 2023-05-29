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

    public boolean timerIsReady() {
        mContext.enforceCallingOrSelfPermission(JAVANATIVETEST_PERM, null);
        return nativeTimerIsReady();
    }
    
    public void timerTrigger() {
        mContext.enforceCallingOrSelfPermission(JAVANATIVETEST_PERM, null);
        nativeTimerTrigger();
    }

    public void algorithmExec() {
        mContext.enforceCallingOrSelfPermission(JAVANATIVETEST_PERM, null);
        nativeAlgorithmExec();
    }

    private static native boolean nativeTimerIsReady();
    private static native void nativeTimerTrigger();
    private static native void nativeAlgorithmExec();
}