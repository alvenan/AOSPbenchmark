package vendor.alvenan.javanativetestapp;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.widget.Toast;

import vendor.alvenan.javanativetestapp.IJavaNativeTestApp;
import vendor.alvenan.timermanager.TimerManager;

public class JavaNativeActivity extends AppCompatActivity {
    private final static int N_LOOP = 100;
    private JavaNativeTestAppImpl jniFuncs = new JavaNativeTestAppImpl();
    private TimerManager timer = TimerManager.getInstance();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        Log.i("JavaNativeTestApp", "Application started");
        // qsortCall();
        dijkstraCall();

        JavaNativeActivity.this.finish();
        System.exit(0);
    }

    private void qsortCall() {
        String file_path;
        int arr_size;
        try {
            for(int i=1;i<=N_LOOP;i++) {
                for (int j=1; j<=6; j++) {

                    arr_size = (int)Math.pow(10,j);
                    file_path = "sdcard/input_data/qsort_input_" + Integer.toString(arr_size) + "_"+ Integer.toString(i) +".txt";

                    while (timer.isReady()) ;

                    Log.i("JavaNativeTestApp", "Starting Quick Sort on file" + file_path);

                    timer.trigger();  //Timer ON
                    //Início Chamada de Testes
                    jniFuncs.qsortExec(file_path, arr_size);
                    //Fim da Chamada de Testes
                    timer.trigger(); //Timer OFF
                    
                    Log.i("JavaNativeTestApp", "Finished Quick Sort on file" + file_path);
                }
                timer.reset(); 
            }
        } catch (android.os.RemoteException e) {
                Toast.makeText(this, "Error when tring to access Binder!", Toast.LENGTH_LONG).show();
                Log.e("JavaNativeTestApp: Java", "Error when tring to access Binder!");
        }
    }

    private void dijkstraCall() {
        String file_path;
        int graph_size;
        try {
            for(int i=1;i<=N_LOOP;i++) {
                for (int j=0; j<=3; j++) {

                    graph_size = (j==0) ? 3 : (int)Math.pow(10,j);
                    file_path = "sdcard/dijkstra_input_data/dijkstra_input_" + Integer.toString(graph_size) + "_"+ Integer.toString(i) +".txt";

                    while (timer.isReady());

                    Log.i("JavaNativeTestApp", "Starting Dijkstra on file " + file_path);

                    timer.trigger();  //Timer ON
                    //Início Chamada de Testes
                    jniFuncs.dijkstraExec(file_path, graph_size);
                    //Fim da Chamada de Testes
                    timer.trigger(); //Timer OFF
                    
                    Log.i("JavaNativeTestApp", "Finished Dijkstra on file " + file_path);
                }
                timer.reset(); 
            }
        } catch (android.os.RemoteException e) {
                Toast.makeText(this, "Error when tring to access Binder!", Toast.LENGTH_LONG).show();
                Log.e("JavaNativeTestApp: Java", "Error when tring to access Binder!");
        }
    }
}

class JavaNativeTestAppImpl extends IJavaNativeTestApp.Stub {
    static {
        System.loadLibrary("javanativetestapp");
    }
    public native void qsortExec(String input_path, int arr_size);
    public native void dijkstraExec(String input_path, int graph_size);
}