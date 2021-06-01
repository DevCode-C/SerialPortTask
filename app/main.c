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
__IO ITStatus uartState = SET;
__IO ITStatus status = RESET;
extern uint8_t RxBuffer[20];


int main( void )
{
    HAL_Init( );
    UART_Init();
    uint16_t counter = 0;
    uint32_t tick  = HAL_GetTick();
    for (; ;)
    {
        if((uartState == SET) && ((HAL_GetTick() - tick) > 1000 ))
        {
            task(&tick,&counter);
        }  
    } 
    return 0u;
}


