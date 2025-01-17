#ifndef STATEMONITOR_H
#define STATEMONITOR_H
#include "GPIOuniv.h"

enum State { START, SHOW, INSERT, PAUSE };
extern volatile State currentState;
extern volatile bool stateChanged;

using namespace BBB;

void setupGPIO();
void check_buttons();
int calculate_pot_level(int pot_value, int num_intervals);

extern GPIOuniv outGPIO;
extern GPIOuniv outGPIO1;
extern GPIOuniv outGPIO2;
extern GPIOuniv outGPIO3;
extern GPIOuniv inGPIO;
extern GPIOuniv inGPIO1;
extern GPIOuniv inGPIO2;
extern GPIOuniv inGPIO3;
extern GPIOuniv startGPIO;
extern GPIOuniv pauseGPIO;

#endif
