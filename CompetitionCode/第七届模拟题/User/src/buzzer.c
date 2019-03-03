#include "buzzer.h"

void Buzzer_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE); 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); 
     
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_NoJTRST,ENABLE); 
    
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
       
    Buzzer_OFF();
}

void Buzzer_OFF(void)
{
    GPIO_SetBits(GPIOB,GPIO_Pin_4);     //·äÃùÆ÷Í£
}

void Buzzer_ON(void)
{
    GPIO_ResetBits(GPIOB,GPIO_Pin_4);     //·äÃùÆ÷Ïì
}
