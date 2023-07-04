#include <timer_lib.h>
#include <algorithms.h>
#include <log/log.h>
#include <math.h>

#define N_LOOP 100

void check_offset();
void qsort_call();
void dijkstra_call();
void fft_call();

static int pow10[7] = {
    1, 10, 100, 1000, 10000, 100000, 1000000
};

int main(int argc, char* argv[]) {

    ALOG(LOG_INFO, "NativeTestApp", "Application started");

    if(argc==0)
        check_offset();
    else
    switch (atoi(argv[1])) {
    case 1:
        ALOG(LOG_INFO, "NativeTestApp", "Calling Quick Sort Algorithm");
        qsort_call();
    break;
    case 2:
        ALOG(LOG_INFO, "NativeTestApp", "Calling Dijkstra Algorithm");
        dijkstra_call();
    break;    
    case 3:
        ALOG(LOG_INFO, "NativeTestApp", "Calling FFT Algorithm");
        fft_call();
    break;
    default:
        check_offset();
        break;
    }
    return 0;
}

void check_offset() {
    Timer timer;
    timer.reset();
    for(int i=1;i<=N_LOOP; i++){
            while(timer.isReady());

            timer.trigger(); //Timer ON
            timer.trigger(); //Timer OFF
    }
}
void qsort_call() {
    int arr_size;
    string file_path;
    Timer timer;
    timer.reset();

    for(int j=1; j<=6; j++) {
        for(int i=1;i<=N_LOOP; i++){
            
            arr_size = pow10[j];
            file_path = "sdcard/qsort_input_data/qsort_input_" + to_string(arr_size) + "_"+ to_string(i) +".txt";

            while(timer.isReady());

            ALOG(LOG_INFO, "NativeTestApp", "Starting Quick Sort on file %s", file_path.c_str());

            timer.trigger(); //Timer ON
            //Início Chamada de Testes
            qsortExec((char *) file_path.c_str(), arr_size);
            //Fim da Chamada de Testes
            timer.trigger(); //Timer OFF
            
            ALOG(LOG_INFO, "NativeTestApp", "Finished Quick Sort on file %s", file_path.c_str());
        }
        timer.reset();
    }
}

void dijkstra_call() {
    int graph_size;
    string file_path;
    Timer timer;
    timer.reset();
    for(int j=0; j<4; j++) {
        for(int i=1;i<=N_LOOP; i++){
            graph_size = (j==0)? 3 : pow10[j];
            file_path = "sdcard/dijkstra_input_data/dijkstra_input_" + to_string(graph_size) + "_"+ to_string(i) +".txt";

            while(timer.isReady());

            ALOG(LOG_INFO, "NativeTestApp", "Starting Dijkstra on file %s", file_path.c_str());

            timer.trigger(); //Timer ON
            //Início Chamada de Testes
            dijkstraExec((char *) file_path.c_str(), graph_size);
            //Fim da Chamada de Testes
            timer.trigger(); //Timer OFF
            
            ALOG(LOG_INFO, "NativeTestApp", "Finished Dijkstra  on file %s", file_path.c_str());
        }
        timer.reset();
    }
}

void fft_call(){
    Timer timer;
    static int Ntest[] = { 1<<3, 1<<10, 1<<13, 1<<17, 1<<20, -1 };

    timer.reset();
    for (int i = 0; Ntest[i] > 0; ++i) {

        while(timer.isReady());

        timer.trigger(); //Timer ON
        fftExec(Ntest[i]);
        timer.trigger(); //Timer OFF
    }
}
