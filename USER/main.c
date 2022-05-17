#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "key.h"
#include "24cxx.h"
#include "w25qxx.h"
#include "touch.h"
#include "sram.h"
#include "timer.h"
#include "malloc.h"
#include "GUI.h"
#include "FramewinDLG.h"
#include "JY61.h"
#include "beep.h"
//#include "this_output.h"
#include <stdio.h>
/************************************************
 ALIENTEK 精英STM32F103开发板
 
 2021电赛联赛
************************************************/




int main(void)
{
    HAL_Init();                    	 	//初始化HAL库    
    Stm32_Clock_Init(RCC_PLL_MUL9);   	//设置时钟,72M
    
	delay_init(72);               		//初始化延时函数
    //HAL_NVIC_SetPriorityGrouping(NVIC_PriorityGroup_2); 	//设置NVIC中断分组2:2位抢占优先级，2位响应优先级 已有正点原子修改在hal库
    
	uart_init(115200);					//初始化串口
	LED_Init();							//初始化LED	
    BEEP_Init();
	KEY_Init();							//初始化按键
	LCD_Init();							//初始化LCD
	//tp_dev.init();				   		//触摸屏初始化 
 	TP_Init();				//触摸屏初始化
    //TP_Adjust();
    
	SRAM_Init();		//初始化SRAM
	TIM3_Init(999,71);	//1KHZ 定时器1ms 
	TIM6_Init(999,719);	//10ms中断

	my_mem_init(SRAMIN); 		//初始化内部内存池
	my_mem_init(SRAMEX);  		//初始化外部内存池
	
	__HAL_RCC_CRC_CLK_ENABLE();//使能CRC时钟，否则STemWin不能使用 
	WM_SetCreateFlags(WM_CF_MEMDEV);
	GUI_Init();
    
    BEEP = 1;
    delay_ms(50);
    BEEP = 0;
    //更换皮肤
//    #include "DIALOG.h"
//	BUTTON_SetDefaultSkin(BUTTON_SKIN_FLEX); 
//	CHECKBOX_SetDefaultSkin(CHECKBOX_SKIN_FLEX);
//	DROPDOWN_SetDefaultSkin(DROPDOWN_SKIN_FLEX);
//	FRAMEWIN_SetDefaultSkin(FRAMEWIN_SKIN_FLEX);
//	HEADER_SetDefaultSkin(HEADER_SKIN_FLEX);
//	MENU_SetDefaultSkin(MENU_SKIN_FLEX);
//	MULTIPAGE_SetDefaultSkin(MULTIPAGE_SKIN_FLEX);
//	PROGBAR_SetDefaultSkin(PROGBAR_SKIN_FLEX);
//	RADIO_SetDefaultSkin(RADIO_SKIN_FLEX);
//	SCROLLBAR_SetDefaultSkin(SCROLLBAR_SKIN_FLEX);
//	SLIDER_SetDefaultSkin(SLIDER_SKIN_FLEX);
//	SPINBOX_SetDefaultSkin(SPINBOX_SKIN_FLEX);
    void LogPrint(char *log,WM_HWIN hWin);
    void refresh_Measure(WM_HWIN hWin);
    int i = 0;
    //char stemp[100] = "";

        
    WM_HWIN hWin;
	hWin = CreateFramewin(); // 绘制窗口函数


    
	while(1)
	{
		//GUI_Delay(100); 
        GUI_Exec();

        LED0 = !LED0;
        
        refresh_Measure(hWin);
        
        if(BEEP == 1){
            i++;
            if(i ==150){
                BEEP = 0;
                i = 0;
            }
        }
        

	}
}


