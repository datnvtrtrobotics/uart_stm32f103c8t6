/*
 * uart_f103.c
 *
 *  Created on: Jul 11, 2024
 *      Author: tdat
 */
#include "uart.h"
#include "stm32f1xx_hal.h"
#include "uart_f103.h"

//UART_HandleTypeDef huart1;
//UART_HandleTypeDef huart2;
//UART_HandleTypeDef huart3;

//  huart1 = uart1.huart;
//  huart2 = uart2.huart;
//  huart3 = uart3.huart;
int write_byte ;
uint8_t receivedData;
//#define BUFFER_SIZE 128
//char rx_buffer[BUFFER_SIZE];
uint16_t buffer_index = 0;

void Config_uart(){
UART_Config uartConfig;
uartConfig.baudRate = 115200;
uartConfig.wordLength = UART_WORDLENGTH_8B;
uartConfig.stopBits = UART_STOPBITS_1;
uartConfig.parity = UART_PARITY_NONE;

if (init(&uart1.huart, uartConfig) != 0) {
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
    // Xử lý lỗi
}
}
CircularBuffer rxBuffer = { {0}, 0, 0 };
void CircularBuffer_Write(CircularBuffer *cb, uint8_t data) {
    uint16_t next = (cb->head + 1) % BUFFER_SIZE;
    if (next != cb->tail) {
        cb->buffer[cb->head] = data;
        cb->head = next;
    }
}

int CircularBuffer_Read(CircularBuffer *cb, uint8_t *data) {
    if (cb->head == cb->tail) {
        return 0; // Buffer empty
    }
    *data = cb->buffer[cb->tail];
    cb->tail = (cb->tail + 1) % BUFFER_SIZE;
    return 1; // Success
}
void CheckAndPrintReceivedData() {
    static uint8_t tempBuffer[BUFFER_SIZE];
    static uint16_t index = 0;
    uint8_t byte;

    while(CircularBuffer_Read(&rxBuffer, &byte)) {
    	if (byte == '\n' || byte == '\r') {
    		tempBuffer[index] = '\0';
    		char msg[BUFFER_SIZE + 10];
    		snprintf(msg, sizeof(msg), "Received: %s\n\r", tempBuffer);
    		HAL_UART_Transmit(&uart1.huart, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
    	    index = 0;
    	} else if (index < BUFFER_SIZE - 1) {
    	    tempBuffer[index++] = byte;
    	}
    }
}


//read
//    uint8_t buffer[30];
//    size_t len = 30;

//readbyte
//   uint8_t receivedData;


//write
//    uint8_t buffer[] = "\nHello, UART!";
//    size_t bufferSize = sizeof(buffer) - 1;


//writebyte
//  char dataToSend = 'A';

//void handle_uart(){
//	if (UART_Available()) {
//		    uint8_t data = UART_Read();
//			//HAL_UART_Receive_IT(&uart1.huart, &data, 1);
//		    if (data != -1) {
//		    	if (data == '\r' || data == '\n') {
//		    		rx_buffer[buffer_index] = '\0';
//		            UART_Print("Received: ");
//		            UART_Println((uint8_t*)rx_buffer);
//		            buffer_index = 0;
//		         } else if (buffer_index < BUFFER_SIZE - 1) {
//		        	 rx_buffer[buffer_index++] = data;  // Lưu trữ ký tự vào bộ đệm
//		         }
//		    }
//	}
//}
//
//void uart_it(){
//	if (UART_Available()) {
//	UART_Print("Received: ");
//	uint8_t dt[6];
//	uint8_t data_it = HAL_UART_Receive_IT(&uart1.huart, dt, 6);
//
//	UART_Println((uint8_t*)data_it);
//	}
//}





