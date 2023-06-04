package vendor.alvenan.javanativetestservice;

import android.content.Context;
import android.util.Log;
import java.util.concurrent.TimeUnit;

class JavaNativeTestServiceImpl extends IJavaNativeTestService.Stub {
    public static final String JAVANATIVETEST_PERM = 
        "vendor.alvenan.javanativetestservice.permission.JAVANATIVETEST";

    private final Context mContext;

    static {
        Log.i("JavaNativeTestServiceImpl", "Loading library...7");
        // try {
        //     Log.i("JavaNativeTestServiceImpl", "Waiting 10 seconds to debug...");
        //     TimeUnit.SECONDS.sleep(10);
        // } catch (Exception e) {
        //     Log.e("JavaNativeTestServiceImpl", "Catch Exception");
        // }    
        System.loadLibrary("javanativetestservice_jni");
    }

    public JavaNativeTestServiceImpl(Context context) {
        Log.i("JavaNativeTestServiceImpl", "Giving context...");
        mContext = context;
    }

    public void algorithmExec() {
        mContext.enforceCallingOrSelfPermission(JAVANATIVETEST_PERM, null);
        nativeAlgorithmExec();
    }

    private static native void nativeAlgorithmExec();
}