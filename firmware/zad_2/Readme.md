# STM32G474RET3 RGB LED Control with HAL

## Important informations

- The main function of the project can be found in `Core/Src/main.c`.

## Description

This project is designed for the STM32G474RET3 microcontroller and demonstrates control of an RGB LED using the HAL library. After programming the microcontroller, the RGB LED will exhibit the following behaviors:

- The red (R) LED will change its intensity sinusoidally.
- The green (G) LED will change its intensity in a sawtooth pattern.
- The blue (B) LED will change its intensity in a triangular pattern.

All these intensity patterns complete one cycle in approximately 2 seconds (T = 2s).

## Getting Started

To get started with this project, follow the instructions below.

### Prerequisites

You'll need the following:

- STM32CubeIDE installed
- An STM32 development board (e.g., Nucleo, Discovery)
- USB-to-UART adapter (if your board doesn't have USB UART)
- Terminal software (e.g., PuTTY, Tera Term)

### Installation

1. Clone or download this repository (`led_lighting`).
2. Open the project in STM32CubeIDE.
3. Build the project.
4. Flash the firmware to your STM32 board.
