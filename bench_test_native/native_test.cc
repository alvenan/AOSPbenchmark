#include <iostream>
#include <timer.h>

#define N_TEST 5

int main() {

    Timer *timer = new Timer();

    for(int i=0; i<=N_TEST; i++) {
        while(timer->getTimerBegin());

        cout << "Começa o teste " << i << endl;

        //Início Chamada de Testes
        //Fim da Chamada de Testes

        timer->setTimerEnd();
    }

    delete timer;
    return 0;
}