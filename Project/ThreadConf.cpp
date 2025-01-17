#include "ThreadConf.h"
#include "StateMonitor.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <cstdlib>
#include <ctime>

// Valores del tiempo de espera según la dificultad.
const int difficulty_delays[] = {1000, 700, 400}; // fácil, medio, difícil en milisegundos.
const int timeout_values[] = {5, 3, 1}; // fácil, medio, difíci en segundos.

extern int difficultyLevel;
extern int timeoutLevel;

std::vector<int> sequence;
int currentLevel = 0;

void show_sequence() {
    int show_delay = difficulty_delays[difficultyLevel];
    std::cout << "Mostrando secuencia: ";
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    for (int led : sequence) {
        std::cout << led << " ";
        switch (led) {
            case 0:
                outGPIO.setValue(GPIOuniv::HIGH);
                std::this_thread::sleep_for(std::chrono::milliseconds(show_delay));
                outGPIO.setValue(GPIOuniv::LOW);
                break;
            case 1:
                outGPIO1.setValue(GPIOuniv::HIGH);
                std::this_thread::sleep_for(std::chrono::milliseconds(show_delay));
                outGPIO1.setValue(GPIOuniv::LOW);
                break;
            case 2:
                outGPIO2.setValue(GPIOuniv::HIGH);
                std::this_thread::sleep_for(std::chrono::milliseconds(show_delay));
                outGPIO2.setValue(GPIOuniv::LOW);
                break;
            case 3:
                outGPIO3.setValue(GPIOuniv::HIGH);
                std::this_thread::sleep_for(std::chrono::milliseconds(show_delay));
                outGPIO3.setValue(GPIOuniv::LOW);
                break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    std::cout << std::endl;
}

bool get_player_input() {
    int timeout_per_led = timeout_values[timeoutLevel];
    for (int led : sequence) {
        bool correct = false;
        auto start_time = std::chrono::steady_clock::now();
        std::cout << "Esperando la entrada del jugador para el LED " << led << std::endl;
        while (std::chrono::steady_clock::now() - start_time < std::chrono::seconds(timeout_per_led)) {
            switch (led) {
                case 0:
                    if (inGPIO.getValue() == GPIOuniv::HIGH) {
                        outGPIO.setValue(GPIOuniv::HIGH);
                        correct = true;
                        std::cout << "El jugador ha presionado correctamente el pulsador para el LED " << led << std::endl;
                        while (inGPIO.getValue() == GPIOuniv::HIGH);
                        outGPIO.setValue(GPIOuniv::LOW);
                        break;
                    }
                    break;
                case 1:
                    if (inGPIO1.getValue() == GPIOuniv::HIGH) {
                        outGPIO1.setValue(GPIOuniv::HIGH);
                        correct = true;
                        std::cout << "El jugador ha presionado correctamente el pulsador para el LED " << led << std::endl;
                        while (inGPIO1.getValue() == GPIOuniv::HIGH);
                        outGPIO1.setValue(GPIOuniv::LOW);
                        break;
                    }
                    break;
                case 2:
                    if (inGPIO2.getValue() == GPIOuniv::HIGH) {
                        outGPIO2.setValue(GPIOuniv::HIGH);
                        correct = true;
                        std::cout << "El jugador ha presionado correctamente el pulsador para el LED " << led << std::endl;
                        while (inGPIO2.getValue() == GPIOuniv::HIGH);
                        outGPIO2.setValue(GPIOuniv::LOW);
                        break;
                    }
                    break;
                case 3:
                    if (inGPIO3.getValue() == GPIOuniv::HIGH) {
                        outGPIO3.setValue(GPIOuniv::HIGH);
                        correct = true;
                        std::cout << "El jugador ha presionado correctamente el pulsador para el LED " << led << std::endl;
                        while (inGPIO3.getValue() == GPIOuniv::HIGH);
                        outGPIO3.setValue(GPIOuniv::LOW);
                        break;
                    }
                    break;
            }
            if (correct) break;
        }
        if (!correct) {
            std::cout << "El jugador no ha presionado correctamente el LED " << led << std::endl;
            return false;
        }
    }
    return true;
}

void thread_start() {
    if (currentState == START || currentState == SHOW || currentState == INSERT) {
        std::cout << "Ejecutando hilo Start" << std::endl;
        sequence.clear();
        currentLevel = 1;
        sequence.push_back(rand() % 4);
        std::cout << "Juego iniciado en el nivel " << currentLevel << " con secuencia inicial" << std::endl;
        stateChanged = true;
    }
}

void thread_pause() {
    if (currentState == PAUSE) {
        std::cout << "Juego pausado" << std::endl;
        while (currentState == PAUSE) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        std::cout << "Reanudando juego" << std::endl;
    }
}

void thread_principal() {
    if (currentState == SHOW) {
        std::cout << "Hilo principal ejecutándose" << std::endl;
        show_sequence();
        currentState = INSERT;
        stateChanged = true;
    }
}

void thread_player() {
    if (currentState == INSERT) {
        std::cout << "Hilo del juegador ejecutándose" << std::endl;
        if (get_player_input()) {
            currentLevel++;
            sequence.push_back(rand() % 4);
            std::cout << "correcto, avanzando al nivel " << currentLevel << std::endl;
            currentState = SHOW;
        } else {
            std::cout << "incorrecto, reiniciando juego" << std::endl;
            currentLevel = 0;
            currentState = START;
        }
        stateChanged = true;
    }
}

void thread_sound() {
    if (currentState == START || currentState == SHOW || currentState == PAUSE) {
        std::cout << "Hilo de sonido ejecutándose" << std::endl;
    }
}
