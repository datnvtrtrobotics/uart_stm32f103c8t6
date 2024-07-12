/*
 * uart.c
 *
 *  Created on: Jul 10, 2024
 *      Author: tdat
 */

#include "stm32f1xx_hal.h"
#include "uart.h"

UART_Driver uart1 = { .huart.Instance = USART1, .isInitialized = 0 };
UART_Driver uart2 = { .huart.Instance = USART2, .isInitialized = 0 };
UART_Driver uart3 = { .huart.Instance = USART3, .isInitialized = 0 };

// Hàm trợ giúp khởi tạo GPIO cho UART
static void UART_MspInit(UART_HandleTypeDef *huart) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    if (huart->Instance == USART1) {
        __HAL_RCC_USART1_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();

        GPIO_InitStruct.Pin = GPIO_PIN_9 ;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_10;
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT ;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    }
    if (huart->Instance == USART2) {
        __HAL_RCC_USART2_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();

        GPIO_InitStruct.Pin = GPIO_PIN_2;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_3;
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    }
    if (huart->Instance == USART3) {
        __HAL_RCC_USART3_CLK_ENABLE();
        __HAL_RCC_GPIOB_CLK_ENABLE();

        GPIO_InitStruct.Pin = GPIO_PIN_10;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_11;
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    }
}

int UART_Init(UART_Driver *uart, UART_Config config) {
    if (uart->isInitialized) {
        return -1; // UART đã được khởi tạo trước đó
    }
    uart->config = config;

    uart->huart.Init.BaudRate = config.baudRate;
    uart->huart.Init.WordLength = config.wordLength;
    uart->huart.Init.StopBits = config.stopBits;
    uart->huart.Init.Parity = config.parity;
    uart->huart.Init.Mode = UART_MODE_TX_RX;
    uart->huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    uart->huart.Init.OverSampling = UART_OVERSAMPLING_16;

    UART_MspInit(&uart->huart);

    if (HAL_UART_Init(&uart->huart) != HAL_OK) {
        return 1; // Khởi tạo thất bại
    }

    uart->isInitialized = 1;
    return 0; // Khởi tạo thành công
}

int init(UART_HandleTypeDef *huart, UART_Config config) {
	    if (huart->Instance == USART1) {
	        return UART_Init(&uart1, config);
	    } else if (huart->Instance == USART2) {
	        return UART_Init(&uart2, config);
	    } else if (huart->Instance == USART3) {
	        return UART_Init(&uart3, config);
    } else {
        return 1; // Không tìm thấy UART phù hợp
    }
}

size_t read(uint8_t *buff, size_t len) {
    if (HAL_UART_Receive(&uart1.huart, buff, len, 100) == HAL_OK) {
        return len;
    } else if (HAL_UART_Receive(&uart2.huart, buff, len, 100) == HAL_OK) {
        return len;
    } else if (HAL_UART_Receive(&uart3.huart, buff, len, 100) == HAL_OK) {
        return len;
    }
    return 0;  // No data received
}
uint8_t readbyte() {
    uint8_t data = 0x30;
    if (HAL_UART_Receive(&uart1.huart, &data, 1, 100) == HAL_OK) {
        return data;
    }
    if (HAL_UART_Receive(&uart2.huart, &data, 1, 100) == HAL_OK) {
        return data;
//    } else if (HAL_UART_Receive(&uart3.huart, &data, 1, 100) == HAL_OK) {
//        return data;
    }
    return data;  // No data received
}

size_t write(uint8_t *buff, size_t len) {
    if (HAL_UART_Transmit(&uart1.huart, buff, len, HAL_MAX_DELAY) == HAL_OK) {
        return len;
    } else if (HAL_UART_Transmit(&uart2.huart, buff, len, HAL_MAX_DELAY) == HAL_OK) {
        return len;
    } else if (HAL_UART_Transmit(&uart3.huart, buff, len, HAL_MAX_DELAY) == HAL_OK) {
        return len;
    }
    return 0;  // No data written
}
int writebyte(char byte) {
    if (HAL_UART_Transmit(&uart1.huart,(uint8_t *) &byte, 1, HAL_MAX_DELAY) == HAL_OK) {
        return 0;  // Write successful
    } else if (HAL_UART_Transmit(&uart1.huart,(uint8_t *) &byte, 1, HAL_MAX_DELAY) == HAL_TIMEOUT) {
        return 1;  // Timeout
    } else if (HAL_UART_Transmit(&uart2.huart, (uint8_t *)&byte, 1, HAL_MAX_DELAY) == HAL_OK) {
        return 0;  // Write successful
    } else if (HAL_UART_Transmit(&uart2.huart,(uint8_t *) &byte, 1, HAL_MAX_DELAY) == HAL_TIMEOUT) {
        return 1;  // Timeout
    } else if (HAL_UART_Transmit(&uart3.huart, (uint8_t *)&byte, 1, HAL_MAX_DELAY) == HAL_OK) {
        return 0;  // Write successful
    } else if (HAL_UART_Transmit(&uart3.huart,(uint8_t *) &byte, 1, HAL_MAX_DELAY) == HAL_TIMEOUT) {
        return 1;  // Timeout
    } else {
        return -1;  // Error
    }
}

void UART_Print( char* str) {
	HAL_UART_Transmit(&uart1.huart, (uint8_t*)str, strlen(str), 100);
}

void UART_Println( uint8_t* str) {
	char buffer[128];
    snprintf(buffer, sizeof(buffer), "%s\r\n", str);
    HAL_UART_Transmit(&uart1.huart, (uint8_t*)buffer, strlen(buffer),100);
}


int UART_Available(){
	return __HAL_UART_GET_FLAG(&uart1.huart, UART_FLAG_RXNE);
}

uint8_t UART_Read() {
    uint8_t rxData;
    if (HAL_UART_Receive_IT(&uart1.huart, &rxData, 1) == HAL_OK){
    	return rxData;
    }
    return -1;
}
