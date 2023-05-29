#include <iostream>
#include <timer_lib.h>

#define N_TEST 5

int main() {

    Timer timer;

    for(int i=0; i<=N_TEST; i++) {
        while(timer.getTimerBegin());

        cout << "Começa o teste " << i << endl;
        timer.setTimer();

        //Início Chamada de Testes
        //Fim da Chamada de Testes

        timer.setTimer();
    }
    return 0;
}