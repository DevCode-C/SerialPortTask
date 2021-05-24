#include "stm32f0xx.h"
#include <stdint.h>
#include "app_bsp.h"
#include "stm32f070xb.h"
#include "stm32f0xx_hal_gpio.h"
#include "funciones.h"

/**------------------------------------------------------------------------------------------------
Brief.- Punto de entrada del programa
-------------------------------------------------------------------------------------------------*/

int main( void )
{
    HAL_Init( );
    initTask();
    task();

    return 0u;
}

