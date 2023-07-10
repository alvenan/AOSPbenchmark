package vendor.alvenan.javanativetestapp;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.widget.Toast;
import android.view.View;
import android.widget.Button;

import vendor.alvenan.javanativetestapp.IJavaNativeTestApp;
import vendor.alvenan.timermanager.TimerManager;

public class MainActivity extends AppCompatActivity {

    private final static int N_LOOP = 100;
    private JavaNativeTestAppImpl jniFuncs = new JavaNativeTestAppImpl();
    private TimerManager timer = TimerManager.getInstance();
    private static int[] pow10 = {1, 10, 100, 1000, 10000, 100000, 1000000};
    private static int[] Ntest = { 64, 96, 128, 160, 192, 256, 384, 480, 512, 640, 768, 800, 1024, 2048, 2400, 4096, 8192, 9216, 16384, 32768, 262144, 1048576, -1 };

    private Button qsortBtn, dijksBtn, fftBtn, secBtn, offsetBtn, closeApp;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        qsortBtn = (Button) findViewById(R.id.button);
        dijksBtn = (Button) findViewById(R.id.button2);
        fftBtn = (Button) findViewById(R.id.button3);
        secBtn = (Button) findViewById(R.id.button4);
        offsetBtn = (Button) findViewById(R.id.button5);
        closeApp = (Button) findViewById(R.id.button6);

        qsortBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                qsortCall();
            }
        });

        dijksBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                dijkstraCall();
            }
        });

        fftBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                fftCall();
            }
        });

        secBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                rsaCall();
            }
        });

        offsetBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                checkOffset();
            }
        });

        closeApp.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                MainActivity.this.finish();
                System.exit(0);
            }
        });

        Log.i("JavaNativeTestApp", "Application started");
    }

    private void checkOffset() {
        try {
            timer.reset(); 
            for(int i=1;i<=N_LOOP;i++) {
                while (!timer.isReady());
                timer.trigger();  //Timer ON
                timer.trigger(); //Timer OFF      
            }
        } catch (android.os.RemoteException e) {
                Toast.makeText(this, "Error when tring to access Binder!", Toast.LENGTH_LONG).show();
                Log.e("JavaNativeTestApp: Java", "Error when tring to access Binder!");
        }
    }
    private void qsortCall() {
        String file_path;
        int arr_size;
        try {
            timer.reset();
            for (int j=1; j<=6; j++) {
                for(int i=1;i<=N_LOOP;i++) {

                    arr_size = pow10[j];
                    file_path = "sdcard/input_data/qsort_input_" + Integer.toString(arr_size) + "_"+ Integer.toString(i) +".txt";

                    while (!timer.isReady()) ;

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
            timer.reset(); 
            for (int j=0; j<=3; j++) {
                for(int i=1;i<=N_LOOP;i++) {
                    graph_size = (j==0) ? 3 : pow10[j];
                    file_path = "sdcard/dijkstra_input_data/dijkstra_input_" + Integer.toString(graph_size) + "_"+ Integer.toString(i) +".txt";

                    while (!timer.isReady());

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

    private void fftCall() {
        String file_path;
        int graph_size;
        try {
            timer.reset();

            for (int i = 0; Ntest[i] > 0; ++i) {

                while(!timer.isReady());
        
                timer.trigger(); //Timer ON
                Log.i("JavaNativeTestApp: Java", "Antes de chamar FFT");
                jniFuncs.fftExec(Ntest[i]);
                Log.i("JavaNativeTestApp: Java", "Depois de chamar FFT");
                timer.trigger(); //Timer OFF
            }
            timer.reset();

        } catch (android.os.RemoteException e) {
                Toast.makeText(this, "Error when tring to access Binder!", Toast.LENGTH_LONG).show();
                Log.e("JavaNativeTestApp: Java", "Error when tring to access Binder!");
        }
    }


    private void rsaCall(){
        String file_path;
        int str_size;
        try {
            timer.reset();

            for(int j=1; j<=7; j++) {
                for(int i=1;i<=N_LOOP; i++){
                    str_size = pow10[j];
                    file_path = "sdcard/rsa_input_data/rsa_input_" + Integer.toString(str_size) + "_"+ Integer.toString(i) +".txt";
        
                    while(!timer.isReady());
                    Log.i("JavaNativeTestApp: Java", "Starting RSA on file " + file_path);
        
                    timer.trigger(); //Timer ON
                    jniFuncs.rsaExec(file_path);
                    timer.trigger(); //Timer OFF
        
                    Log.i("JavaNativeTestApp: Java", "Finished RSA on file " + file_path);
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
    public native void fftExec(int N);
    public native void rsaExec(String input_path);
}