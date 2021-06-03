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
// __IO ITStatus status = RESET;
uint8_t status;
extern uint8_t RxBuffer[10];


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


