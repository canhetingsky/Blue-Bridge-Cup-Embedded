#include "led.h"

void LED_Init(void)
{   
    GPIO_InitTypeDef GPIO_InitStruct;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
    
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOD, &GPIO_InitStruct);
    
    GPIO_InitStruct.GPIO_Pin = LED1_PIN | LED2_PIN | LED3_PIN | LED4_PIN | LED5_PIN | LED6_PIN | LED7_PIN | LED8_PIN;
    GPIO_Init(GPIOC, &GPIO_InitStruct);
    
    GPIO_SetBits(GPIOC,LED1_PIN | LED2_PIN | LED3_PIN | LED4_PIN | LED5_PIN | LED6_PIN | LED7_PIN | LED8_PIN);
    GPIO_SetBits(GPIOD,GPIO_Pin_2);
    GPIO_ResetBits(GPIOD,GPIO_Pin_2);
}

void LED_Control(uint16_t LEDn_Pin,uint16_t LED_STATE)
{
    GPIO_SetBits(GPIOC,LEDALL);
    GPIO_SetBits(GPIOD,GPIO_Pin_2);
    GPIO_ResetBits(GPIOD,GPIO_Pin_2);
    
    switch (LED_STATE)
    {
        case LED_ON:
            GPIO_ResetBits(GPIOC,LEDn_Pin);
            GPIO_SetBits(GPIOD,GPIO_Pin_2);
            GPIO_ResetBits(GPIOD,GPIO_Pin_2);
            break;
        case LED_OFF:
            GPIO_SetBits(GPIOC,LEDn_Pin);
            GPIO_SetBits(GPIOD,GPIO_Pin_2);
            GPIO_ResetBits(GPIOD,GPIO_Pin_2);
            break;
        default:
            break;
    }
}
