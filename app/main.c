#include "stm32f0xx.h"
#include <stdint.h>
#include "app_bsp.h"
#include "stm32f070xb.h"
#include "stm32f0xx_hal_conf.h"
#include "funciones.h"

/**------------------------------------------------------------------------------------------------
Brief.- Punto de entrada del programa
-------------------------------------------------------------------------------------------------*/
UART_HandleTypeDef UartHandle;
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

    for (; ;)
    {
        HAL_UART_Transmit(&UartHandle,(uint8_t *)"Hola mundo\n\r",sizeof("Hola mundo\n\r")-1,100);
        HAL_Delay(1000);
    }
    
    return 0u;
}

