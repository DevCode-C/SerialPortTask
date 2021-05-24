#include "stm32f0xx.h"
#include <stdint.h>
#include "app_bsp.h"
#include "stm32f070xb.h"
#include "stm32f0xx_hal_gpio.h"
#include "stm32f0xx_hal_rcc.h"
#include "funciones.h"

// #define TASK 1

GPIO_InitTypeDef    GPIO_PORTC;
GPIO_InitTypeDef    GPIO_PORTA;
GPIO_InitTypeDef    GPIO_InitStruct;


void initTask()
{
    __HAL_RCC_GPIOC_CLK_ENABLE();
    GPIO_PORTC.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_PORTC.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_PORTC.Pull = GPIO_NOPULL;
    GPIO_PORTC.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3; 
    GPIO_PORTC.Pin += GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
    HAL_GPIO_Init(GPIOC, &GPIO_PORTC);

    __HAL_RCC_GPIOA_CLK_ENABLE( );
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull  = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Pin   = GPIO_PIN_5;
    HAL_GPIO_Init( GPIOA, &GPIO_InitStruct );

    GPIO_PORTA.Mode = GPIO_MODE_INPUT;
    // GPIO_PORTA.Pull = GPIO_NOPULL;
    GPIO_PORTA.Pin  =  GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_8 | GPIO_PIN_9;
    GPIO_PORTA.Pin  +=  GPIO_PIN_11 | GPIO_PIN_12;
    HAL_GPIO_Init(GPIOA, &GPIO_PORTA);
    
}
#if (TASK == 1)
    /*
        Parpadee los leds conectados al puerto C de manera alternada (enciendo leds
        D1, D3, D5, D7, y despues D2, D4, D6, D8).
    */
    void task(void)
    {
        uint8_t state = 0;
        for( ; ; )
        {
            state = !state;

            HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3,state);
            HAL_GPIO_WritePin(GPIOC,GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7,!state);
            
            HAL_GPIO_TogglePin( GPIOA, GPIO_PIN_5 );
            HAL_Delay( 100u );
        }
    }

#elif (TASK == 2)
    /*
        Ingrese un numero en binario por el puerto A usando el microswitch y despliegue
        su inverso en los leds del puerto A
    */
    void task(void)
    {
        for( ; ; )
        {
            HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0,!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0));
            HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1));
            HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_8));
            HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3,!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_9));
            HAL_GPIO_WritePin(GPIOC,GPIO_PIN_4,!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_11));
            HAL_GPIO_WritePin(GPIOC,GPIO_PIN_5,!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_12));

            HAL_GPIO_TogglePin( GPIOA, GPIO_PIN_5 );
            HAL_Delay( 100u );
        }
    }

#elif (TASK == 3)
    /*
        Escriba un programa que rote un led apagado en el puerto A a velocidad
        suficiente para ser perceptible por el ojo humano
    */
    void task(void)
    {
        uint8_t state = 0;
        // uint8_t dato[8] = {1<<0,1<<1,1<<2,1<<3,1<<4,1<<5,1<<6,1<<7};
        for( ; ; )
        {
            for (uint8_t i = 0; i < 8; i++)
            {
                // state &= ~(1<<i);
                state = (1<<i) & 0xff;
                HAL_GPIO_WritePin(GPIOC,0xff,1);
                HAL_GPIO_WritePin(GPIOC,state,0);
                // HAL_GPIO_WritePin(GPIOC,0xff,1); 
                // HAL_GPIO_WritePin(GPIOC,dato[i],0); 
                
                
                HAL_GPIO_TogglePin( GPIOA, GPIO_PIN_5 );
                HAL_Delay( 100u );
            }

        }
    }

#elif (TASK == 4)
    /*
        Escriba un programa que rote un led en el puerto C pero esta vez varie la
        velocidad de rotación usando los micro switches del puerto A (se pueden
        ingresar 16 combinaciones de valores, así que se debe tener 16 diferentes
        velocidades).
    */
    void task(void)
    {
        
        uint8_t state       = 0;
        // uint8_t count       = 0;
        uint8_t inputState  = 0;
        for( ; ; )
        {
           for (uint8_t i = 0; i < 8; i++)
            {
                inputState  = HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0) + 1;
                inputState += HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1)<<1;
                inputState += HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_8)<<2;
                inputState += HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_9)<<3;

                state = (1<<i) & 0xff;
                HAL_GPIO_WritePin(GPIOC,0xff,1);
                HAL_GPIO_WritePin(GPIOC,state,0);
                
                HAL_GPIO_TogglePin( GPIOA, GPIO_PIN_5 );
                HAL_Delay( inputState*10);
            }
        }
    }   
#endif