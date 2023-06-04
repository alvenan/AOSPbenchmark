package vendor.alvenan.javanativetestservice;

import android.app.Application;
import android.os.ServiceManager;
import android.util.Log;

public class JavaNativeTestService extends Application {
    private static final String SERVICE_NAME = "vendor.alvenan.javanativetest";
    private JavaNativeTestServiceImpl serviceImpl;

    public void onCreate() {
        super.onCreate();
        Log.i("JavaNativeTestService", "Starting service...");
        serviceImpl = new JavaNativeTestServiceImpl(getApplicationContext());
        ServiceManager.addService(SERVICE_NAME, serviceImpl);
    }

    public void onTerminate() {
        super.onTerminate();
    }
}