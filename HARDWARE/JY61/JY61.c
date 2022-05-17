/*
编写者：Kevin
网址：http://RobotControl.taobao.com
作者E-mail：1609370741@qq.com
编译环境：MDK-Lite  Version: 5.17
初版时间: 2016-1-31
测试： 本程序已在【君悦智控】的STM32Core平台上完成测试
功能：
用STM32Core平台串口2读取JY901的数据，然后通过串口1打印到串口助手,串口助手波特率要选为9600。
JY-61的波特率要修改为115200.
注意：示例程序输出的是ASCLL码，用16进制（HEX）显示是不能看到准确数据的。

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





//用串口2给JY模块发送指令
void sendcmd(char cmd[])
{
//	char i;
//	for(i=0;i<3;i++)
//		UART2_Put_Char(cmd[i]);
}

//CopeSerial2Data为串口中断调用函数，串口每收到一个数据，调用一次这个函数。
void CopeSerial2Data(unsigned char ucData)
{
	static unsigned char ucRxBuffer[11];
	static unsigned char ucRxCnt = 0;	
	
	
	ucRxBuffer[ucRxCnt++]=ucData;	//将收到的数据存入缓冲区中
	if (ucRxBuffer[0]!=0x55) //数据头不对，则重新开始寻找0x55数据头
	{
		ucRxCnt=0;
		return;
	}
	if (ucRxCnt<11) {return;}//数据不满11个，则返回
	else
	{
		switch(ucRxBuffer[1])//判断数据是哪种数据，然后将其拷贝到对应的结构体中，有些数据包需要通过上位机打开对应的输出后，才能接收到这个数据包的数据
		{
			//memcpy为编译器自带的内存拷贝函数，需引用"string.h"，将接收缓冲区的字符拷贝到数据结构体里面，从而实现数据的解析。
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
		ucRxCnt=0;//清空缓存区
	}
}




void JY61_main(void)
{  		
	unsigned char i = 0;
//	SysTick_init(72,10);//设置时钟频率
//	Initial_UART1(9600);//接PC的串口
//	Initial_UART2(115200);//接JY61模块的串口	
//	
//	LED_ON();
	delay_ms(1000);delay_ms(1000);//等等JY61初始化完成

	//功能现象，10秒钟左右会进行一次加速度校准,Z轴角度归零，XYZ角度会缓慢回到0度状态
	while(1)
	{			
//		delay_ms(1000);
//		i++;
//		if(i>10)
//		{
//			i = 0;
//			printf("正在进行加速度校准\r\n");
//			sendcmd(ACCCMD);//等待模块内部自动校准好，模块内部会自动计算需要一定的时间
//			printf("加速度校准完成\r\n");
//			delay_ms(100);
//			printf("进行Z轴角度清零\r\n");
//			sendcmd(YAWCMD);
//			printf("Z轴角度清零完成\r\n");
//		}
//		printf("-----------------------------------\r\n");
		//输出加速度
		//串口接受到的数据已经拷贝到对应的结构体的变量中了，根据说明书的协议，以加速度为例 stcAcc.a[0]/32768*16就是X轴的加速度，
		printf("Acc:%.3f %.3f %.3f\r\n",(float)stcAcc.a[0]/32768*16,(float)stcAcc.a[1]/32768*16,(float)stcAcc.a[2]/32768*16);

		//输出角速度
		printf("Gyro:%.3f %.3f %.3f\r\n",(float)stcGyro.w[0]/32768*2000,(float)stcGyro.w[1]/32768*2000,(float)stcGyro.w[2]/32768*2000);

		//输出角度
		printf("Angle:%.3f %.3f %.3f\r\n",(float)stcAngle.Angle[0]/32768*180,(float)stcAngle.Angle[1]/32768*180,(float)stcAngle.Angle[2]/32768*180);

	}//主循环
}



