#include <chrono>
#include <thread>
#include <timer.h>

#define N_TEST 5

int main() {

    Timer *timer = new Timer();

    keyboardExit(0, timer);
    signal(SIGINT, (void (*)(int))keyboardExit);

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