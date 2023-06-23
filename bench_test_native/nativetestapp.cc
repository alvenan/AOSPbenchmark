#include <iostream>
#include <timer_lib.h>
#include <algorithms.h>

#define N_TEST 10

int main() {

    Timer timer;

    for(int i=0; i<N_TEST; i++) {
        while(timer.isReady());

        cout << "Starting algorithm test Nº" << i << endl;
        timer.trigger(); //Timer ON

        //Início Chamada de Testes
        cout << testfunc() << endl;
        //Fim da Chamada de Testes

        timer.trigger(); //Timer OFF
    }
    timer.reset();
    return 0;
}