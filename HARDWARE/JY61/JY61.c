/*
��д�ߣ�Kevin
��ַ��http://RobotControl.taobao.com
����E-mail��1609370741@qq.com
���뻷����MDK-Lite  Version: 5.17
����ʱ��: 2016-1-31
���ԣ� ���������ڡ������ǿء���STM32Coreƽ̨����ɲ���
���ܣ�
��STM32Coreƽ̨����2��ȡJY901�����ݣ�Ȼ��ͨ������1��ӡ����������,�������ֲ�����ҪѡΪ9600��
JY-61�Ĳ�����Ҫ�޸�Ϊ115200.
ע�⣺ʾ�������������ASCLL�룬��16���ƣ�HEX����ʾ�ǲ��ܿ���׼ȷ���ݵġ�

 */
#include <string.h>
#include <stdio.h>

//#include "UART1.h"
//#include "UART2.h"
#include "delay.h"
#include "JY61.h"



struct SAcc 		stcAcc;
struct SGyro 		stcGyro;
struct SAngle 	stcAngle;
struct STime         stcTime;

char YAWCMD[3] = {0XFF,0XAA,0X52};
char ACCCMD[3] = {0XFF,0XAA,0X67};
char SLEEPCMD[3] = {0XFF,0XAA,0X60};
char UARTMODECMD[3] = {0XFF,0XAA,0X61};
char IICMODECMD[3] = {0XFF,0XAA,0X62};





//�ô���2��JYģ�鷢��ָ��
void sendcmd(char cmd[])
{
//	char i;
//	for(i=0;i<3;i++)
//		UART2_Put_Char(cmd[i]);
}

//CopeSerial2DataΪ�����жϵ��ú���������ÿ�յ�һ�����ݣ�����һ�����������
void CopeSerial2Data(unsigned char ucData)
{
	static unsigned char ucRxBuffer[11];
	static unsigned char ucRxCnt = 0;	
	
	
	ucRxBuffer[ucRxCnt++]=ucData;	//���յ������ݴ��뻺������
	if (ucRxBuffer[0]!=0x55) //����ͷ���ԣ������¿�ʼѰ��0x55����ͷ
	{
		ucRxCnt=0;
		return;
	}
	if (ucRxCnt<11) {return;}//���ݲ���11�����򷵻�
	else
	{
		switch(ucRxBuffer[1])//�ж��������������ݣ�Ȼ���俽������Ӧ�Ľṹ���У���Щ���ݰ���Ҫͨ����λ���򿪶�Ӧ������󣬲��ܽ��յ�������ݰ�������
		{
			//memcpyΪ�������Դ����ڴ濽��������������"string.h"�������ջ��������ַ����������ݽṹ�����棬�Ӷ�ʵ�����ݵĽ�����
            case 0x50:	
                memcpy(&stcTime,&ucRxBuffer[2],8);
                break;
			case 0x51:	
                memcpy(&stcAcc,&ucRxBuffer[2],8);
                break;
			case 0x52:	
                memcpy(&stcGyro,&ucRxBuffer[2],8);
                break;
			case 0x53:	
                memcpy(&stcAngle,&ucRxBuffer[2],8);
                break;
            default: break;
		}
		ucRxCnt=0;//��ջ�����
	}
}




void JY61_main(void)
{  		
	unsigned char i = 0;
//	SysTick_init(72,10);//����ʱ��Ƶ��
//	Initial_UART1(9600);//��PC�Ĵ���
//	Initial_UART2(115200);//��JY61ģ��Ĵ���	
//	
//	LED_ON();
	delay_ms(1000);delay_ms(1000);//�ȵ�JY61��ʼ�����

	//��������10�������һ����һ�μ��ٶ�У׼,Z��Ƕȹ��㣬XYZ�ǶȻỺ���ص�0��״̬
	while(1)
	{			
//		delay_ms(1000);
//		i++;
//		if(i>10)
//		{
//			i = 0;
//			printf("���ڽ��м��ٶ�У׼\r\n");
//			sendcmd(ACCCMD);//�ȴ�ģ���ڲ��Զ�У׼�ã�ģ���ڲ����Զ�������Ҫһ����ʱ��
//			printf("���ٶ�У׼���\r\n");
//			delay_ms(100);
//			printf("����Z��Ƕ�����\r\n");
//			sendcmd(YAWCMD);
//			printf("Z��Ƕ��������\r\n");
//		}
//		printf("-----------------------------------\r\n");
		//������ٶ�
		//���ڽ��ܵ��������Ѿ���������Ӧ�Ľṹ��ı������ˣ�����˵�����Э�飬�Լ��ٶ�Ϊ�� stcAcc.a[0]/32768*16����X��ļ��ٶȣ�
		printf("Acc:%.3f %.3f %.3f\r\n",(float)stcAcc.a[0]/32768*16,(float)stcAcc.a[1]/32768*16,(float)stcAcc.a[2]/32768*16);

		//������ٶ�
		printf("Gyro:%.3f %.3f %.3f\r\n",(float)stcGyro.w[0]/32768*2000,(float)stcGyro.w[1]/32768*2000,(float)stcGyro.w[2]/32768*2000);

		//����Ƕ�
		printf("Angle:%.3f %.3f %.3f\r\n",(float)stcAngle.Angle[0]/32768*180,(float)stcAngle.Angle[1]/32768*180,(float)stcAngle.Angle[2]/32768*180);

	}//��ѭ��
}



