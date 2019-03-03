#include "key.h"

void Key_Init(void)
{   
    GPIO_InitTypeDef  GPIO_InitStructure;
  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    //B1°¢B2∞¥º¸“˝Ω≈≈‰÷√
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_8; // 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    //B3°¢B4∞¥º¸“˝Ω≈≈‰÷√
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

uint8_t Key_Scan(void)
{
    if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == 0)
    {
        while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == 0);
        return 0x01;
    }
    if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8) == 0)
    {
        while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8) == 0);
        return 0x02;
    }
    if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == 0)
    {
        while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == 0);
        return 0x03;
    }
    if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2) == 0)
    {
        while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2) == 0);
        return 0x04;
    }
    return 0x00;
}
