package vendor.alvenan.javanativetestapp;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.widget.Toast;

import vendor.alvenan.javanativetestapp.IJavaNativeTestApp;
import vendor.alvenan.timermanager.TimerManager;

public class MainActivity extends AppCompatActivity {
    private final static int N_TEST = 10;
    private JavaNativeTestAppImpl jniFuncs = new JavaNativeTestAppImpl();
    private TimerManager timer = TimerManager.getInstance();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        Log.i("JavaNativeTestApp: Java", "Application started");

        // Example of a call to a native method
        try {
            for (int i=0; i<N_TEST; i++) {
                while (timer.isReady()) ;
                Log.i("JavaNativeTestApp: Java", "Starting algorithm test Nº" + String.valueOf(i));

                timer.trigger();  //Timer ON
                //Início Chamada de Testes
                jniFuncs.algorithmExec();
                //Fim da Chamada de Testes
                timer.trigger(); //Timer OFF
            }
            timer.reset(); 
        } catch (android.os.RemoteException e) {
                Toast.makeText(this, "Error when tring to access Binder!", Toast.LENGTH_LONG).show();
                Log.e("JavaNativeTestApp: Java", "Error when tring to access Binder!");
        }
        MainActivity.this.finish();
        System.exit(0);
    }
}

class JavaNativeTestAppImpl extends IJavaNativeTestApp.Stub {
    static {
        System.loadLibrary("javanativetestapp");
    }
    public native void algorithmExec();
}