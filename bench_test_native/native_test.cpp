#include <chrono>
#include <thread>
#include <signal.h>
#include "../timer/timer.h"
#include "../algorithms/algorithms.h"

#define N_TEST 5

int main() {

    Timer *timer = new Timer();
    signal(SIGINT, (void (*)(int))keyboardExit);
    keyboardExit(0, timer);

    for(int i=0; i<=N_TEST; i++) {
        while(timer->getTimerBegin());

        if(i==0)
            cout << "Configurando Testes" << endl;
        else
            cout << "Começa o teste " << i << endl;

        //Início Chamada de Testes
        // this_thread::sleep_for(std::chrono::seconds(1s));
        //Fim da Chamada de Testes

        timer->setTimerEnd();
    }

    delete timer;
    return 0;
}