#include <chrono>
#include <thread>
#include "../algorithms/algorithms.h"
#include "../timer/timer.h"

using namespace std;

#define N_TEST 5

int main() {
    Timer *timer = new Timer();

    for(int i=0; i<N_TEST; i++) {
        while(timer->getTimerBegin());

        //Início Chamada de Testes
        cout << "Saiu do While" << endl;
        std::this_thread::sleep_for(std::chrono::seconds(2s));
        //Fim da Chamada de Testes

        timer->setTimerEnd();
    }
    return 0;
}