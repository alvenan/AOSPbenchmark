package vendor.alvenan.javanativetestapp;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.widget.Toast;
import android.os.IBinder;

import vendor.alvenan.javanativetestapp.IJavaNativeTestApp;
import vendor.alvenan.timermanager.TimerManager;

public class MainActivity extends AppCompatActivity {
    private JavaNativeTestAppImpl jniFunc;
    private TimerManager timer = TimerManager.getInstance();
    private final static int N_TEST = 100;
    Handler handler = new Handler();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        jniFunc = new JavaNativeTestAppImpl();
        Log.i("JavaNativeTestApp", "Application started");

        // Example of a call to a native method
        for (int i=0; i<N_TEST; i++) {
            try {

                while (timer.isReady()) ;
                Log.i("JavaNativeTestApp", "Comaça o teste " + String.valueOf(i));

                timer.trigger();
                jniFunc.algorithmExec();
                timer.trigger();

            } catch (android.os.RemoteException e) {
                Toast.makeText(this, "Error when tring to access Binder!", Toast.LENGTH_LONG).show();
                Log.e("JavaNativeTestApp", "Error when tring to access Binder!");
            }
        }
        MainActivity.this.finish();
        System.exit(0);
    }
}