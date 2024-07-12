/*
 * uart.h
 *
 *  Created on: Jul 10, 2024
 *      Author: tdat
 */


#ifndef __UART_H
#define __UART_H

#include "stm32f1xx_hal.h"
#include <stdio.h>
#include <string.h>
typedef struct {
    uint32_t baudRate;
    uint32_t wordLength;
    uint32_t stopBits;
    uint32_t parity;
} UART_Config;

typedef struct {
    UART_HandleTypeDef huart;
    UART_Config config;
    uint8_t isInitialized;
} UART_Driver;
extern UART_Driver uart1;
extern UART_Driver uart2;
extern UART_Driver uart3;



int UART_Init(UART_Driver *uart, UART_Config config);
int init(UART_HandleTypeDef *huart, UART_Config config);
size_t read(uint8_t *buff, size_t len);
uint8_t readbyte(void);
size_t write(uint8_t *buff, size_t len);
int writebyte(char byte);

#endif // __UART_H
