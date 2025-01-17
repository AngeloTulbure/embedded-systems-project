#include "StateMonitor.h"
#include "PotentiometerServo.h"
#include <chrono>
#include <thread>
#include <iostream>

volatile State currentState = START;
volatile bool stateChanged = false;
using namespace BBB;

GPIOuniv outGPIO(GPIOuniv::P9_12); // GPIO60 1º led verde
GPIOuniv outGPIO1(GPIOuniv::P9_23); // GPIO49 2º led amarillo
GPIOuniv outGPIO2(GPIOuniv::P9_30); // GPIO112 3º led rojo
GPIOuniv outGPIO3(GPIOuniv::P9_27); // GPIO115 4º led azul

GPIOuniv inGPIO(GPIOuniv::P9_15); // GPIO48 1º botón verde
GPIOuniv inGPIO1(GPIOuniv::P9_41); // GPIO20 2º botón amarillo
GPIOuniv inGPIO2(GPIOuniv::P8_16); // GPIO46 3º botón rojo
GPIOuniv inGPIO3(GPIOuniv::P8_18); // GPIO65 4º botón azul

GPIOuniv startGPIO(GPIOuniv::P8_12); // GPIO44 botón start
GPIOuniv pauseGPIO(GPIOuniv::P8_14); // GPIO26 botón pausa

// Variables para los valores de los potenciómetros y umbrales de dificultad y timeout.
extern int difficultyServoValue;
extern int timeoutServoValue;
int difficultyLevel = 0; // 0: fácil, 1: medio, 2: difícil
int timeoutLevel = 0; // 0: fácil, 1: medio, 2: difícil

void setupGPIO() {
    // Configurar los pines
    std::cout << "Configuración de GPIOs completa" << std::endl;
}

void check_buttons() {
    while (true) {
        if (startGPIO.getValue() == GPIOuniv::HIGH) {
            if (currentState == START) {

                difficultyLevel = calculate_pot_level(difficultyServoValue, 3);
                timeoutLevel = calculate_pot_level(timeoutServoValue, 3);

                servosEnabled = false; // Queremos leer el valor de los potenciómetros para establecer la dificultad solo al principio.
                currentState = SHOW;
                stateChanged = true;
                std::cout << "Pulsador START presionado, cambiando estado a SHOW" << std::endl;
            }
        }
        if (pauseGPIO.getValue() == GPIOuniv::HIGH) {
            if (currentState != START) {
                if (currentState == PAUSE) {
                    currentState = SHOW;
                    std::cout << "Pulsador PAUSE presionado, reanudando juego en estado SHOW" << std::endl;
                } else {
                    currentState = PAUSE;
                    std::cout << "Pulsador pause presionado, reanudando juego" << std::endl;
                }
                stateChanged = true;
            }
        }
        // Lógica para que si se presiona un botón, se encienda la luz correspondiente.
        if (currentState == INSERT) {
            if (inGPIO.getValue() == GPIOuniv::HIGH) {
                outGPIO.setValue(GPIOuniv::HIGH);
            } else {
                outGPIO.setValue(GPIOuniv::LOW);
            }
            if (inGPIO1.getValue() == GPIOuniv::HIGH) {
                outGPIO1.setValue(GPIOuniv::HIGH);
            } else {
                outGPIO1.setValue(GPIOuniv::LOW);
            }
            if (inGPIO2.getValue() == GPIOuniv::HIGH) {
                outGPIO2.setValue(GPIOuniv::HIGH);
            } else {
                outGPIO2.setValue(GPIOuniv::LOW);
            }
            if (inGPIO3.getValue() == GPIOuniv::HIGH) {
                outGPIO3.setValue(GPIOuniv::HIGH);
            } else {
                outGPIO3.setValue(GPIOuniv::LOW);
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

// Funciones para calcular el nivel a partir del valor del potenciómetro.
int calculate_pot_level(int pot_value, int num_intervals) {
    int interval_size = 4095 / num_intervals;
    return pot_value / interval_size;
}
