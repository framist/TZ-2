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
 ALIENTEK ��ӢSTM32F103������
 
 2021��������
************************************************/




int main(void)
{
    HAL_Init();                    	 	//��ʼ��HAL��    
    Stm32_Clock_Init(RCC_PLL_MUL9);   	//����ʱ��,72M
    
	delay_init(72);               		//��ʼ����ʱ����
    //HAL_NVIC_SetPriorityGrouping(NVIC_PriorityGroup_2); 	//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ� ��������ԭ���޸���hal��
    
	uart_init(115200);					//��ʼ������
	LED_Init();							//��ʼ��LED	
    BEEP_Init();
	KEY_Init();							//��ʼ������
	LCD_Init();							//��ʼ��LCD
	//tp_dev.init();				   		//��������ʼ�� 
 	TP_Init();				//��������ʼ��
    //TP_Adjust();
    
	SRAM_Init();		//��ʼ��SRAM
	TIM3_Init(999,71);	//1KHZ ��ʱ��1ms 
	TIM6_Init(999,719);	//10ms�ж�

	my_mem_init(SRAMIN); 		//��ʼ���ڲ��ڴ��
	my_mem_init(SRAMEX);  		//��ʼ���ⲿ�ڴ��
	
	__HAL_RCC_CRC_CLK_ENABLE();//ʹ��CRCʱ�ӣ�����STemWin����ʹ�� 
	WM_SetCreateFlags(WM_CF_MEMDEV);
	GUI_Init();
    
    BEEP = 1;
    delay_ms(50);
    BEEP = 0;
    //����Ƥ��
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
	hWin = CreateFramewin(); // ���ƴ��ں���


    
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


