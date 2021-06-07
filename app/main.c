#include "stm32f0xx.h"
#include <stdint.h>
#include <stdio.h>
#include "app_bsp.h"
#include "stm32f070xb.h"
#include "stm32f0xx_hal_conf.h"
#include "string.h"
#include "stm32f0xx_hal.h"
#include "funciones.h"

/**------------------------------------------------------------------------------------------------
Brief.- Punto de entrada del programa
-------------------------------------------------------------------------------------------------*/

UART_HandleTypeDef UartHandle;
__IO ITStatus uartState = RESET;
uint8_t status;
uint8_t RxBuffer[20];
uint8_t RxByte;

void UART_Init(void);

int main( void )
{
    HAL_Init( );
    UART_Init();

    for (; ;)
    {
        status = HAL_UART_Receive(&UartHandle,RxBuffer,4,5000);
        if (status == HAL_OK)
        {
            if (!memcmp("led\r",RxBuffer,sizeof("led\r")-1))
            {
                HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_3);
            }
        }
        else
        {
            HAL_UART_Transmit(&UartHandle,(uint8_t*)"Timeout\r\n",9,500);
        }
    } 
    return 0u;
}


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
    // HAL_UART_Receive_IT(&UartHandle,&RxByte,1);
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