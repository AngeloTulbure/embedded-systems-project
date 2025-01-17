#include <iostream>
#include <thread>
#include <chrono>
#include "StateMonitor.h"
#include "ThreadConf.h"
#include "PotentiometerServo.h"

void state_machine() {
    while (true) {
        if (stateChanged) {
            stateChanged = false;
            switch (currentState) {
                case START:
                    thread_start();
                    break;
                case SHOW:
                    thread_principal();
                    break;
                case INSERT:
                    thread_player();
                    break;
                case PAUSE:
                    thread_pause();
                    break;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main() {
    setupGPIO();
    srand(time(0)); // Semilla para la genereación aleatoria en la secuencia
    std::thread buttonThread(check_buttons);
    std::thread servoThread(control_servo);
    std::thread(state_machine).detach();

    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    buttonThread.join();
    servoThread.join();
    return 0;
}
