#include <chrono>
#include <thread>
#include <signal.h>
#include "../algorithms/algorithms.h"
#include "../timer/timer.h"

using namespace std;

#define N_TEST 5

Timer *timer = new Timer();

void finish(int signum);

int main() {

    signal(SIGINT, finish);

    for(int i=0; i<=N_TEST; i++) {
        while(timer->getTimerBegin());

        if(i!=0)
            cout << "Começa o teste " << i << endl;
        else 
            cout << "Configurando Testes" << endl;

        //Início Chamada de Testes
        // this_thread::sleep_for(std::chrono::seconds(1s));
        //Fim da Chamada de Testes

        timer->setTimerEnd();
    }

    delete timer;
    return 0;
}

void finish(int signum) {
    delete timer;
    exit(signum);
}