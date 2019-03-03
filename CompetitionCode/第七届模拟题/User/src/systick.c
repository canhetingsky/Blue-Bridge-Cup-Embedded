#include "systick.h"
#include "buzzer.h"
#include "led.h"

uint32_t TimingDelay = 0;
uint32_t LED_FLICKER = 0;  //LEDÉÁË¸Ìõ¼þÅÐ¶Ï£¬1--ÉÁË¸£¬0--²»ÉÁË¸£»
volatile float k=0.5f;
extern uint16_t ADCConvertedValue;

void Delay_MS(uint32_t ms)
{
    TimingDelay = ms;
    while(TimingDelay!=0);
}

void SysTick_Handler(void)
{
    static uint16_t flag_1s = 0;

    TimingDelay--;
    flag_1s++;
    if(flag_1s>400)
    {
        flag_1s=0;
    }

    if(LED_FLICKER==1)
    {
        if(flag_1s<200)
        {
            LED_Control(LED1_PIN,LED_ON);
        }
        else if(flag_1s<400)
        {
            LED_Control(LED1_PIN,LED_OFF);    
        }
    }
    else
    {
        LED_Control(LED1_PIN,LED_OFF);
    }
}
