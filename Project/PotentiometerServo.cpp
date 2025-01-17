#include "PotentiometerServo.h"
#include "ADC.h"
#include "PWMuniv.h"
#include <thread>
#include <chrono>

using namespace BBB;

bool servosEnabled = true; // Habilitar servomotores.

int difficultyServoValue = 0;
int timeoutServoValue = 0;

void control_servo() {
    // Inicialización de servomotores y de potenciómetros.
    PWM pwm1(PWM::P9_14); // P9_14
    PWM pwm2(PWM::P9_22); // P9_22
    ADC adcCH0(0); // Potenciómetro 1 P9_39 AIN0
    ADC adcCH1(1); // Potenciómetro 2 P9_40 AIN1

    // Rangos de los duty-cycles de los servomotores.
    unsigned min_duty_cycle1 = 450000;
    unsigned max_duty_cycle1 = 2400000;
    unsigned min_duty_cycle2 = 580000;
    unsigned max_duty_cycle2 = 2600000;

    // Inicializar valores previos de los potenciómetros
    int prev_adc_value0 = adcCH0.readAnalog();
    int prev_adc_value1 = adcCH1.readAnalog();

    pwm1.setPolarity(PWM::ACTIVE_HIGH);
    pwm1.setPeriod(20000000);
    pwm1.run();

    pwm2.setPolarity(PWM::ACTIVE_HIGH);
    pwm2.setPeriod(20000000);
    pwm2.run();

    while (servosEnabled) {
        int adc_value0 = adcCH0.readAnalog();
        int adc_value1 = adcCH1.readAnalog();

        if (adc_value0 != prev_adc_value0) {
            // Invertir el valor del potenciómetro 1. Es para que gire en el sentido correcto.
            int inverted_adc_value0 = 4095 - adc_value0;

            // Calcular el nuevo duty-cycle según los valores mínimo y máximo.
            double aval_pu0 = (double)inverted_adc_value0 / 4095.0;
            unsigned duty_cycle1 = min_duty_cycle1 + aval_pu0 * (max_duty_cycle1 - min_duty_cycle1);

            pwm1.setDutyCycle(duty_cycle1);
            difficultyServoValue = adc_value0;
            prev_adc_value0 = adc_value0;
        }

        if (adc_value1 != prev_adc_value1) {
        	// Invertir el valor del potenciómetro 2. Es para que gire en el sentido correcto.
        	int inverted_adc_value1 = 4095 - adc_value1;

            // Calcular el nuevo duty-cycle según los valores mínimo y máximo.
            double aval_pu1 = (double)inverted_adc_value1 / 4095.0;
            unsigned duty_cycle2 = min_duty_cycle2 + aval_pu1 * (max_duty_cycle2 - min_duty_cycle2);


            pwm2.setDutyCycle(duty_cycle2);
            timeoutServoValue = adc_value1;
            prev_adc_value1 = adc_value1;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    pwm1.stop();
    pwm2.stop();
}
