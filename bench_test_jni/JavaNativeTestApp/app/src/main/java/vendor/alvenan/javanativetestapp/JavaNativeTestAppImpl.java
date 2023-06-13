package vendor.alvenan.javanativetestapp;

class JavaNativeTestAppImpl extends IJavaNativeTestApp.Stub {
    static {
        System.loadLibrary("javanativetestapp");
    }
    public native void algorithmExec();
}