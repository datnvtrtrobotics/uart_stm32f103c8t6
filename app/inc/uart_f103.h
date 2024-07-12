/*
 * uart_f103.h
 *
 *  Created on: Jul 11, 2024
 *      Author: tdat
 */


#ifndef UART_F103_H
#define UART_F103_H

#include "stm32f1xx_hal.h"
//extern uint8_t data;

#define BUFFER_SIZE 300
typedef struct {
	      uint8_t buffer[BUFFER_SIZE];
	      volatile uint16_t head;
	      volatile uint16_t tail;
} CircularBuffer;
extern CircularBuffer rxBuffer;
// Buffer definitions
//#define BUFFER_SIZE 128
//extern char rx_buffer[BUFFER_SIZE];
extern uint16_t buffer_index;

void Config_uart(void);
void CircularBuffer_Write(CircularBuffer *cb, uint8_t data);
int CircularBuffer_Read(CircularBuffer *cb, uint8_t *data);
void CheckAndPrintReceivedData();

void handle_uart(void);

// UART communication functions
int UART_Available(void);
uint8_t UART_Read(void);
void UART_Print(const char *str);
void UART_Println(const uint8_t *str);

#endif /* UART_F103_H */
