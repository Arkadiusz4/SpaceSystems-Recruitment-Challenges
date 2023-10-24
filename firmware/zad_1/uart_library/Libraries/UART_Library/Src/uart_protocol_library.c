#include <stdio.h>
#include <stdbool.h>
#include "stm32g4xx_hal.h"
#include "uart_protocol_library.h"

// Initialing UART
void UART_Init(UART_HandleTypeDef *huart) {
	huart->Instance = USART1;
	huart->Init.BaudRate = 115200;
	huart->Init.WordLength = UART_WORDLENGTH_8B;
	huart->Init.Parity = UART_PARITY_NONE;
	huart->Init.StopBits = UART_STOPBITS_1;
	huart->Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart->Init.Mode = UART_MODE_TX_RX;

	if (HAL_UART_Init(huart) != HAL_OK) {
		printf("Cannot initialize UART \n");
		return HAL_ERROR;
	}

	retrun HAL_OK;
}

// Sending frame by UART
void UART_SendFrame(UART_HandleTypeDef *huart, uint8_t id, uint8_t len,
		uint8_t *payload) {
	uint8_t txBuffer[8]; // Buffer for the frame
	uint16_t frameLength = len + 3; // Frame length

	if (frameLength > sizeof(txBuffer)) {
		printf("Error: Frame too large to send\n");
		return;
	}

	txBuffer[0] = 0x3C; // START byte
	txBuffer[1] = id;	// ID byte
	txBuffer[2] = len;	// LENGTH byte

	// Copying the payload to the frame buffer
	for (int i = 0; i < len; i++) {
		txBuffer[i + 3] = payload[i];
	}

	// Send the frame by UART
	if (HAL_UART_Transmit(huart, txBuffer, frameLength, HAL_MAX_DELAY)
			!= HAL_OK) {
		int maxRetries = 3;
		int retries = 0;

		while (retries < maxRetries) {
			if (HAL_UART_Transmit(huart, txBuffer, frameLength, HAL_MAX_DELAY)
					== HAL_OK) {
				break;
			}
			retries++;
		}

		if (retries == maxRetries) {
			printf("UART transmission error\n");
		}
	}
}

// Receiving frame by UART
bool UART_ReceiveFrame(UART_HandleTypeDef *huart, uint8_t *id, uint8_t *len,
		uint8_t *payload) {
	uint8_t rxBuffer[8]; // Frame size
	uint8_t startByte = 0x3C;

	// Waiting for the start byte
	while (1) {
		HAL_UART_Receive(huart, rxBuffer, 1, HAL_MAX_DELAY); // Receiving one byte

		if (rxBuffer[0] == startByte) {
			break;  // Founded start byte
		}
	}

	// Receiving ID and length
	HAL_UART_Receive(huart, rxBuffer + 1, 2, HAL_MAX_DELAY);

	*id = rxBuffer[1];
	*len = rxBuffer[2];

	// Receiving payload
	HAL_UART_Receive(huart, rxBuffer + 3, *len, HAL_MAX_DELAY);

	// If frame is correct, copy the payload
	if (rxBuffer[1] == *id && rxBuffer[2] == *len) {
		for (int i = 0; i < *len; i++) {
			payload[i] = rxBuffer[i + 3];
		}

		callback(*len, payload);

		return true;
	}

	return false;
}

// Handle USART interruptions (optional function, it's hard to test without physical board :( )
void USART2_IRQHandler() {
	if (LL_USART_IsActiveFlag_RXNE(USART2)) {
		// Receive a single byte from UART
		uint8_t receivedByte = LL_USART_ReceiveData8(USART2);

		// Call the UART_ReceiveFrame function to process the received frame
		uint8_t id, len;
		uint8_t payload[8];
		bool frameReceived = UART_ReceiveFrame(&id, &len, payload,
				receivedByte);

		if (frameReceived) {
			// The frame was successfully received
			callback(*len, payload);
		}
	}
}

void callback(uint8_t len, uint8_t *payload) {
	switch (payload[0]) {
	case MOTOR_SET_MODE_ID:
		motor_set_mode(len - 1, payload + 1);
		break;
	case MOTOR_SET_SPEED_ID:
		motor_set_speed(len - 1, payload + 1);
		break;
	case MOTOR_SET_POS_ID:
		motor_set_pos(len - 1, payload + 1);
		break;
	default:
		printf("Error: Unknown frame identifier\n");
		break;
	}
}

void motor_set_mode(uint8_t len, uint8_t *payload) {
	if (len != 1) {
		printf("Error: Invalid frame length for MOTOR_SET_MODE\n");
		return;
	}

	uint8_t mode = payload[0];
	printf("Received MOTOR_SET_MODE frame. Mode: %d\n", mode);
}

void motor_set_speed(uint8_t len, uint8_t *payload) {
	if (len != 3) {
		printf("Error: Invalid frame length for MOTOR_SET_SPEED\n");
		return;
	}
	uint8_t speed = payload[0];
	uint8_t param1 = payload[1];
	uint8_t param2 = payload[2];

	printf(
			"Received MOTOR_SET_SPEED frame. Speed: %d, Param1: %d, Param2: %d\n",
			speed, param1, param2);
}

void motor_set_pos(uint8_t len, uint8_t *payload) {
	if (len != 5) {
		printf("Error: Invalid frame length for MOTOR_SET_POS\n");
		return;
	}

	uint8_t position = payload[0];
	uint8_t param1 = payload[1];
	uint8_t param2 = payload[2];
	uint8_t param3 = payload[3];
	uint8_t param4 = payload[4];

	printf(
			"Received MOTOR_SET_POS frame. Position: %d, Param1: %d, Param2: %d, Param3: %d, Param4: %d\n",
			position, param1, param2, param3, param4);
}

