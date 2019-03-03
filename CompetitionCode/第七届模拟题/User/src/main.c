#include <stm32f10x.h>
#include <stdio.h>
#include "led.h"
#include "buzzer.h"
#include "key.h"
#include "systick.h"
#include "usart1.h"
#include "adc.h"
#include "rtc.h"
#include "lcd.h"
#include "eeprom.h"
#include "i2c.h"

/*configuration*/
#define USE_LED    1    /*choose whether to use led；USE_LED  0-don't use ；1——use*/
#define USE_BUZZER 1    /*choose whether to use buzzer；USE_BUZZER  0-don't use ；1——use*/

extern uint32_t LED_FLICKER;
extern volatile float k;

uint16_t ADCConvertedValue;

uint8_t Bsp_Init(void);

int main()
{
    uint8_t flicker=1,menu=1,adjust=1,key_temp,string[20];
    float  voltage;
    
    //TimeVar:RTC Counter; THH:Hour; TMM: Minute; TSS:Second
    uint32_t TimeVar = 0,THH = 0, TMM = 0, TSS = 0;
    uint32_t STHH = 0, STMM = 0, STSS = 0;

    if(Bsp_Init() == 1)
    {
         USART_SendString("All Init OK!\r\n");
         Buzzer_ON();
         Delay_MS(1000);
         Buzzer_OFF();
    }
    else
    {
        Buzzer_ON();
        Delay_MS(300);
        Buzzer_OFF();
        Delay_MS(300);
        Buzzer_ON();
        Delay_MS(300);
        Buzzer_OFF();
    }

    while(1)
    {
    	ADCConvertedValue = Get_Adc();
        voltage = ADCConvertedValue*3.30/4095;

        TimeVar = RTC_GetCounter();
        THH = TimeVar / 3600;
    	TMM = (TimeVar % 3600) / 60;
    	TSS = (TimeVar % 3600) % 60;

        if (TimeVar == 0x00015180)   //24小时后归零
        {
             RTC_SetCounter(0x0);
             /* Wait until last write operation on RTC registers has finished */
             RTC_WaitForLastTask();

             sprintf((char *)string,"%.2f+%.1f+%0.2d%0.2d%0.2d\n",voltage,k,THH, TMM, TSS);
             USART_SendString((int8_t *)string);
        }

        //按键检测及处理
        key_temp = Key_Scan();
		switch(key_temp)
		{
			case 0x01:
				flicker = 1 - flicker;  //闪烁功能切换，开启-->关闭，关闭-->开启
				break;
			case 0x02:
                LCD_Clear(Grey);
                switch (menu)
                {
                    case 1:
                        STHH = THH;
                        STMM = TMM;
                        STSS = TSS;
                        menu = 2;
                        sprintf((char *)string,"%.2f+%.1f+%0.2d%0.2d%0.2d\n",voltage,k,THH, TMM, TSS);
                        USART_SendString((int8_t *)string);
                        break;
                    case 2:
                        Time_Adjust(STHH,STMM,STSS);
                        menu = 1;
                        sprintf((char *)string,"%.2f+%.1f+%0.2d%0.2d%0.2d\n",voltage,k,STHH, STMM, STSS);
                        USART_SendString((int8_t *)string);
                        break;
                    default:
                        break;
                }                                 
				break;
			case 0x03:
                if(menu == 2)
                {
                    adjust++;
                    if(adjust == 4)
                    {
                         adjust = 1;
                    }
                }
				break;
			case 0x04:
                if(menu == 2)
                {
                    switch (adjust)
                    {
                        case 1:
                            STHH++;
                            if(STHH == 24)
                            {
                                STHH = 0;
                            }
                            break;
                        case 2:
                            STMM++;
                            if(STMM == 60)
                            {
                                STMM = 0;
                            }
                            break;
                        case 3:
                            STSS++;
                            if(STSS == 60)
                            {
                                STSS = 0;
                            }
                            break;
                        default:
                            break;
                    }
                }
				break;
            default:
                break;
		}

        //液晶屏界面显示
        switch (menu)
        {
            case 1:
                sprintf((char *)string,"   V1:%.2fV",voltage);
                LCD_DisplayStringLine(Line2,string);
                sprintf((char *)string,"   k:%.1f",k);
                LCD_DisplayStringLine(Line3,string);
                if(flicker == 1)
                {
                    sprintf((char *)string,"   LED:ON ");
                    LCD_DisplayStringLine(Line4,string);
                }
                else
                {
                    sprintf((char *)string,"   LED:OFF");
                    LCD_DisplayStringLine(Line4,string);
                }
                sprintf((char *)string,"   T:%0.2d-%0.2d-%0.2d",THH, TMM, TSS);
                LCD_DisplayStringLine(Line5,string);
                sprintf((char *)string,"                   1");
                LCD_DisplayStringLine(Line9,string);
                break;
            case 2:
                sprintf((char *)string,"    Setting");
                LCD_DisplayStringLine(Line3,string);
                sprintf((char *)string,"   T:%0.2d-%0.2d-%0.2d",STHH, STMM, STSS);
                LCD_DisplayStringLine(Line5,string);
                LCD_ClearLine(Line6);
                switch (adjust)
                {
                    case 1:
                        sprintf((char *)string,"     --");
                        LCD_DisplayStringLine(Line6,string);
                        break;
                    case 2:
                        sprintf((char *)string,"        --");
                        LCD_DisplayStringLine(Line6,string);
                        break;
                    case 3:
                        sprintf((char *)string,"           --");
                        LCD_DisplayStringLine(Line6,string);
                        break;
                    default:
                        break;
                }
                sprintf((char *)string,"                   2");
                LCD_DisplayStringLine(Line9,string);
                break;
            default:
                break;
         }    

        if((voltage > (3.3*k)) && (flicker ==1))
        {
            LED_FLICKER=1;  //LED达到闪烁条件
        }
        else 
        {
            LED_FLICKER=0; //LED未满足闪烁条件
        }
    }
}

uint8_t Bsp_Init(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
#if USE_LED == 1
    LED_Init();
#endif    
#if USE_BUZZER == 1
    Buzzer_Init();                      
#endif
    Key_Init();
    Usart1_Init(115200);
    ADC1_Init();
//    RTC_Init();
    RTC_Configuration();
    Time_Adjust(23,59,55);
    SysTick_Config(SystemCoreClock/1000);   //1ms中断
    
	STM3210B_LCD_Init();
	LCD_SetTextColor(Magenta);
	LCD_SetBackColor(White);
	LCD_Clear(Grey);

    i2c_init();
    k = (float)(x24c02_read(0xff)/10.0);

    return 1;
}
