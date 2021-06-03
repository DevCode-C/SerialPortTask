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
__IO ITStatus status = RESET;
extern uint8_t RxBuffer[20];


int main( void )
{
    HAL_Init( );
    UART_Init();

    for (; ;)
    {
        if (status == SET)
        {
            status = RESET;
            if (!memcmp("uno\r",RxBuffer,sizeof("uno\r")-1))
            {
                HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_0);
            }
            else if (!memcmp("dos\r",RxBuffer,sizeof("dos\r")-1))
            {
                HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_1);
            }
            else if (!memcmp("tres\r",RxBuffer,sizeof("tres\r")-1))
            {
                HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_2);
            }
        }
        
    } 
    return 0u;
}


