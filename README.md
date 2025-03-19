# Simon Game Project

## Overview
This project is an implementation of the classic "Simon" game using a BeagleBone Black (BBB) embedded system. Players must replicate an increasingly complex sequence of colored lights, with the game providing auditory and visual feedback. The project emphasizes concurrent programming, GPIO management, and analog/digital I/O integration.

## Features

- **Game Logic**:
  - Four colored LEDs represent the game sequence.
  - Players interact via buttons corresponding to each LED.
  - Levels increase in complexity, with adjustable difficulty.
- **Controls**:
  - Start, Pause, and Level controls via dedicated buttons.
  - Two potentiometers configure game speed and timeout durations.
  - Servos indicate the current settings for speed and timeout.

## Hardware Components

- **BeagleBone Black**: Main embedded system.
- **Inputs**:
  - 1 Start button.
  - 1 Pause button.
  - 4 game buttons (one for each LED).
  - 2 potentiometers for difficulty adjustments.
- **Outputs**:
  - 4 LEDs (green, yellow, red, blue) for sequence display.
  - 2 servos for difficulty indication.
- **Additional**:
  - Transistors, resistors, and connecting cables.
  - Plastic base for assembly and cable organization.
 
 ## Challenges and Solutions

- **Overloading Risk**: Managed by frequent voltage monitoring and ensuring a common ground for all components.
- **State Transition Timing**: Optimized delays and robust verification of state transitions.
- **GPIO Management**: Ensured efficient and conflict-free pin usage.
