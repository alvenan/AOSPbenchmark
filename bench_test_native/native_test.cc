#include <iostream>
#include <timer_lib.h>

#define N_TEST 5

int main() {

    Timer timer;

    for(int i=0; i<=N_TEST; i++) {
        while(timer.isReady());

        cout << "Começa o teste " << i << endl;
        timer.trigger(); //Timer ON

        //Início Chamada de Testes
        //Fim da Chamada de Testes

        timer.trigger(); //Timer OFF
    }
    return 0;
}