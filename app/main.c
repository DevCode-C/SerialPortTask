#include "stm32f0xx.h"
#include <stdint.h>
#include "app_bsp.h"
#include "stm32f070xb.h"
#include "stm32f0xx_hal_conf.h"
#include "funciones.h"
#include "string.h"

/**------------------------------------------------------------------------------------------------
Brief.- Punto de entrada del programa
-------------------------------------------------------------------------------------------------*/
UART_HandleTypeDef UartHandle;

uint8_t msg[] = "BIenvenidos y Hola mundo\n\r";
__IO ITStatus uartState = SET;
__IO ITStatus status = RESET;

uint8_t RxByte;
uint8_t RxBuffer[20];

int main( void )
{
    HAL_Init( );
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

    for (; ;)
    {
        if(status == SET)
        {
            status = RESET;
            HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_5);
            HAL_UART_Transmit_IT(&UartHandle,RxBuffer,strlen((const char *)RxBuffer));
        }   
    }
    
    return 0u;
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    uartState = SET;
    memset(RxBuffer,0,sizeof(RxBuffer)-1);
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

