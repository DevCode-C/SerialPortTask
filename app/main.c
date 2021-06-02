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
    uint16_t pinvalue = 1;
    uint32_t tick  = HAL_GetTick();
    uint32_t tick2  = HAL_GetTick();
    for (; ;)
    {
        if((uartState == SET) && ((HAL_GetTick() - tick) > 2000 ))
        {
            task(&tick, &pinvalue);
        }
        if((HAL_GetTick() - tick2) > 300 )
        {
            tick2  = HAL_GetTick();
            HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_5);
        }  
    } 
    return 0u;
}


