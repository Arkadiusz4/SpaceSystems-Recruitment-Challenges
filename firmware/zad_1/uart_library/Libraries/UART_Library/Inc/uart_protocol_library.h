#include <stdbool.h>
#ifndef UART_PROTOCOL_LIBRARY_H
#define UART_PROTOCOL_LIBRARY_H

#define MOTOR_SET_MODE_ID   0x11
#define MOTOR_SET_SPEED_ID  0x12
#define MOTOR_SET_POS_ID    0x13

// Initialize UART
void UART_Init(UART_HandleTypeDef *huart) {};

// Send a frame via UART
void UART_SendFrame(UART_HandleTypeDef *huart, uint8_t id, uint8_t len,
		uint8_t *payload) {};

// Receive a frame via UART
bool UART_ReceiveFrame(UART_HandleTypeDef *huart, uint8_t *id, uint8_t *len, uint8_t *payload) {};

// USART2 interrupt handler (now it is nowhere used)
void USART2_IRQHandler() {};

// Callback for processing received frames
void callback(uint8_t len, uint8_t* payload) {};

#endif /* UART_PROTOCOL_LIBRARY_H */

