# STM32G474RET3 UART transmission library 

## Important informations

- The main function of the project can be found in `Core/Src/main.c`.
- Other functions related to UART communication are located in the `Libraries/UART_Library/Src/uart_protocol_library.c`.

## Description

This project is an STM32CubeIDE-based application that demonstrates UART communication. It provides a library for UART frame transmission and reception, and it includes example code for sending and receiving frames.

## Getting Started

To get started with this project, follow the instructions below.

### Prerequisites

You'll need the following:

- STM32CubeIDE installed
- An STM32 development board (e.g., Nucleo, Discovery)
- USB-to-UART adapter (if your board doesn't have USB UART)
- Terminal software (e.g., PuTTY, Tera Term)

### Installation

1. Clone or download this repository (`uart_library`).
2. Open the project in STM32CubeIDE.
3. Build the project.
4. Flash the firmware to your STM32 board.

### Example

Show an example of how to use your project. You can include a code snippet here.

```c
#include "main.h"
#include "uart_protocol_library.h"

UART_HandleTypeDef huart2;

int main(void) {

	HAL_Init();

	SystemClock_Config();

	MX_GPIO_Init();
	MX_USART2_UART_Init();

	UART_Init(&huart2);

  // Inside this for loop you can test UART
	while (1) {
		uint8_t data_to_send[] = { 0x01, 0x02, 0x03 };
		UART_SendFrame(&huart2, 0x10, sizeof(data_to_send), data_to_send);

		// Example of receiving a frame
		uint8_t received_id, received_len;
		uint8_t received_payload[8];
		bool frame_received = UART_ReceiveFrame(&huart2, &received_id,
				&received_len, received_payload);

		if (frame_received) {
			callback(received_len, received_payload);
		}
	}
}
```
