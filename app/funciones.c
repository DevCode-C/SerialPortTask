#include "stm32f0xx.h"
#include <stdint.h>
#include "app_bsp.h"
#include "stm32f070xb.h"
#include "stm32f0xx_hal_gpio.h"
#include "stm32f0xx_hal_rcc.h"
#include "funciones.h"

// #define TASK 1
extern UART_HandleTypeDef UartHandle;
uint8_t RxByte;
uint8_t RxBuffer[20];

extern __IO ITStatus uartState;
extern __IO ITStatus status;

void UART_Init()
{
    UartHandle.Instance             = USART2;
    UartHandle.Init.BaudRate        = 9600;
    UartHandle.Init.WordLength      = UART_WORDLENGTH_8B;
    UartHandle.Init.StopBits        = UART_STOPBITS_1;
    UartHandle.Init.Parity          = UART_PARITY_NONE;
    UartHandle.Init.HwFlowCtl       = UART_HWCONTROL_NONE;
    UartHandle.Init.Mode            = UART_MODE_TX_RX;
    UartHandle.Init.OverSampling    = UART_OVERSAMPLING_16;

    HAL_UART_Init(&UartHandle);
    HAL_UART_Receive_IT(&UartHandle,&RxByte,1);
}

void task(uint32_t *tick, uint16_t *counter)
{
    *tick = HAL_GetTick();
    uartState = RESET;
    HAL_GPIO_WritePin(GPIOC,*counter,GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOC,~(*counter),GPIO_PIN_RESET);
    HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_5);
    sprintf((char *)RxBuffer,"Val: %d\n",*counter);
    HAL_UART_Transmit_IT(&UartHandle,RxBuffer,strlen((const char *)RxBuffer));
    *counter += 1;
    // if (*counter > 500)
    if (*counter > 9)
    {
        *counter = 0;
    }
}


void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    uartState = SET;
    memset(RxBuffer,0,sizeof(RxBuffer));
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    static uint32_t i = 0;
    RxBuffer[i] = RxByte;
    i++;
    if(RxBuffer[i-1] == '\r')
    {
        status = SET;
        i=0;
    }
    HAL_UART_Receive_IT(&UartHandle,&RxByte,1);
}