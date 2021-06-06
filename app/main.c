#include "stm32f0xx.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
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
int16_t timedelay= 100;

int main( void )
{
    HAL_Init( );
    UART_Init();

    for (; ;)
    {
        if (status == SET)
        {
            status = RESET;
            timedelay = atoi((const char *)RxBuffer);
            if ((timedelay > 999 || timedelay < 10) || (timedelay < 0))
            {
                timedelay= 100;
                HAL_UART_Transmit_IT(&UartHandle,(uint8_t*)"Numero no valido\r\n",sizeof("Numero no valido\r\n")-1);
            }
            else
            {
                HAL_UART_Transmit_IT(&UartHandle,(uint8_t*)"Numero valido\r\n",sizeof("Numero valido\r\n")-1);
            }
            
        }
        HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_5);
        HAL_Delay(timedelay);
        
    } 
    return 0u;
}


