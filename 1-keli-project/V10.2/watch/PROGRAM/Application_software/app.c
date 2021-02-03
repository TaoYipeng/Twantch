
#include "stdio.h"

#include "app.h"

#include "display.h"

#include "main.h"
#include "adc.h"
#include "dma.h"
#include "i2c.h"

#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

#include "contro.h"

#include "display.h"

#include "lcd.h"
#include "lcd_init.h"
#include "apppicture.h"

#include "mpu6050Driver.h"


uint8_t clock_time_hour[7] = {70,70,70,70,70,70};

uint8_t clock_time_min[7] = {60,60,60,60,60,60};

uint8_t clock_Data[7];


/*******************************************
* @function: 	��Ϸ
* @input:			��
* @return:		��
* @author:		��С��
* @time:			2020.10.25
*******************************************/
int X_cricle ,Y_cricle;

int X_cricle_his ,Y_cricle_his;

void APP_GAME(void)
{
	unsigned char switch_value;
	
	float pitch,roll,yaw; 		//ŷ����
	
	float Jpitch,Jroll,Jyaw; 		//ŷ����//У׼ֵ

	begin:
	
	X_cricle = LCD_W/2;
	
	Y_cricle = LCD_H/2;
	
	LCD_Fill(0,0,LCD_W,LCD_H,BLACK); //
	
	Draw_Circle(	X_cricle,	Y_cricle,	5,	RED	);
	
	Draw_Circle(	2,	18,	5,	RED	);
	
	Draw_Circle(	67,	1,	5,	RED	);
	
	Draw_Circle(	23,	96,	5,	RED	);
	
	Draw_Circle(	76,	24,	5,	RED	);
	
	Draw_Circle(	19,	200,	5,	RED	);
	
	Draw_Circle(	90,	210,	5,	RED	);
	
	Draw_Circle(	100,	18,	5,	RED	);

	//HAL_Delay(200); //�ȴ�
	
	printf("��Ϸ��ʼ��\r\n");
	
	/*���¶������ǽ���У׼*/
	while(1)
	{
		if(	mpu_dmp_get_data(	&pitch,	&roll,	&yaw	)	==	0	)
		{
			printf("%.2f %.2f %.2f \r\n",pitch,roll,yaw);
			
			Jpitch = pitch; //�Ի�ȡ���ĽǶȽ���У׼
			
			Jroll = roll;
			
			Jyaw = yaw;
			
			printf("��Ϸ��ʼ�����\r\n");
			
			break;
		}
	}
	
	printf("��������Ϸ\r\n");
	
	/*LCD_W 135	 LCD_H 240*/
	while(1)
	{
		switch_value = Get_Key_value(0);
		
		if(	switch_value	 == Button_1_pressed	||	switch_value	 == Button_3_pressed	)	goto begin;
		
		if(	switch_value	 == Button_2_pressed	)	break;
		
		if(	mpu_dmp_get_data(	&pitch,	&roll,	&yaw	)	==	0	)
		{
			printf("%.2f %.2f %.2f \r\n",pitch,roll,yaw);
			
			pitch = pitch	-	Jpitch	;
			
			roll = roll	-	Jroll	;
			
			yaw = yaw	-	Jyaw	;
		}
		
		
		Draw_Circle(	X_cricle_his,	Y_cricle_his,	10,	BLACK	);

		if(	pitch	>	8	)
		{
			Y_cricle ++ ;
		}
		if(pitch	<	-8	)
		{
			Y_cricle-- ;
		}
		
		if(	roll	>	8	)
		{
			X_cricle-- ;
		}
		if(	roll	<	-8	)	
		{
			X_cricle ++ ;
		}
		
		if(	X_cricle	>	LCD_W	)
		{
			X_cricle	=	LCD_W;
		}
		if(	X_cricle	<	0	)
		{
			X_cricle	=	0;
		}
		if(	Y_cricle	>	LCD_H	)
		{
			Y_cricle	=	LCD_H;
		}
		if(	Y_cricle	<	0	)
		{
			Y_cricle	=	0;
		}
		
		Draw_Circle(X_cricle,Y_cricle,10,GREEN);

		HAL_Delay(5);
		
		X_cricle_his = X_cricle;
		
		Y_cricle_his = Y_cricle;
		
	}//��Ϸ��ѭ������
	
	printf("�˳�����Ϸ\r\n");
	
}


/*******************************************
* @function: 	���ӵĹ���
* @input:			��
* @return:		��
* @author:		��С��
* @time:			2020.10.3
*******************************************/

void clock_begin_display(void)
{
	LCD_Fill(0,	0,	LCD_W,	LCD_H,	WHITE); //��ʾ����ɰ�ɫˢ��
	
	LCD_Fill(0,	0,	LCD_W,	30,	WHITE); //��ʾ����ɻ�ɫˢ��
		
	LCD_Fill(0,	30,	LCD_W,	31,	BLACK); //����		
	
	LCD_Fill(0,	60,	LCD_W,	61,	BLACK); //����			
	
	LCD_Fill(0,	90,	LCD_W,	91,	BLACK); //����			
	
	LCD_Fill(0,	120,	LCD_W,	121,	BLACK); //����			
	
	LCD_Fill(0,	150,	LCD_W,	151,	BLACK); //����			
	
	LCD_Fill(0,	180,	LCD_W,	181,	BLACK); //����			
	
	LCD_Fill(0,	210,	LCD_W,	211,	BLACK); //����

	LCD_Fill(0,		61,	LCD_W,	90,	WHITE); //��ʾ����ɻ�ɫˢ��
	
	
	//LCD_Fill(0,		0,	LCD_W,	30,	LGRAY); //��ʾ����ɻ�ɫˢ��
		
	LCD_ShowChinese(0,	3,	"����",	BLACK,	WHITE,24,0);
	
//	LCD_Fill(0,		31,	LCD_W,	60,	WHITE); //��ʾ����ɻ�ɫˢ��	
	
	LCD_ShowChinese(0,		33,	"�½�",	BLACK,	WHITE,24,0);
		
	//��ʾ��һ������
	if(clock_time_hour[0] != 60)
	{
		LCD_ShowFloatNum1(5,	68,	clock_time_hour[0]+clock_time_min[0]*0.01,	4,	BLACK,	WHITE,	16);
		
		switch(clock_Data[0])
		{
			case 0:	LCD_ShowChinese(80,		63,	"ÿ��",	BLACK,	WHITE,	24,0);	break;//��ʾ��һ��
			case 1:	LCD_ShowChinese(80,		63,	"��һ",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
			case 2:	LCD_ShowChinese(80,		63,	"�ܶ�",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
			case 3:	LCD_ShowChinese(80,		63,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
			case 4:	LCD_ShowChinese(80,		63,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
			case 5:	LCD_ShowChinese(80,		63,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
			case 6:	LCD_ShowChinese(80,		63,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
			case 7:	LCD_ShowChinese(80,		63,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
		}
	}	
	
	//��ʾ��2������
	if(clock_time_hour[1] != 60)
	{
		LCD_ShowFloatNum1(5,	98,	clock_time_hour[1]+clock_time_min[1]*0.01,	4,	BLACK,	WHITE,	16);
		switch(clock_Data[1])
		{
			case 0:	LCD_ShowChinese(80,		93,	"ÿ��",	BLACK,	WHITE,	24,0);	break;//��ʾ��һ��
			case 1:	LCD_ShowChinese(80,		93,	"��һ",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
			case 2:	LCD_ShowChinese(80,		93,	"�ܶ�",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
			case 3:	LCD_ShowChinese(80,		93,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
			case 4:	LCD_ShowChinese(80,		93,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
			case 5:	LCD_ShowChinese(80,		93,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
			case 6:	LCD_ShowChinese(80,		93,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
			case 7:	LCD_ShowChinese(80,		93,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
		}
	}
	
	
	//��ʾ��3������
	if(clock_time_hour[2] != 60)
	{
		LCD_ShowFloatNum1(5,	128,	clock_time_hour[2]+clock_time_min[2]*0.01,	4,	BLACK,	WHITE,	16);
		switch(clock_Data[2])
		{
			case 0:	LCD_ShowChinese(80,		123,	"ÿ��",	BLACK,	WHITE,	24,0);	break;//��ʾ��һ��
			case 1:	LCD_ShowChinese(80,		123,	"��һ",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
			case 2:	LCD_ShowChinese(80,		123,	"�ܶ�",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
			case 3:	LCD_ShowChinese(80,		123,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
			case 4:	LCD_ShowChinese(80,		123,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
			case 5:	LCD_ShowChinese(80,		123,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
			case 6:	LCD_ShowChinese(80,		123,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
			case 7:	LCD_ShowChinese(80,		123,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
		}
	}
	
	
	//��ʾ��4������
	if(clock_time_hour[3] != 60)
	{
		LCD_ShowFloatNum1(5,	158,	clock_time_hour[2]+clock_time_min[2]*0.01,	4,	BLACK,	WHITE,	16);
		switch(clock_Data[2])
		{
			case 0:	LCD_ShowChinese(80,		153,	"ÿ��",	BLACK,	WHITE,	24,0);	break;//��ʾ��һ��
			case 1:	LCD_ShowChinese(80,		153,	"��һ",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
			case 2:	LCD_ShowChinese(80,		153,	"�ܶ�",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
			case 3:	LCD_ShowChinese(80,		153,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
			case 4:	LCD_ShowChinese(80,		153,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
			case 5:	LCD_ShowChinese(80,		153,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
			case 6:	LCD_ShowChinese(80,		153,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
			case 7:	LCD_ShowChinese(80,		153,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
		}
	}
	
	
	//��ʾ��5������
	if(clock_time_hour[4] != 60)
	{
		LCD_ShowFloatNum1(5,	188,	clock_time_hour[4]+clock_time_min[4]*0.01,	4,	BLACK,	WHITE,	16);
		switch(clock_Data[4])
		{
			case 0:	LCD_ShowChinese(80,		183,	"ÿ��",	BLACK,	WHITE,	24,0);	break;//��ʾ��һ��
			case 1:	LCD_ShowChinese(80,		183,	"��һ",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
			case 2:	LCD_ShowChinese(80,		183,	"�ܶ�",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
			case 3:	LCD_ShowChinese(80,		183,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
			case 4:	LCD_ShowChinese(80,		183,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
			case 5:	LCD_ShowChinese(80,		183,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
			case 6:	LCD_ShowChinese(80,		183,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
			case 7:	LCD_ShowChinese(80,		183,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
		}
	}
	//��ʾ��6������
	if(clock_time_hour[5] != 60)
	{
		LCD_ShowFloatNum1(5,	218,	clock_time_hour[5]+clock_time_min[5]*0.01,	4,	BLACK,	WHITE,	16);
		switch(clock_Data[5])
		{
			case 0:	LCD_ShowChinese(80,		213,	"ÿ��",	BLACK,	WHITE,	24,0);	break;//��ʾ��һ��
			case 1:	LCD_ShowChinese(80,		213,	"��һ",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
			case 2:	LCD_ShowChinese(80,		213,	"�ܶ�",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
			case 3:	LCD_ShowChinese(80,		213,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
			case 4:	LCD_ShowChinese(80,		213,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
			case 5:	LCD_ShowChinese(80,		213,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
			case 6:	LCD_ShowChinese(80,		213,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
			case 7:	LCD_ShowChinese(80,		213,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
		}
	}
}


/*******************************************
* @function: 	���ӵĹ���
* @input:			��
* @return:		��
* @author:		��С��
* @time:			2020.10.3
*******************************************/

void set_clock_fun(unsigned char i)
{
	unsigned char switch_value = 0;
	
	unsigned char Number_of_cycles_ = 1;
	
	unsigned char flag_ = 0;
	
	int value_1 = 6; //ʱ������
	
	int value_2 = 40; //��������
	
	int value_3 = 0; //���� 0����ÿ�� ��7��������
	
	if(clock_time_hour[i] != 60)
	{
		value_1 = clock_time_hour[i];
		
		value_2 = clock_time_min[i];

		value_3 = clock_Data[i];
	}
	
	LCD_Fill(0,		0,		LCD_W,	LCD_H,	WHITE); //��ʾ����ɰ�ɫˢ��
			
	LCD_ShowIntNum1(5,	65,	6,	2,	BLACK,	LGRAY,	32); //��ʾʱ����
				
	LCD_ShowChinese(37,		65,	"ʱ",	BLACK,	WHITE,	32,0); //��ʾʱ
	
	LCD_ShowIntNum1(69,	65,	40,	2,	BLACK,	WHITE,	32); //��ʾ����
	
	LCD_ShowChinese(101,		65,	"��",	BLACK,	WHITE,	32,0); //��ʾ��
	
	LCD_ShowChinese(37,		110,	"ÿ��",	BLACK,	WHITE,	32,0); //��ʾ��һ��
	
	LCD_ShowChinese(5,		210,	"ȷ��",	BLACK,	WHITE,	24,0); //��ʾȷ��
	
	LCD_ShowChinese(85,		210,	"ɾ��",	BLACK,	WHITE,	24,0); //��ʾɾ��
	
	while(1)
	{
		switch_value = Get_Key_value(1); //��ⰴ��
		
		if(switch_value == Button_1_pressed)// ���µ���ѡ��ʱ���������
		{
			Number_of_cycles_--;
			
			flag_ = 1;
			
			if(Number_of_cycles_<1)
			{
				Number_of_cycles_ = 5;
			}
		}
		
		if(switch_value == Button_3_pressed)// // ���µ���ѡ��ʱ���������
		{
			Number_of_cycles_++;
			
			flag_ = 1;
			
			if(Number_of_cycles_>5)
			{
				Number_of_cycles_ = 1;
			}
		}

		
		/*************************************
		
		��ʾ���֣���ʱ�����ں�ȷ��ɾ���ֿ�������ʾ��ÿ�ΰ������²Ž���ˢ��
		
		*****************************************/
		if(Number_of_cycles_ == 1 && flag_ == 1)
		{
			flag_ = 0;
			
			LCD_ShowChinese(85,		210,	"ɾ��",	BLACK,	WHITE,	24,0); //��ʾɾ��
			
			LCD_ShowIntNum1(5,	65,	value_1,	2,	BLACK,	LGRAY,	32); //��ʾʱ����
			
			LCD_ShowIntNum1(69,	65,	value_2,	2,	BLACK,	WHITE,	32); //��ʾ����
		}
		if(Number_of_cycles_ == 2 && flag_ == 1)
		{
			flag_ = 0;
			
			LCD_ShowIntNum1(5,	65,	value_1,	2,	BLACK,	WHITE,	32); //��ʾʱ����
			
			LCD_ShowIntNum1(69,	65,	value_2,	2,	BLACK,	LGRAY,	32); //��ʾ����
			
			switch(value_3)
			{
				case 0:	LCD_ShowChinese(37,		110,	"ÿ��",	BLACK,	WHITE,	32,0);  break;//��ʾ��һ��
				case 1:	LCD_ShowChinese(37,		110,	"��һ",	BLACK,	WHITE,	32,0);  break;//��ʾ��һ��
				case 2:	LCD_ShowChinese(37,		110,	"�ܶ�",	BLACK,	WHITE,	32,0);  break;//��ʾ��һ��
				case 3:	LCD_ShowChinese(37,		110,	"����",	BLACK,	WHITE,	32,0);  break;//��ʾ��һ��
				case 4:	LCD_ShowChinese(37,		110,	"����",	BLACK,	WHITE,	32,0);  break;//��ʾ��һ��
				case 5:	LCD_ShowChinese(37,		110,	"����",	BLACK,	WHITE,	32,0);  break;//��ʾ��һ��
				case 6:	LCD_ShowChinese(37,		110,	"����",	BLACK,	WHITE,	32,0);  break;//��ʾ��һ��
				case 7:	LCD_ShowChinese(37,		110,	"����",	BLACK,	WHITE,	32,0);  break;//��ʾ��һ��
			}
		}
		if(Number_of_cycles_ == 3 && flag_ == 1)
		{
			flag_ = 0;
			
			LCD_ShowIntNum1(69,	65,	value_2,	2,	BLACK,	WHITE,	32); //��ʾ����
			
			switch(value_3)
			{
				case 0:	LCD_ShowChinese(37,		110,	"ÿ��",	BLACK,	LGRAY,	32,0);  break;//��ʾ��һ��
				case 1:	LCD_ShowChinese(37,		110,	"��һ",	BLACK,	LGRAY,	32,0);  break;//��ʾ��һ��
				case 2:	LCD_ShowChinese(37,		110,	"�ܶ�",	BLACK,	LGRAY,	32,0);  break;//��ʾ��һ��
				case 3:	LCD_ShowChinese(37,		110,	"����",	BLACK,	LGRAY,	32,0);  break;//��ʾ��һ��
				case 4:	LCD_ShowChinese(37,		110,	"����",	BLACK,	LGRAY,	32,0);  break;//��ʾ��һ��
				case 5:	LCD_ShowChinese(37,		110,	"����",	BLACK,	LGRAY,	32,0);  break;//��ʾ��һ��
				case 6:	LCD_ShowChinese(37,		110,	"����",	BLACK,	LGRAY,	32,0);  break;//��ʾ��һ��
				case 7:	LCD_ShowChinese(37,		110,	"����",	BLACK,	LGRAY,	32,0);  break;//��ʾ��һ��
			}
			LCD_ShowChinese(5,		210,	"ȷ��",	BLACK,	WHITE,	24,0); //��ʾȷ��
		}
		if(Number_of_cycles_ == 4 && flag_ == 1)
		{
			flag_ = 0;
			
			switch(value_3)
			{
				case 0:	LCD_ShowChinese(37,		110,	"ÿ��",	BLACK,	WHITE,	32,0);  break;//��ʾ��һ��
				case 1:	LCD_ShowChinese(37,		110,	"��һ",	BLACK,	WHITE,	32,0);  break;//��ʾ��һ��
				case 2:	LCD_ShowChinese(37,		110,	"�ܶ�",	BLACK,	WHITE,	32,0);  break;//��ʾ��һ��
				case 3:	LCD_ShowChinese(37,		110,	"����",	BLACK,	WHITE,	32,0);  break;//��ʾ��һ��
				case 4:	LCD_ShowChinese(37,		110,	"����",	BLACK,	WHITE,	32,0);  break;//��ʾ��һ��
				case 5:	LCD_ShowChinese(37,		110,	"����",	BLACK,	WHITE,	32,0);  break;//��ʾ��һ��
				case 6:	LCD_ShowChinese(37,		110,	"����",	BLACK,	WHITE,	32,0);  break;//��ʾ��һ��
				case 7:	LCD_ShowChinese(37,		110,	"����",	BLACK,	WHITE,	32,0);  break;//��ʾ��һ��
			}
			
			LCD_ShowChinese(5,		210,	"ȷ��",	BLACK,	LGRAY,	24,0); //��ʾȷ��
			
			LCD_ShowChinese(85,		210,	"ɾ��",	BLACK,	WHITE,	24,0); //��ʾɾ��
		}
		if(Number_of_cycles_ == 5 && flag_ == 1)
		{
			flag_ = 0;
			
			LCD_ShowChinese(5,		210,	"ȷ��",	BLACK,	WHITE,	24,0); //��ʾȷ��
			
			LCD_ShowChinese(85,		210,	"ɾ��",	BLACK,	LGRAY,	24,0); //��ʾɾ��
			
			LCD_ShowIntNum1(5,	65,	value_1,	2,	BLACK,	WHITE,	32); //��ʾʱ����
		}
		
		
		//�Թ��ܽ��в�����
		if(Number_of_cycles_ == 1 && switch_value == Button_2_pressed) //��Сʱ���ڵĹ��ܽ��в���
		{
			while(1)
			{
				switch_value = Get_Key_value(1);
				
				LCD_ShowIntNum1(5,	65,	value_1,	2,	BLACK,	LGRAYBLUE,	32); //��ʾʱ���� //ѡ���Ժ��ɻ���ɫ
				
				if(switch_value == Button_1_pressed)
				{								
					value_1 --;									
				}
				if(switch_value == Button_3_pressed)
				{						
					value_1 ++;
				}
				if(value_1 < 0)
				{
					value_1 = 23;
				}
				if(value_1 > 23)
				{
					value_1 = 0;
				}
				if(switch_value == Button_2_pressed)
				{
					LCD_ShowIntNum1(5,	65,	value_1,	2,	BLACK,	LGRAY,	32); //��ʾʱ���� //ѡ���Ժ��ɻ���ɫ //��ѡ��֮�����ɫ�ı����
					
					break;
				}
			}
		}	
		if(Number_of_cycles_ == 2 && switch_value == Button_2_pressed) //�Է��ӵ��ڵĹ��ܽ��в���
		{
			while(1)
			{
				switch_value = Get_Key_value(1);
				
				LCD_ShowIntNum1(69,	65,	value_2,	2,	BLACK,	LGRAYBLUE,	32); //��ʾ���� //ѡ���Ժ��ɻ���ɫ
				
				if(switch_value == Button_1_pressed)
				{								
					value_2 --;									
				}
				if(switch_value == Button_3_pressed)
				{						
					value_2 ++;
				}
				if(value_2 < 0)
				{
					value_2 = 59;
				}
				if(value_2 > 59)
				{
					value_2 = 0;
				}
				if(switch_value == Button_2_pressed)
				{
					LCD_ShowIntNum1(69,	65,	value_2,	2,	BLACK,	LGRAY,	32);  //��ʾʱ���� //ѡ���Ժ��ɻ���ɫ //��ѡ��֮�����ɫ�ı����
					
					break;
				}
			}
		}	
		if(Number_of_cycles_ == 3 && switch_value == Button_2_pressed) //���������ڵĹ��ܽ��в���
		{
			while(1)
			{
				switch_value = Get_Key_value(1);
				
				switch(value_3)
				{
					case 0:	LCD_ShowChinese(37,		110,	"ÿ��",	BLACK,	LGRAYBLUE,	32,0);  break;//��ʾ��һ��
					case 1:	LCD_ShowChinese(37,		110,	"��һ",	BLACK,	LGRAYBLUE,	32,0);  break;//��ʾ��һ��
					case 2:	LCD_ShowChinese(37,		110,	"�ܶ�",	BLACK,	LGRAYBLUE,	32,0);  break;//��ʾ��һ��
					case 3:	LCD_ShowChinese(37,		110,	"����",	BLACK,	LGRAYBLUE,	32,0);  break;//��ʾ��һ��
					case 4:	LCD_ShowChinese(37,		110,	"����",	BLACK,	LGRAYBLUE,	32,0);  break;//��ʾ��һ��
					case 5:	LCD_ShowChinese(37,		110,	"����",	BLACK,	LGRAYBLUE,	32,0);  break;//��ʾ��һ��
					case 6:	LCD_ShowChinese(37,		110,	"����",	BLACK,	LGRAYBLUE,	32,0);  break;//��ʾ��һ��
					case 7:	LCD_ShowChinese(37,		110,	"����",	BLACK,	LGRAYBLUE,	32,0);  break;//��ʾ��һ��
				}
				
				if(switch_value == Button_1_pressed)
				{								
					value_3 --;									
				}
				if(switch_value == Button_3_pressed)
				{						
					value_3 ++;
				}
				if(value_3 < 0)
				{
					value_3 = 7;
				}
				if(value_3 > 7)
				{
					value_3 = 0;
				}
				if(switch_value == Button_2_pressed)
				{
					switch(value_3)
					{
						case 0:	LCD_ShowChinese(37,		110,	"ÿ��",	BLACK,	LGRAY,	32,0);  break;//��ʾ��һ��
						case 1:	LCD_ShowChinese(37,		110,	"��һ",	BLACK,	LGRAY,	32,0);  break;//��ʾ��һ��
						case 2:	LCD_ShowChinese(37,		110,	"�ܶ�",	BLACK,	LGRAY,	32,0);  break;//��ʾ��һ��
						case 3:	LCD_ShowChinese(37,		110,	"����",	BLACK,	LGRAY,	32,0);  break;//��ʾ��һ��
						case 4:	LCD_ShowChinese(37,		110,	"����",	BLACK,	LGRAY,	32,0);  break;//��ʾ��һ��
						case 5:	LCD_ShowChinese(37,		110,	"����",	BLACK,	LGRAY,	32,0);  break;//��ʾ��һ��
						case 6:	LCD_ShowChinese(37,		110,	"����",	BLACK,	LGRAY,	32,0);  break;//��ʾ��һ��
						case 7:	LCD_ShowChinese(37,		110,	"����",	BLACK,	LGRAY,	32,0);  break;//��ʾ��һ��
					}
				
					break;
				}
			}
		}	
		if(Number_of_cycles_ == 4 && switch_value == Button_2_pressed) //�����˹��ܵ����ã�����ѭ�����ص����ӵĽ���
		{
			clock_time_hour[i] = value_1;
			
			clock_time_min[i] = value_2; //�����úõ����ӵ����ڸ��µ������ﱣ������
			
			clock_Data[i] = value_3; //�����úõ�ʱ����µ������ﱣ������
			
//			value_1 = 6; //����ֵ�ָ���֮ǰ��״̬ ��Ϊ��һ���½�������׼��
//			
//			value_2 = 40;
			
			value_1 = sTime.Hours;
	
			value_2 = sTime.Minutes;
			
			value_3 = 0;

			break; //�˳�
		}	
		if(Number_of_cycles_ == 5 && switch_value == Button_2_pressed)  //�����˹��ܵ����ã�����ѭ�����ص����ӵĽ���
		{
			clock_time_hour[0] = 70; //����������ǲ��������ʮ�������¼�������Ч���¼����ж�Ϊ��Ч���Ӿͻᱻɾ��
			
			value_1 = sTime.Hours;
	
			value_2 = sTime.Minutes;		
			
//			value_1 = 6; //����ֵ�ָ���֮ǰ��״̬ ��Ϊ��һ���½�������׼��
//			
//			value_2 = 40;
			
			value_3 = 0;
			
			clock_time_hour[i] = 60;
			
		 //�˳�ѵ��֮���ص���ʼ�ĵط�
			
			break;
		}		
	}
}


/*******************************************
* @function: 	���ӵĹ���
* @input:			��
* @return:		��
* @author:		��С��
* @time:			2020.10.3
*******************************************/


unsigned char display_clock_function(unsigned char Number_of_cycles,unsigned char flag__)
{
	//��ʾ�½��ͷ���
	if(Number_of_cycles == 1 && flag__ == 1)
	{
//		flag__ = 0; //������Ļˢ��
		
		LCD_Fill(0,		211,LCD_W,240,WHITE); //��ʾ����ɻ�ɫˢ��
		
		//��ʾ��6������
		if(clock_time_hour[5] != 60)
		{
			LCD_ShowFloatNum1(5,	218,	clock_time_hour[5]+clock_time_min[5]*0.01,	4,	BLACK,	WHITE,	16);
			switch(clock_Data[5])
			{
				case 0:	LCD_ShowChinese(80,		213,	"ÿ��",	BLACK,	WHITE,	24,0);	break;//��ʾ��һ��
				case 1:	LCD_ShowChinese(80,		213,	"��һ",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 2:	LCD_ShowChinese(80,		213,	"�ܶ�",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 3:	LCD_ShowChinese(80,		213,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 4:	LCD_ShowChinese(80,		213,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 5:	LCD_ShowChinese(80,		213,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 6:	LCD_ShowChinese(80,		213,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 7:	LCD_ShowChinese(80,		213,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
			}
		}
		
		LCD_Fill(0,		0,LCD_W,30,LGRAY); //��ʾ����ɻ�ɫˢ��
		
		LCD_ShowChinese(0,		3,	"����",	BLACK,	LGRAY,24,0);
		
		LCD_Fill(0,		31,LCD_W,60,WHITE); //��ʾ����ɻ�ɫˢ��
		
		LCD_ShowChinese(0,		33,	"�½�",	BLACK,	WHITE,24,0);
	}
	
	
	if(Number_of_cycles == 2 && flag__ == 1)
	{
//		flag__ = 0; //������Ļˢ��
													
		LCD_Fill(0,		0,LCD_W,30,WHITE); //��ʾ����ɻ�ɫˢ��
		
		LCD_ShowChinese(0,		3,	"����",	BLACK,	WHITE,24,0);
		
		LCD_Fill(0,		31,LCD_W,60,LGRAY); //��ʾ����ɻ�ɫˢ��	
		
		LCD_ShowChinese(0,		33,	"�½�",	BLACK,	LGRAY,24,0);
		
		LCD_Fill(0,		61,LCD_W,90,WHITE); //��ʾ����ɻ�ɫˢ��
		//��ʾ��һ������
		if(clock_time_hour[0] != 60)
		{
			LCD_ShowFloatNum1(5,	68,	clock_time_hour[0]+clock_time_min[0]*0.01,	4,	BLACK,	WHITE,	16);
			
			switch(clock_Data[0])
			{
				case 0:	LCD_ShowChinese(80,		63,	"ÿ��",	BLACK,	WHITE,	24,0);	break;//��ʾ��һ��
				case 1:	LCD_ShowChinese(80,		63,	"��һ",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 2:	LCD_ShowChinese(80,		63,	"�ܶ�",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 3:	LCD_ShowChinese(80,		63,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 4:	LCD_ShowChinese(80,		63,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 5:	LCD_ShowChinese(80,		63,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 6:	LCD_ShowChinese(80,		63,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 7:	LCD_ShowChinese(80,		63,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
			}
			//LCD_ShowChinese(80,		63,	clock_time_hour[0],	BLACK,	WHITE,24,0);
		}
	}
	
	//��ʾ���ӵ��б�
	if(Number_of_cycles == 3 && flag__ == 1)
	{
//		flag__ = 0; //������Ļˢ��

		LCD_Fill(0,		31,LCD_W,60,WHITE); //��ʾ����ɻ�ɫˢ��
		
		LCD_ShowChinese(0,		33,	"�½�",	BLACK,	WHITE,24,0);
		
		LCD_Fill(0,		61,LCD_W,90,LGRAY); //��ʾ����ɻ�ɫˢ��
		
		//��ʾ��һ������
		if(clock_time_hour[0] != 60)
		{
			LCD_ShowFloatNum1(5,	68,	clock_time_hour[0]+clock_time_min[0]*0.01,	4,	BLACK,	LGRAY,	16);
			
			switch(clock_Data[0])
			{
				case 0:	LCD_ShowChinese(80,		63,	"ÿ��",	BLACK,	LGRAY,	24,0);	break;//��ʾ��һ��
				case 1:	LCD_ShowChinese(80,		63,	"��һ",	BLACK,	LGRAY,	24,0);  break;//��ʾ��һ��
				case 2:	LCD_ShowChinese(80,		63,	"�ܶ�",	BLACK,	LGRAY,	24,0);  break;//��ʾ��һ��
				case 3:	LCD_ShowChinese(80,		63,	"����",	BLACK,	LGRAY,	24,0);  break;//��ʾ��һ��
				case 4:	LCD_ShowChinese(80,		63,	"����",	BLACK,	LGRAY,	24,0);  break;//��ʾ��һ��
				case 5:	LCD_ShowChinese(80,		63,	"����",	BLACK,	LGRAY,	24,0);  break;//��ʾ��һ��
				case 6:	LCD_ShowChinese(80,		63,	"����",	BLACK,	LGRAY,	24,0);  break;//��ʾ��һ��
				case 7:	LCD_ShowChinese(80,		63,	"����",	BLACK,	LGRAY,	24,0);  break;//��ʾ��һ��
			}
		}
		
		LCD_Fill(0,		91,LCD_W,120,WHITE); //��ʾ����ɻ�ɫˢ��
		//��ʾ��2������
		if(clock_time_hour[1] != 60)
		{
			LCD_ShowFloatNum1(5,	98,	clock_time_hour[1]+clock_time_min[1]*0.01,	4,	BLACK,	WHITE,	16);
			switch(clock_Data[1])
			{
				case 0:	LCD_ShowChinese(80,		93,	"ÿ��",	BLACK,	WHITE,	24,0);	break;//��ʾ��һ��
				case 1:	LCD_ShowChinese(80,		93,	"��һ",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 2:	LCD_ShowChinese(80,		93,	"�ܶ�",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 3:	LCD_ShowChinese(80,		93,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 4:	LCD_ShowChinese(80,		93,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 5:	LCD_ShowChinese(80,		93,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 6:	LCD_ShowChinese(80,		93,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 7:	LCD_ShowChinese(80,		93,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
			}
		}
	}
	
	
	
	if(Number_of_cycles == 4 && flag__ == 1)
	{
//		flag__ = 0; //������Ļˢ��
		
		LCD_Fill(0,		61,LCD_W,90,WHITE); //��ʾ����ɻ�ɫˢ��

		//��ʾ��һ������
		if(clock_time_hour[0] != 60)
		{
			LCD_ShowFloatNum1(5,	68,	clock_time_hour[0]+clock_time_min[0]*0.01,	4,	BLACK,	WHITE,	16);
			
			switch(clock_Data[0])
			{
				case 0:	LCD_ShowChinese(80,		63,	"ÿ��",	BLACK,	WHITE,	24,0);	break;//��ʾ��һ��
				case 1:	LCD_ShowChinese(80,		63,	"��һ",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 2:	LCD_ShowChinese(80,		63,	"�ܶ�",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 3:	LCD_ShowChinese(80,		63,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 4:	LCD_ShowChinese(80,		63,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 5:	LCD_ShowChinese(80,		63,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 6:	LCD_ShowChinese(80,		63,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 7:	LCD_ShowChinese(80,		63,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
			}
		}	
		
		LCD_Fill(0,		91,LCD_W,120,LGRAY); //��ʾ����ɻ�ɫˢ��
		//��ʾ��2������
		if(clock_time_hour[1] != 60)
		{
			LCD_ShowFloatNum1(5,	98,	clock_time_hour[1]+clock_time_min[1]*0.01,	4,	BLACK,	LGRAY,	16);
			switch(clock_Data[1])
			{
				case 0:	LCD_ShowChinese(80,		93,	"ÿ��",	BLACK,	LGRAY,	24,0);	break;//��ʾ��һ��
				case 1:	LCD_ShowChinese(80,		93,	"��һ",	BLACK,	LGRAY,	24,0);  break;//��ʾ��һ��
				case 2:	LCD_ShowChinese(80,		93,	"�ܶ�",	BLACK,	LGRAY,	24,0);  break;//��ʾ��һ��
				case 3:	LCD_ShowChinese(80,		93,	"����",	BLACK,	LGRAY,	24,0);  break;//��ʾ��һ��
				case 4:	LCD_ShowChinese(80,		93,	"����",	BLACK,	LGRAY,	24,0);  break;//��ʾ��һ��
				case 5:	LCD_ShowChinese(80,		93,	"����",	BLACK,	LGRAY,	24,0);  break;//��ʾ��һ��
				case 6:	LCD_ShowChinese(80,		93,	"����",	BLACK,	LGRAY,	24,0);  break;//��ʾ��һ��
				case 7:	LCD_ShowChinese(80,		93,	"����",	BLACK,	LGRAY,	24,0);  break;//��ʾ��һ��
			}
		}
		
		
		LCD_Fill(0,		121,LCD_W,150,WHITE); //��ʾ����ɻ�ɫˢ��
		//��ʾ��3������
		if(clock_time_hour[2] != 60)
		{
			LCD_ShowFloatNum1(5,	128,	clock_time_hour[2]+clock_time_min[2]*0.01,	4,	BLACK,	WHITE,	16);
			switch(clock_Data[2])
			{
				case 0:	LCD_ShowChinese(80,		123,	"ÿ��",	BLACK,	WHITE,	24,0);	break;//��ʾ��һ��
				case 1:	LCD_ShowChinese(80,		123,	"��һ",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 2:	LCD_ShowChinese(80,		123,	"�ܶ�",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 3:	LCD_ShowChinese(80,		123,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 4:	LCD_ShowChinese(80,		123,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 5:	LCD_ShowChinese(80,		123,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 6:	LCD_ShowChinese(80,		123,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 7:	LCD_ShowChinese(80,		123,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
			}
		}
	}
	
	if(Number_of_cycles == 5 && flag__ == 1)
	{
//		flag__ = 0; //������Ļˢ��
		
		LCD_Fill(0,		91,LCD_W,120,WHITE); //��ʾ����ɻ�ɫˢ��
		//��ʾ��2������
		if(clock_time_hour[1] != 60)
		{
			LCD_ShowFloatNum1(5,	98,	clock_time_hour[1]+clock_time_min[1]*0.01,	4,	BLACK,	WHITE,	16);
			switch(clock_Data[1])
			{
				case 0:	LCD_ShowChinese(80,		93,	"ÿ��",	BLACK,	WHITE,	24,0);	break;//��ʾ��һ��
				case 1:	LCD_ShowChinese(80,		93,	"��һ",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 2:	LCD_ShowChinese(80,		93,	"�ܶ�",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 3:	LCD_ShowChinese(80,		93,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 4:	LCD_ShowChinese(80,		93,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 5:	LCD_ShowChinese(80,		93,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 6:	LCD_ShowChinese(80,		93,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 7:	LCD_ShowChinese(80,		93,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
			}
//			LCD_ShowFloatNum1(5,	98,	6.39,	4,	BLACK,	WHITE,	16);
//					
//			LCD_ShowChinese(80,		93,	"ÿ��",	BLACK,	WHITE,24,0);
		}
		
		LCD_Fill(0,		121,LCD_W,150,LGRAY); //��ʾ����ɻ�ɫˢ��
		//��ʾ��3������
		if(clock_time_hour[2] != 60)
		{
			LCD_ShowFloatNum1(5,	128,	clock_time_hour[2]+clock_time_min[2]*0.01,	4,	BLACK,	LGRAY,	16);
			switch(clock_Data[2])
			{
				case 0:	LCD_ShowChinese(80,		123,	"ÿ��",	BLACK,	LGRAY,	24,0);	break;//��ʾ��һ��
				case 1:	LCD_ShowChinese(80,		123,	"��һ",	BLACK,	LGRAY,	24,0);  break;//��ʾ��һ��
				case 2:	LCD_ShowChinese(80,		123,	"�ܶ�",	BLACK,	LGRAY,	24,0);  break;//��ʾ��һ��
				case 3:	LCD_ShowChinese(80,		123,	"����",	BLACK,	LGRAY,	24,0);  break;//��ʾ��һ��
				case 4:	LCD_ShowChinese(80,		123,	"����",	BLACK,	LGRAY,	24,0);  break;//��ʾ��һ��
				case 5:	LCD_ShowChinese(80,		123,	"����",	BLACK,	LGRAY,	24,0);  break;//��ʾ��һ��
				case 6:	LCD_ShowChinese(80,		123,	"����",	BLACK,	LGRAY,	24,0);  break;//��ʾ��һ��
				case 7:	LCD_ShowChinese(80,		123,	"����",	BLACK,	LGRAY,	24,0);  break;//��ʾ��һ��
			}
//			LCD_ShowFloatNum1(5,	128,	6.39,	4,	BLACK,	LGRAY,	16);
//					
//			LCD_ShowChinese(80,		123,	"ÿ��",	BLACK,	LGRAY,24,0);
		}
		
		LCD_Fill(0,		151,LCD_W,180,WHITE); //��ʾ����ɻ�ɫˢ��
		//��ʾ��4������
		if(clock_time_hour[3] != 60)
		{
			LCD_ShowFloatNum1(5,	158,	clock_time_hour[3]+clock_time_min[3]*0.01,	4,	BLACK,	WHITE,	16);
			switch(clock_Data[3])
			{
				case 0:	LCD_ShowChinese(80,		153,	"ÿ��",	BLACK,	WHITE,	24,0);	break;//��ʾ��һ��
				case 1:	LCD_ShowChinese(80,		153,	"��һ",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 2:	LCD_ShowChinese(80,		153,	"�ܶ�",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 3:	LCD_ShowChinese(80,		153,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 4:	LCD_ShowChinese(80,		153,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 5:	LCD_ShowChinese(80,		153,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 6:	LCD_ShowChinese(80,		153,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 7:	LCD_ShowChinese(80,		153,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
			}
//			LCD_ShowFloatNum1(5,	158,	6.39,	4,	BLACK,	WHITE,	16);
//					
//			LCD_ShowChinese(80,		153,	"ÿ��",	BLACK,	WHITE,24,0);
		}
	}
	
	if(Number_of_cycles == 6 && flag__ == 1)
	{
//		flag__ = 0; //������Ļˢ��
		
		LCD_Fill(0,		121,LCD_W,150,WHITE); //��ʾ����ɻ�ɫˢ��
		//��ʾ��3������
		if(clock_time_hour[2] != 60)
		{
			LCD_ShowFloatNum1(5,	128,	clock_time_hour[2]+clock_time_min[2]*0.01,	4,	BLACK,	WHITE,	16);
			switch(clock_Data[2])
			{
				case 0:	LCD_ShowChinese(80,		123,	"ÿ��",	BLACK,	WHITE,	24,0);	break;//��ʾ��һ��
				case 1:	LCD_ShowChinese(80,		123,	"��һ",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 2:	LCD_ShowChinese(80,		123,	"�ܶ�",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 3:	LCD_ShowChinese(80,		123,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 4:	LCD_ShowChinese(80,		123,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 5:	LCD_ShowChinese(80,		123,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 6:	LCD_ShowChinese(80,		123,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 7:	LCD_ShowChinese(80,		123,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
			}
//			LCD_ShowFloatNum1(5,	128,	6.39,	4,	BLACK,	WHITE,	16);
//					
//			LCD_ShowChinese(80,		123,	"ÿ��",	BLACK,	WHITE,24,0);
		}
		
		LCD_Fill(0,		151,LCD_W,180,LGRAY); //��ʾ����ɻ�ɫˢ��
		//��ʾ��4������
		if(clock_time_hour[3] != 60)
		{
			LCD_ShowFloatNum1(5,	158,	clock_time_hour[3]+clock_time_min[3]*0.01,	4,	BLACK,	LGRAY,	16);
			switch(clock_Data[3])
			{
				case 0:	LCD_ShowChinese(80,		153,	"ÿ��",	BLACK,	LGRAY,	24,0);	break;//��ʾ��һ��
				case 1:	LCD_ShowChinese(80,		153,	"��һ",	BLACK,	LGRAY,	24,0);  break;//��ʾ��һ��
				case 2:	LCD_ShowChinese(80,		153,	"�ܶ�",	BLACK,	LGRAY,	24,0);  break;//��ʾ��һ��
				case 3:	LCD_ShowChinese(80,		153,	"����",	BLACK,	LGRAY,	24,0);  break;//��ʾ��һ��
				case 4:	LCD_ShowChinese(80,		153,	"����",	BLACK,	LGRAY,	24,0);  break;//��ʾ��һ��
				case 5:	LCD_ShowChinese(80,		153,	"����",	BLACK,	LGRAY,	24,0);  break;//��ʾ��һ��
				case 6:	LCD_ShowChinese(80,		153,	"����",	BLACK,	LGRAY,	24,0);  break;//��ʾ��һ��
				case 7:	LCD_ShowChinese(80,		153,	"����",	BLACK,	LGRAY,	24,0);  break;//��ʾ��һ��
			}
//			LCD_ShowFloatNum1(5,	158,	6.39,	4,	BLACK,	LGRAY,	16);
//					
//			LCD_ShowChinese(80,		153,	"ÿ��",	BLACK,	LGRAY,24,0);
		}
		
		LCD_Fill(0,		181,LCD_W,210,WHITE); //��ʾ����ɻ�ɫˢ��
		//��ʾ��5������
		if(clock_time_hour[4] != 60)
		{
			LCD_ShowFloatNum1(5,	188,	clock_time_hour[4]+clock_time_min[4]*0.01,	4,	BLACK,	WHITE,	16);
			switch(clock_Data[4])
			{
				case 0:	LCD_ShowChinese(80,		183,	"ÿ��",	BLACK,	WHITE,	24,0);	break;//��ʾ��һ��
				case 1:	LCD_ShowChinese(80,		183,	"��һ",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 2:	LCD_ShowChinese(80,		183,	"�ܶ�",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 3:	LCD_ShowChinese(80,		183,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 4:	LCD_ShowChinese(80,		183,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 5:	LCD_ShowChinese(80,		183,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 6:	LCD_ShowChinese(80,		183,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 7:	LCD_ShowChinese(80,		183,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
			}
//			LCD_ShowFloatNum1(5,	188,	6.39,	4,	BLACK,	WHITE,	16);
//					
//			LCD_ShowChinese(80,		183,	"ÿ��",	BLACK,	WHITE,24,0);
		}
	}
	
	if(Number_of_cycles == 7 && flag__ == 1)
	{
//		flag__ = 0; //������Ļˢ��
		
		LCD_Fill(0,		151,LCD_W,180,WHITE); //��ʾ����ɻ�ɫˢ��
		//��ʾ��4������
		if(clock_time_hour[3] != 60)
		{
			LCD_ShowFloatNum1(5,	158,	clock_time_hour[3]+clock_time_min[3]*0.01,	4,	BLACK,	WHITE,	16);
			switch(clock_Data[3])
			{
				case 0:	LCD_ShowChinese(80,		153,	"ÿ��",	BLACK,	WHITE,	24,0);	break;//��ʾ��һ��
				case 1:	LCD_ShowChinese(80,		153,	"��һ",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 2:	LCD_ShowChinese(80,		153,	"�ܶ�",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 3:	LCD_ShowChinese(80,		153,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 4:	LCD_ShowChinese(80,		153,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 5:	LCD_ShowChinese(80,		153,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 6:	LCD_ShowChinese(80,		153,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 7:	LCD_ShowChinese(80,		153,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
			}
//			LCD_ShowFloatNum1(5,	158,	6.39,	4,	BLACK,	WHITE,	16);
//					
//			LCD_ShowChinese(80,		153,	"ÿ��",	BLACK,	WHITE,24,0);
		}
		
		LCD_Fill(0,		181,LCD_W,210,LGRAY); //��ʾ����ɻ�ɫˢ��
		//��ʾ��5������
		if(clock_time_hour[4] != 60)
		{
			LCD_ShowFloatNum1(5,	188,	clock_time_hour[4]+clock_time_min[4]*0.01,	4,	BLACK,	LGRAY,	16);
			switch(clock_Data[4])
			{
				case 0:	LCD_ShowChinese(80,		183,	"ÿ��",	BLACK,	LGRAY,	24,0);	break;//��ʾ��һ��
				case 1:	LCD_ShowChinese(80,		183,	"��һ",	BLACK,	LGRAY,	24,0);  break;//��ʾ��һ��
				case 2:	LCD_ShowChinese(80,		183,	"�ܶ�",	BLACK,	LGRAY,	24,0);  break;//��ʾ��һ��
				case 3:	LCD_ShowChinese(80,		183,	"����",	BLACK,	LGRAY,	24,0);  break;//��ʾ��һ��
				case 4:	LCD_ShowChinese(80,		183,	"����",	BLACK,	LGRAY,	24,0);  break;//��ʾ��һ��
				case 5:	LCD_ShowChinese(80,		183,	"����",	BLACK,	LGRAY,	24,0);  break;//��ʾ��һ��
				case 6:	LCD_ShowChinese(80,		183,	"����",	BLACK,	LGRAY,	24,0);  break;//��ʾ��һ��
				case 7:	LCD_ShowChinese(80,		183,	"����",	BLACK,	LGRAY,	24,0);  break;//��ʾ��һ��
			}
//			LCD_ShowFloatNum1(5,	188,	6.39,	4,	BLACK,	LGRAY,	16);
//					
//			LCD_ShowChinese(80,		183,	"ÿ��",	BLACK,	LGRAY,24,0);
		}
		
		LCD_Fill(0,		211,LCD_W,240,WHITE); //��ʾ����ɻ�ɫˢ��
		//��ʾ��6������
		if(clock_time_hour[5] != 60)
		{
			LCD_ShowFloatNum1(5,	218,	clock_time_hour[5]+clock_time_min[5]*0.01,	4,	BLACK,	WHITE,	16);
			
			switch(clock_Data[5])
			{
				case 0:	LCD_ShowChinese(80,		213,	"ÿ��",	BLACK,	WHITE,	24,0);	break;//��ʾ��һ��
				case 1:	LCD_ShowChinese(80,		213,	"��һ",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 2:	LCD_ShowChinese(80,		213,	"�ܶ�",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 3:	LCD_ShowChinese(80,		213,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 4:	LCD_ShowChinese(80,		213,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 5:	LCD_ShowChinese(80,		213,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 6:	LCD_ShowChinese(80,		213,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 7:	LCD_ShowChinese(80,		213,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
			}
//			LCD_ShowFloatNum1(5,	218,	6.39,	4,	BLACK,	WHITE,	16);
//					
//			LCD_ShowChinese(80,		213,	"ÿ��",	BLACK,	WHITE,24,0);
		}
	}
	
	if(Number_of_cycles == 8 && flag__ == 1)
	{
//		flag__ = 0; //������Ļˢ��
		
		LCD_Fill(0,		181,LCD_W,210,WHITE); //��ʾ����ɻ�ɫˢ��
		//��ʾ��5������
		if(clock_time_hour[4] != 60)
		{
			LCD_ShowFloatNum1(5,	188,	clock_time_hour[4]+clock_time_min[4]*0.01,	4,	BLACK,	WHITE,	16);
			
			switch(clock_Data[4])
			{
				case 0:	LCD_ShowChinese(80,		183,	"ÿ��",	BLACK,	WHITE,	24,0);	break;//��ʾ��һ��
				case 1:	LCD_ShowChinese(80,		183,	"��һ",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 2:	LCD_ShowChinese(80,		183,	"�ܶ�",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 3:	LCD_ShowChinese(80,		183,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 4:	LCD_ShowChinese(80,		183,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 5:	LCD_ShowChinese(80,		183,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 6:	LCD_ShowChinese(80,		183,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
				case 7:	LCD_ShowChinese(80,		183,	"����",	BLACK,	WHITE,	24,0);  break;//��ʾ��һ��
			}
//			LCD_ShowFloatNum1(5,	188,	6.39,	4,	BLACK,	WHITE,	16);
//					
//			LCD_ShowChinese(80,		183,	"ÿ��",	BLACK,	WHITE,24,0);
		}
		
		LCD_Fill(0,		211,LCD_W,240,LGRAY); //��ʾ����ɻ�ɫˢ��
		//��ʾ��6������
		if(clock_time_hour[5] != 60)
		{
			LCD_ShowFloatNum1(5,	218,	clock_time_hour[5]+clock_time_min[5]*0.01,	4,	BLACK,	LGRAY,	16);
			
			switch(clock_Data[5])
			{
				case 0:	LCD_ShowChinese(80,		213,	"ÿ��",	BLACK,	LGRAY,	24,0);	break;//��ʾ��һ��
				case 1:	LCD_ShowChinese(80,		213,	"��һ",	BLACK,	LGRAY,	24,0);  break;//��ʾ��һ��
				case 2:	LCD_ShowChinese(80,		213,	"�ܶ�",	BLACK,	LGRAY,	24,0);  break;//��ʾ��һ��
				case 3:	LCD_ShowChinese(80,		213,	"����",	BLACK,	LGRAY,	24,0);  break;//��ʾ��һ��
				case 4:	LCD_ShowChinese(80,		213,	"����",	BLACK,	LGRAY,	24,0);  break;//��ʾ��һ��
				case 5:	LCD_ShowChinese(80,		213,	"����",	BLACK,	LGRAY,	24,0);  break;//��ʾ��һ��
				case 6:	LCD_ShowChinese(80,		213,	"����",	BLACK,	LGRAY,	24,0);  break;//��ʾ��һ��
				case 7:	LCD_ShowChinese(80,		213,	"����",	BLACK,	LGRAY,	24,0);  break;//��ʾ��һ��
			}
		}
		
		LCD_Fill(0,		0,LCD_W,30,WHITE); //��ʾ����ɻ�ɫˢ��
		
		LCD_ShowChinese(0,		3,	"����",	BLACK,	WHITE,24,0);
		
	}
	return 0;
}
/*******************************************
* @function: 	���ӵĹ���
* @input:			��
* @return:		��
* @author:		��С��
* @time:			2020.10.3
*******************************************/

void clock_function(void)
{
//	static unsigned char Number_of_cycles = function_clock;
	
	unsigned char switch_value;
		
	static unsigned char flag__ = 0;
	
//	static unsigned char flag_ = 0;
	
	static unsigned char Number_of_cycles = 1;
	
//	static unsigned char Number_of_cycles_ = 1;
	
	unsigned char i = 0;
	
	LCD_Fill(0,0,LCD_W,LCD_H,BLACK); //�����������
	
	printf("����������app\r\n");

	clock_begin_display(); //�����ӵĿ�ʼ�ı�񻯽������ˢ��
	
	flag__ = 1; //������Ļˢ��
	
	while(1)
	{
		switch_value = Get_Key_value(1);
		
		if(switch_value == Button_3_pressed)
		{
			Number_of_cycles++;
			
			flag__ = 1; //������Ļˢ��
			
			if(Number_of_cycles > 8)
			{
				Number_of_cycles = 1;
			}
		}
		
		if(switch_value == Button_1_pressed)
		{
			Number_of_cycles--;
			
			flag__ = 1; //������Ļˢ��
			
			if(Number_of_cycles<1)
			{
				Number_of_cycles = 8;
			}
		}
		
		//��ʾ��ˢ�½��档�������غ��½��Լ������б�
		flag__ = display_clock_function(Number_of_cycles,flag__); //����ˢ��
		
		//�ж���Ҫ����
		if(switch_value == Button_2_pressed && Number_of_cycles == 1)
		{
//				flag = 1;
			Number_of_cycles = 1;
			
			break;
		}		
		//�ж�ѡ�����½���ť
		if(switch_value == Button_2_pressed && Number_of_cycles == 2)
		{
			for(i=0;i<6;i++)
			{
				if(clock_time_hour[i] == 60)
				{
					
					//�����������ӵĽ���
					set_clock_fun(i);
					
					i=0;
					
					//�Ƴ�����Ҫ����ˢ�½���
					clock_begin_display();
								
					flag__ = 1; //������Ļˢ��
					
					break;
				}
			}
			for(i=0;i<6;i++)
			{
				printf("%d  ",clock_time_hour[i]);
			}
			printf("\r\n");
		}
			
		//�ж�ѡ���˵�һ������
		if(switch_value == Button_2_pressed && Number_of_cycles == 3)
		{
			if(clock_time_hour[0] != 60)
			{
				set_clock_fun(0);
				
				clock_begin_display();
				
				Number_of_cycles = 1;	
			}
			
		}
		//�ж�ѡ���˵�2������
		if(switch_value == Button_2_pressed && Number_of_cycles == 4)
		{
			if(clock_time_hour[1] != 60)
			{
				set_clock_fun(1);
				
				clock_begin_display();
				
				Number_of_cycles = 1;	
			}
			
		}
		//�ж�ѡ���˵�3������
		if(switch_value == Button_2_pressed && Number_of_cycles == 5)
		{
			if(clock_time_hour[2] != 60)
			{
				set_clock_fun(2);
				
				clock_begin_display();
				
				Number_of_cycles = 1;	
			}
			
		}
		//�ж�ѡ���˵�4������
		if(switch_value == Button_2_pressed && Number_of_cycles == 6)
		{
			if(clock_time_hour[3] != 60)
			{
				set_clock_fun(3);
				
				clock_begin_display();
				
				Number_of_cycles = 1;	
			}
			
		}
		//�ж�ѡ���˵�5������
		if(switch_value == Button_2_pressed && Number_of_cycles == 7)
		{
			if(clock_time_hour[4] != 60)
			{
				set_clock_fun(4);
				
				clock_begin_display();
				
				Number_of_cycles = 1;
			}
			
		}
		//�ж�ѡ���˵�6������
		if(switch_value == Button_2_pressed && Number_of_cycles == 8)
		{
			if(clock_time_hour[5] != 60)
			{
				set_clock_fun(5);
				
				clock_begin_display();
				
				Number_of_cycles = 1;
			}
			
		}
	}
}
	
/*******************************************
* @function: 	���ӵĹ���
* @input:			��
* @return:		��
* @author:		��С��
* @time:			2020.10.3
*******************************************/
void light_function(void)
{
	unsigned char switch_value;
	
	LCD_Fill(0,0,LCD_W,LCD_H,WHITE); //����Ļ��ɴ��ɫ
	
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, 600); //����PWM��ռ�ձȣ����ڱ��� //����Ļ���ڳɸ���
	
	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);	
	
	while(1)
	{
		switch_value = Get_Key_value(1);
		
		if(switch_value == Button_3_pressed || switch_value == Button_2_pressed || switch_value == Button_1_pressed)
		{
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, 70); //����PWM��ռ�ձȣ����ڱ���
			
			HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
			
			break;
		}
	}
	MENU_light();

}	



/*******************************************
* @function: 	����ʱ��Ĺ��ܽ��湦��
* @input:			��
* @return:		��
* @author:		��С��
* @time:			2020.10.24
*******************************************/
void set_time_function(void)
{
	unsigned char switch_value = 0;
	
	unsigned char Number_of_cycles_ = 1;
	
	unsigned char flag_ = 0;
	
	int value_1 = 0; //ʱ������
	
	int value_2 = 0; //��������
	
	value_1 = sTime.Hours;
	
	value_2 = sTime.Minutes;
	
	LCD_Fill(0,		0,		LCD_W,	LCD_H,	WHITE); //��ʾ����ɰ�ɫˢ��
			
	LCD_ShowIntNum1(5,	65,	value_1,	2,	BLACK,	LGRAY,	32); //��ʾʱ����
				
	LCD_ShowChinese(37,		65,	"ʱ",	BLACK,	WHITE,	32,0); //��ʾʱ
	
	LCD_ShowIntNum1(69,	65,	value_2,	2,	BLACK,	WHITE,	32); //��ʾ����
	
	LCD_ShowChinese(101,		65,	"��",	BLACK,	WHITE,	32,0); //��ʾ��
		
	LCD_ShowChinese(5,		210,	"ȷ��",	BLACK,	WHITE,	24,0); //��ʾȷ��
	
	LCD_ShowChinese(85,		210,	"ȡ��",	BLACK,	WHITE,	24,0); //��ʾɾ��
	
	/*************************************
		
	������Ҫ�Ĺ���ʵ����ѭ��
		
	*****************************************/
	while(1)
	{
		switch_value = Get_Key_value(1); //��ⰴ��
		
		if(switch_value == Button_1_pressed)// ���µ���ѡ��ʱ���������
		{
			Number_of_cycles_--;
			
			flag_ = 1;
			
			if(Number_of_cycles_<1)
			{
				Number_of_cycles_ = 5;
			}
		}
		
		if(switch_value == Button_3_pressed)// // ���µ���ѡ��ʱ���������
		{
			Number_of_cycles_++;
			
			flag_ = 1;
			
			if(Number_of_cycles_>5)
			{
				Number_of_cycles_ = 1;
			}
		}

		
		/*************************************
		
		��ʾ���֣���ʱ�����ں�ȷ��ɾ���ֿ�������ʾ��ÿ�ΰ������²Ž���ˢ��
		
		*****************************************/
		if(Number_of_cycles_ == 1 && flag_ == 1)
		{
			flag_ = 0;
			
			LCD_ShowChinese(85,		210,	"ȡ��",	BLACK,	WHITE,	24,0); //��ʾɾ��
			
			LCD_ShowIntNum1(5,	65,	value_1,	2,	BLACK,	LGRAY,	32); //��ʾʱ����
			
			LCD_ShowIntNum1(69,	65,	value_2,	2,	BLACK,	WHITE,	32); //��ʾ����
		}
		if(Number_of_cycles_ == 2 && flag_ == 1)
		{
			flag_ = 0;
			
			LCD_ShowIntNum1(5,	65,	value_1,	2,	BLACK,	WHITE,	32); //��ʾʱ����
			
			LCD_ShowIntNum1(69,	65,	value_2,	2,	BLACK,	LGRAY,	32); //��ʾ����
			
			LCD_ShowChinese(5,		210,	"ȷ��",	BLACK,	WHITE,	24,0); //��ʾȷ��
		}
		if(Number_of_cycles_ == 3 && flag_ == 1)
		{
			flag_ = 0;
			
			LCD_ShowIntNum1(69,	65,	value_2,	2,	BLACK,	WHITE,	32); //��ʾ����
			
			LCD_ShowChinese(5,		210,	"ȷ��",	BLACK,	LGRAY,	24,0); //��ʾȷ��
			
			LCD_ShowChinese(85,		210,	"ȡ��",	BLACK,	WHITE,	24,0); //��ʾɾ��
		}
		if(Number_of_cycles_ == 4 && flag_ == 1)
		{
			flag_ = 0;
			
			LCD_ShowChinese(5,		210,	"ȷ��",	BLACK,	WHITE,	24,0); //��ʾȷ��
			
			LCD_ShowChinese(85,		210,	"ȡ��",	BLACK,	LGRAY,	24,0); //��ʾɾ��
			
			LCD_ShowIntNum1(5,	65,	value_1,	2,	BLACK,	WHITE,	32); //��ʾʱ����
		}
		
		
		/*************************************
		
		�Թ���ʵ�ֵľ������
		
		*****************************************/
		if(Number_of_cycles_ == 1 && switch_value == Button_2_pressed) //��Сʱ���ڵĹ��ܽ��в���
		{
			while(1)
			{
				switch_value = Get_Key_value(1);
				
				LCD_ShowIntNum1(5,	65,	value_1,	2,	BLACK,	LGRAYBLUE,	32); //��ʾʱ���� //ѡ���Ժ��ɻ���ɫ
				
				if(switch_value == Button_1_pressed)
				{								
					value_1 --;									
				}
				if(switch_value == Button_3_pressed)
				{						
					value_1 ++;
				}
				if(value_1 < 0)
				{
					value_1 = 23;
				}
				if(value_1 > 23)
				{
					value_1 = 0;
				}
				if(switch_value == Button_2_pressed)
				{
					LCD_ShowIntNum1(5,	65,	value_1,	2,	BLACK,	LGRAY,	32); //��ʾʱ���� //ѡ���Ժ��ɻ���ɫ //��ѡ��֮�����ɫ�ı����
					
					break;
				}
			}
		}	
		if(Number_of_cycles_ == 2 && switch_value == Button_2_pressed) //�Է��ӵ��ڵĹ��ܽ��в���
		{
			while(1)
			{
				switch_value = Get_Key_value(1);
				
				LCD_ShowIntNum1(69,	65,	value_2,	2,	BLACK,	LGRAYBLUE,	32); //��ʾ���� //ѡ���Ժ��ɻ���ɫ
				
				if(switch_value == Button_1_pressed)
				{								
					value_2 --;									
				}
				if(switch_value == Button_3_pressed)
				{						
					value_2 ++;
				}
				if(value_2 < 0)
				{
					value_2 = 59;
				}
				if(value_2 > 59)
				{
					value_2 = 0;
				}
				if(switch_value == Button_2_pressed)
				{
					LCD_ShowIntNum1(69,	65,	value_2,	2,	BLACK,	LGRAY,	32);  //��ʾʱ���� //ѡ���Ժ��ɻ���ɫ //��ѡ��֮�����ɫ�ı����
					
					break;
				}
			}
		}	
		if(Number_of_cycles_ == 3 && switch_value == Button_2_pressed) //�����˹��ܵ����ã�����ѭ�����ص����ӵĽ���
		{
			sTime.Hours = value_1+1;
			
			sTime.Minutes = value_2+1;
			
			sTime.Seconds = 0;
			
			sTime.DayLightSaving = RTC_DAYLIGHTSAVING_SUB1H;
			
			sTime.StoreOperation = RTC_STOREOPERATION_SET;
			
			if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
			{
				Error_Handler();
			}
			break; //�˳�
		}	
		if(Number_of_cycles_ == 4 && switch_value == Button_2_pressed)  //�����˹��ܵ����ã�����ѭ�����ص����ӵĽ���
		{
		 //�˳�ѭ��֮���ص���ʼ�ĵط�
			
			break;
		}		
	}
}


/*******************************************
* @function: 	���������ý��о��幦�ܵ�ʵ��
* @input:			��
* @return:		��
* @author:		��С��
* @time:			2020.10.24
*******************************************/

void set_data_function( void )
{
	unsigned char switch_value = 0;
	
	unsigned char Number_of_cycles_ = 1;
	
	unsigned char flag_ = 0;
	
	int value_WeekDay = 0; //value_WeekDay	value_Month		value_Date		value_Year
	
	int value_Month = 0; //
	
	int value_Date = 0; //
	
	int value_Year = 0; //

	value_WeekDay = sDate.WeekDay;
	
	value_Month = sDate.Month;

	value_Date= sDate.Date;

	value_Year= sDate.Year;

	LCD_Fill(0,		0,		LCD_W,	LCD_H,	WHITE); //��ʾ����ɰ�ɫˢ��
			
	LCD_ShowIntNum1(	5,		65,		value_Month,	2,	BLACK,	LGRAY,	32); //��ʾ��
					
	LCD_ShowChinese(	37,		65,		"��",	BLACK,	WHITE,	32,0); //��ʾ�·�
	
	LCD_ShowIntNum1(	69,		65,		value_Date,	2,	BLACK,	WHITE,	32); //��ʾ��
	
	LCD_ShowChinese(	101,	65,		"��",	BLACK,	WHITE,	32,0); //��ʾ��
	
	LCD_ShowIntNum1(	5,		110,		value_Year,	2,	BLACK,	WHITE,	32); //��ʾ��
	
	LCD_ShowChinese(	37,		110,	"��",	BLACK,	WHITE,	32,0); //��ʾ��
	
	LCD_ShowIntNum1(	101,		110,	value_WeekDay,	2,	BLACK,	WHITE,	32); //��ʾ��
	
	LCD_ShowChinese(	69,		110,	"��",	BLACK,	WHITE,	32,0); //��ʾ��
	
	LCD_ShowChinese(	5,		210,	"ȷ��",	BLACK,	WHITE,	24,0); //��ʾȷ��
	
	LCD_ShowChinese(	85,		210,	"ȡ��",	BLACK,	WHITE,	24,0); //��ʾɾ��
	
	while(1)
	{
		switch_value = Get_Key_value(1); //��ⰴ��
		
		if(switch_value == Button_1_pressed)// ���µ���ѡ��ʱ���������
		{
			Number_of_cycles_--;
			
			flag_ = 1;
			
			if(Number_of_cycles_<1)
			{
				Number_of_cycles_ = 6;
			}
		}
		
		if(switch_value == Button_3_pressed)// // ���µ���ѡ��ʱ���������
		{
			Number_of_cycles_++;
			
			flag_ = 1;
			
			if(Number_of_cycles_>6)
			{
				Number_of_cycles_ = 1;
			}
		}

		
		/*************************************
		
		��ʾ���֣���ʱ�����ں�ȷ��ɾ���ֿ�������ʾ��ÿ�ΰ������²Ž���ˢ��
		
		*****************************************/
		
		if(Number_of_cycles_ == 1 && flag_ == 1)
		{
			flag_ = 0;
			
			LCD_ShowChinese(	85,		210,	"ȡ��",	BLACK,	WHITE,	24,0); //��ʾɾ��
			
			LCD_ShowIntNum1(5,	65,	value_Month,	2,	BLACK,	LGRAY,	32); //��ʾ��
			
			LCD_ShowIntNum1(69,	65,	value_Date,	2,	BLACK,	WHITE,	32); //��ʾ��
		}
		
		
		if(Number_of_cycles_ == 2 && flag_ == 1)
		{
			flag_ = 0;
			
			LCD_ShowIntNum1(5,	65,	value_Month,	2,	BLACK,	WHITE,	32); //��ʾ��
			
			LCD_ShowIntNum1(69,	65,	value_Date,	2,	BLACK,	LGRAY,	32); //��ʾ��
			
			LCD_ShowIntNum1(5,	110,	value_Year,	2,	BLACK,	WHITE,	32); //��ʾ��
		}
		
		
		
		if(Number_of_cycles_ == 3 && flag_ == 1)
		{
			flag_ = 0;
			
			LCD_ShowIntNum1(69,	65,	value_Date,	2,	BLACK,	WHITE,	32); //��ʾ��
			
			LCD_ShowIntNum1(5,	110,	value_Year,	2,	BLACK,	LGRAY,	32); //��ʾ��
			
			switch(value_WeekDay)
			{
				
				case 1:	LCD_ShowChinese(101,		110,	"һ",	BLACK,	WHITE,	32,0);  break;//��ʾ��һ��
				case 2:	LCD_ShowChinese(101,		110,	"��",	BLACK,	WHITE,	32,0);  break;//��ʾ��һ��
				case 3:	LCD_ShowChinese(101,		110,	"��",	BLACK,	WHITE,	32,0);  break;//��ʾ��һ��
				case 4:	LCD_ShowChinese(101,		110,	"��",	BLACK,	WHITE,	32,0);  break;//��ʾ��һ��
				case 5:	LCD_ShowChinese(101,		110,	"��",	BLACK,	WHITE,	32,0);  break;//��ʾ��һ��
				case 6:	LCD_ShowChinese(101,		110,	"��",	BLACK,	WHITE,	32,0);  break;//��ʾ��һ��
				case 7:	LCD_ShowChinese(101,		110,	"��",	BLACK,	WHITE,	32,0);  break;//��ʾ��һ��
			}
		}
		
		
		
		if(Number_of_cycles_ == 4 && flag_ == 1)
		{
			flag_ = 0;
			
			LCD_ShowIntNum1(5,	110,	value_Year,	2,	BLACK,	WHITE,	32); //��ʾ��
			
			switch(value_WeekDay)
			{
				case 1:	LCD_ShowChinese(101,		110,	"һ",	BLACK,	LGRAY,	32,0);  break;//��ʾ��һ��
				case 2:	LCD_ShowChinese(101,		110,	"��",	BLACK,	LGRAY,	32,0);  break;//��ʾ��һ��
				case 3:	LCD_ShowChinese(101,		110,	"��",	BLACK,	LGRAY,	32,0);  break;//��ʾ��һ��
				case 4:	LCD_ShowChinese(101,		110,	"��",	BLACK,	LGRAY,	32,0);  break;//��ʾ��һ��
				case 5:	LCD_ShowChinese(101,		110,	"��",	BLACK,	LGRAY,	32,0);  break;//��ʾ��һ��
				case 6:	LCD_ShowChinese(101,		110,	"��",	BLACK,	LGRAY,	32,0);  break;//��ʾ��һ��
				case 7:	LCD_ShowChinese(101,		110,	"��",	BLACK,	LGRAY,	32,0);  break;//��ʾ��һ��
			}
			LCD_ShowChinese(5,		210,	"ȷ��",	BLACK,	WHITE,	24,0); //��ʾȷ��
		}
		
		
		if(Number_of_cycles_ == 5 && flag_ == 1)
		{
			flag_ = 0;
			
			switch(value_WeekDay)
			{
				case 1:	LCD_ShowChinese(101,		110,	"һ",	BLACK,	WHITE,	32,0);  break;//��ʾ��һ��
				case 2:	LCD_ShowChinese(101,		110,	"��",	BLACK,	WHITE,	32,0);  break;//��ʾ��һ��
				case 3:	LCD_ShowChinese(101,		110,	"��",	BLACK,	WHITE,	32,0);  break;//��ʾ��һ��
				case 4:	LCD_ShowChinese(101,		110,	"��",	BLACK,	WHITE,	32,0);  break;//��ʾ��һ��
				case 5:	LCD_ShowChinese(101,		110,	"��",	BLACK,	WHITE,	32,0);  break;//��ʾ��һ��
				case 6:	LCD_ShowChinese(101,		110,	"��",	BLACK,	WHITE,	32,0);  break;//��ʾ��һ��
				case 7:	LCD_ShowChinese(101,		110,	"��",	BLACK,	WHITE,	32,0);  break;//��ʾ��һ��
			}
			
			LCD_ShowChinese(5,		210,	"ȷ��",	BLACK,	LGRAY,	24,0); //��ʾȷ��
			
			LCD_ShowChinese(85,		210,	"ȡ��",	BLACK,	WHITE,	24,0); //��ʾɾ��
		}
		
		
		if(Number_of_cycles_ == 6 && flag_ == 1)
		{
			flag_ = 0;
			
			LCD_ShowChinese(5,		210,	"ȷ��",	BLACK,	WHITE,	24,0); //��ʾȷ��
			
			LCD_ShowChinese(85,		210,	"ȡ��",	BLACK,	LGRAY,	24,0); //��ʾɾ��
			
			LCD_ShowIntNum1(5,		65,	value_Month,	2,	BLACK,	WHITE,	32); //��ʾʱ����
		}
		
		
		
		/*************************************
		
		���幦��ʵ�ֲ���
		
		*****************************************/
		
		if(Number_of_cycles_ == 1 && switch_value == Button_2_pressed) //��Сʱ���ڵĹ��ܽ��в���
		{ //value_WeekDay	value_Month		value_Date		value_Year
			while(1)
			{
				switch_value = Get_Key_value(1);
				
				LCD_ShowIntNum1(5,	65,	value_Month,	2,	BLACK,	LGRAYBLUE,	32); //��ʾ�·� //ѡ���Ժ��ɻ���ɫ
				
				if(switch_value == Button_1_pressed)
				{								
					value_Month --;									
				}
				if(switch_value == Button_3_pressed)
				{						
					value_Month ++;
				}
				if(value_Month < 1)
				{
					value_Month = 12;
				}
				if(value_Month > 12)
				{
					value_Month = 1;
				}
				if(switch_value == Button_2_pressed)
				{
					LCD_ShowIntNum1(5,	65,	value_Month,	2,	BLACK,	LGRAY,	32); //��ʾʱ���� //ѡ���Ժ��ɻ���ɫ //��ѡ��֮�����ɫ�ı����
					
					break;
				}
			}
		}	
		if(Number_of_cycles_ == 2 && switch_value == Button_2_pressed) //�Է��ӵ��ڵĹ��ܽ��в���
		{
			while(1)
			{
				switch_value = Get_Key_value(1);
				
				LCD_ShowIntNum1(69,	65,	value_Date,	2,	BLACK,	LGRAYBLUE,	32); //��ʾ���� //ѡ���Ժ��ɻ���ɫ
				
				if(switch_value == Button_1_pressed)
				{								
					value_Date --;									
				}
				if(switch_value == Button_3_pressed)
				{						
					value_Date ++;
				}
				if(value_Date < 1)
				{
					value_Date = 31;
				}
				if(value_Date > 31)
				{
					value_Date = 1;
				}
				if(switch_value == Button_2_pressed)
				{
					LCD_ShowIntNum1(69,	65,	value_Date,	2,	BLACK,	LGRAY,	32);  //��ʾʱ���� //ѡ���Ժ��ɻ���ɫ //��ѡ��֮�����ɫ�ı����
					
					break;
				}
			}
		}	
		
		if(Number_of_cycles_ == 3 && switch_value == Button_2_pressed) //�Է��ӵ��ڵĹ��ܽ��в���
		{
			while(1)
			{
				switch_value = Get_Key_value(1);
				
				LCD_ShowIntNum1(5,	110,	value_Year,	2,	BLACK,	LGRAYBLUE,	32); //��ʾ�� //ѡ���Ժ��ɻ���ɫ
				
				if(switch_value == Button_1_pressed)
				{								
					value_Year --;									
				}
				if(switch_value == Button_3_pressed)
				{						
					value_Year ++;
				}
				if(value_Year < 0)
				{
					value_Year = 99;
				}
				if(value_Year > 99)
				{
					value_Year = 0;
				}
				if(switch_value == Button_2_pressed)
				{
					LCD_ShowIntNum1(5,	110,	value_Year,	2,	BLACK,	LGRAY,	32);  //��ʾ�� //ѡ���Ժ��ɻ���ɫ //��ѡ��֮�����ɫ�ı����
					
					break;
				}
			}
		}	
		
		
		if(Number_of_cycles_ == 4 && switch_value == Button_2_pressed) //���������ڵĹ��ܽ��в���
		{
			while(1)
			{
				switch_value = Get_Key_value(1);
				
				switch(value_WeekDay)
				{
					case 1:	LCD_ShowChinese(101,		110,	"һ",	BLACK,	LGRAYBLUE,	32,0);  break;//��ʾ��һ��
					case 2:	LCD_ShowChinese(101,		110,	"��",	BLACK,	LGRAYBLUE,	32,0);  break;//��ʾ��һ��
					case 3:	LCD_ShowChinese(101,		110,	"��",	BLACK,	LGRAYBLUE,	32,0);  break;//��ʾ��һ��
					case 4:	LCD_ShowChinese(101,		110,	"��",	BLACK,	LGRAYBLUE,	32,0);  break;//��ʾ��һ��
					case 5:	LCD_ShowChinese(101,		110,	"��",	BLACK,	LGRAYBLUE,	32,0);  break;//��ʾ��һ��
					case 6:	LCD_ShowChinese(101,		110,	"��",	BLACK,	LGRAYBLUE,	32,0);  break;//��ʾ��һ��
					case 7:	LCD_ShowChinese(101,		110,	"��",	BLACK,	LGRAYBLUE,	32,0);  break;//��ʾ��һ��
				}
				
				if(switch_value == Button_1_pressed)
				{								
					value_WeekDay --;									
				}
				if(switch_value == Button_3_pressed)
				{						
					value_WeekDay ++;
				}
				if(value_WeekDay < 1)
				{
					value_WeekDay = 7;
				}
				if(value_WeekDay > 7)
				{
					value_WeekDay = 1;
				}
				if(switch_value == Button_2_pressed)
				{
					switch(value_WeekDay)
					{
						case 1:	LCD_ShowChinese(101,		110,	"һ",	BLACK,	LGRAY,	32,0);  break;//��ʾ��һ��
						case 2:	LCD_ShowChinese(101,		110,	"��",	BLACK,	LGRAY,	32,0);  break;//��ʾ��һ��
						case 3:	LCD_ShowChinese(101,		110,	"��",	BLACK,	LGRAY,	32,0);  break;//��ʾ��һ��
						case 4:	LCD_ShowChinese(101,		110,	"��",	BLACK,	LGRAY,	32,0);  break;//��ʾ��һ��
						case 5:	LCD_ShowChinese(101,		110,	"��",	BLACK,	LGRAY,	32,0);  break;//��ʾ��һ��
						case 6:	LCD_ShowChinese(101,		110,	"��",	BLACK,	LGRAY,	32,0);  break;//��ʾ��һ��
						case 7:	LCD_ShowChinese(101,		110,	"��",	BLACK,	LGRAY,	32,0);  break;//��ʾ��һ��
					}
					break;
				}
			}
		}	
		if(Number_of_cycles_ == 5 && switch_value == Button_2_pressed) //�����˹��ܵ����ã�����ѭ�����ص����ӵĽ���
		{
			sDate.WeekDay = value_WeekDay;
			
			sDate.Month = value_Month;
			
			sDate.Date = value_Date;
			
			sDate.Year = value_Year;

			if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
			{
				Error_Handler();
			}

			break; //�˳�
		}	
		if(Number_of_cycles_ == 6 && switch_value == Button_2_pressed)  //�����˹��ܵ����ã�����ѭ�����ص����ӵĽ���
		{	
		 //�˳�ѵ��֮���ص���ʼ�ĵط�
		
			break;
		}		
	}
}


/*******************************************
* @function: 	�����������صĹ���
* @input:			��
* @return:		��
* @author:		��С��
* @time:			2020.10.24
*******************************************/

unsigned char Sound_switch = 1; //����Ĭ���Ǵ򿪵�

void set_sound_function(void)
{
	unsigned char switch_value = 0;
	
	unsigned char Number_of_cycles_ = 1;
	
	unsigned char flag_ = 0;

	
	LCD_Fill(0,		0,		LCD_W,	LCD_H,	WHITE); //��ʾ����ɰ�ɫˢ��
			
	if( Sound_switch )
	{
		LCD_ShowPicture(32,		60,		70,		70,	gImage_sound);
	}
	else
	{
		LCD_ShowPicture(32,		60,		69,		70,	gImage_nosound);
	}
		
	LCD_ShowChinese(5,		210,	"ȷ��",	BLACK,	WHITE,	24,0); //��ʾȷ��
	
	LCD_ShowChinese(85,		210,	"ȡ��",	BLACK,	WHITE,	24,0); //��ʾɾ��
	
	/*************************************
		
	������Ҫ�Ĺ���ʵ����ѭ��
		
	*****************************************/
	while(1)
	{
		switch_value = Get_Key_value(1); //��ⰴ��
		
		if(switch_value == Button_1_pressed)// ���µ���ѡ��ʱ���������
		{
			Number_of_cycles_--;
			
			flag_ = 1;
			
			if(Number_of_cycles_<1)
			{
				Number_of_cycles_ = 3;
			}
		}
		
		if(switch_value == Button_3_pressed)// // ���µ���ѡ��ʱ���������
		{
			Number_of_cycles_++;
			
			flag_ = 1;
			
			if(Number_of_cycles_>3)
			{
				Number_of_cycles_ = 1;
			}
		}

		
		/*************************************
		
		��ʾ����
		
		*****************************************/
		if(Number_of_cycles_ == 1 && flag_ == 1)
		{
			flag_ = 0;
			
			LCD_ShowChinese(85,		210,	"ȡ��",	BLACK,	WHITE,	24,0); //��ʾɾ��
			
			LCD_ShowChinese(5,		210,	"ȷ��",	BLACK,	WHITE,	24,0); //��ʾȷ��
			
		}
		if(Number_of_cycles_ == 2 && flag_ == 1)
		{
			flag_ = 0;
			
			LCD_ShowChinese(5,		210,	"ȷ��",	BLACK,	LGRAY,	24,0); //��ʾȷ��
			
			LCD_ShowChinese(85,		210,	"ȡ��",	BLACK,	WHITE,	24,0); //��ʾɾ��			
		}
		if(Number_of_cycles_ == 3 && flag_ == 1)
		{
			flag_ = 0;
			
			LCD_ShowChinese(5,		210,	"ȷ��",	BLACK,	WHITE ,	24,0); //��ʾȷ��
			
			LCD_ShowChinese(85,		210,	"ȡ��",	BLACK,	LGRAY ,	24,0); //��ʾɾ��
		}
		
		
		/*************************************
		
		�Թ���ʵ�ֵľ������
		
		*****************************************/
		if(Number_of_cycles_ == 1 && switch_value == Button_2_pressed) //��Сʱ���ڵĹ��ܽ��в���
		{
			Sound_switch =! Sound_switch;
			
			if( Sound_switch )
			{
				LCD_ShowPicture(32,		60,		70,		70,	gImage_sound);	
			}
			else
			{
				LCD_ShowPicture(32,		60,		69,		70,	gImage_nosound);
			}
		}	
		if(Number_of_cycles_ == 2 && switch_value == Button_2_pressed) //�Է��ӵ��ڵĹ��ܽ��в���
		{
			//�˳�ѭ��֮���ص���ʼ�ĵط�
			break;
		}	
		if(Number_of_cycles_ == 3 && switch_value == Button_2_pressed) //�����˹��ܵ����ã�����ѭ�����ص����ӵĽ���
		{
			break; //�˳�
		}	
		
	}
}

/*******************************************
* @function: 	��ʼ�����ý������Ļ
* @input:			��
* @return:		��
* @author:		��С��
* @time:			2020.10.3
*******************************************/
void setting_function_init_display(void)
{
	LCD_Fill(0,0,LCD_W,LCD_H,BLACK); //�����������

	printf("����������app\r\n");
	
	LCD_Fill(0,0,LCD_W,LCD_H,WHITE); //��ʾ����ɰ�ɫˢ��
	
//	LCD_Fill(0,		0,LCD_W,30,LGRAY); //��ʾ����ɻ�ɫˢ��
		
	LCD_Fill(0,	30,	LCD_W,	31,	BLACK); //����		
	
	LCD_Fill(0,	60,	LCD_W,	61,	BLACK); //����			
	
	LCD_Fill(0,	90,	LCD_W,	91,	BLACK); //����			
	
	LCD_Fill(0,	120,	LCD_W,	121,	BLACK); //����			
	
	LCD_Fill(0,	150,	LCD_W,	151,	BLACK); //����			
	
	LCD_Fill(0,	180,	LCD_W,	181,	BLACK); //����			
	
	LCD_Fill(0,	210,	LCD_W,	211,	BLACK); //����
				
	
	
	LCD_ShowChinese(0,		3,		"����",			BLACK,	WHITE,24,0);
	LCD_ShowChinese(0,		33,		"����ʱ��",	BLACK,	WHITE,24,0);
	LCD_ShowChinese(0,		63,		"��������",	BLACK,	WHITE,24,0);
	LCD_ShowChinese(0,		93,		"����",			BLACK,	WHITE,24,0);
	LCD_ShowChinese(0,		123,	"�Ʋ���",		BLACK,	WHITE,24,0);
	LCD_ShowChinese(0,		153,	"�ƹ�",			BLACK,	WHITE,24,0);
	LCD_ShowChinese(0,		183,	"�������",	BLACK,	WHITE,24,0);

}


/*******************************************
* @function: 	���õĹ���
* @input:			��
* @return:		��
* @author:		��С��
* @time:			2020.10.3
*******************************************/
void setting_function(void)
{
//	static unsigned char Number_of_cycles = function_clock;
	
	unsigned char switch_value;
		
	static unsigned char flag__ = 0;
	
	static unsigned char Number_of_cycles = 1;
	
	flag__ = 1; //������Ļˢ��
	
	setting_function_init_display(); //��ʼ�����ý������Ļ
	
	while(1)
	{
		switch_value = Get_Key_value(1);
		
		if(switch_value == Button_3_pressed)
		{
			Number_of_cycles++;
			
			flag__ = 1; //������Ļˢ��
			
			if(Number_of_cycles>8)
			{
				Number_of_cycles = 1;
			}
		}
		
		if(switch_value == Button_1_pressed)
		{
			Number_of_cycles--;
			
			flag__ = 1; //������Ļˢ��
			
			if(Number_of_cycles<1)
			{
				Number_of_cycles = 8;
			}
		}
		
		/*************************************
		
		��ʾ����
		
		*****************************************/
		if(Number_of_cycles == 1 && flag__ == 1)
		{
			flag__ = 0; //������Ļˢ��
			
			LCD_Fill(0,		211,LCD_W,240,WHITE); //��ʾ����ɻ�ɫˢ��
			
			LCD_Fill(0,		0,LCD_W,30,LGRAY); //��ʾ����ɻ�ɫˢ��
			
			LCD_ShowChinese(0,		3,	"����",	BLACK,	LGRAY,24,0);
			
			LCD_Fill(0,		31,LCD_W,60,WHITE); //��ʾ����ɻ�ɫˢ��
			
			LCD_ShowChinese(0,		33,	"����ʱ��",	BLACK,	WHITE,24,0);
		}
		if(Number_of_cycles == 2 && flag__ == 1)
		{
			flag__ = 0; //������Ļˢ��
														
			LCD_Fill(0,		0,LCD_W,30,WHITE); //��ʾ����ɻ�ɫˢ��
			
			LCD_ShowChinese(0,		3,	"����",	BLACK,	WHITE,24,0);
			
			LCD_Fill(0,		31,LCD_W,60,LGRAY); //��ʾ����ɻ�ɫˢ��	
			
			LCD_ShowChinese(0,		33,	"����ʱ��",	BLACK,	LGRAY,24,0);
			
			LCD_Fill(0,		61,LCD_W,90,WHITE); //��ʾ����ɻ�ɫˢ��
			
			LCD_ShowChinese(0,		63,"��������",	BLACK,	WHITE,24,0);
		}

		if(Number_of_cycles == 3 && flag__ == 1)
		{
			flag__ = 0; //������Ļˢ��

			LCD_Fill(0,		31,LCD_W,60,WHITE); //��ʾ����ɻ�ɫˢ��
			
			LCD_ShowChinese(0,		33,"����ʱ��",	BLACK,	WHITE,24,0);
			
			LCD_Fill(0,		61,LCD_W,90,LGRAY); //��ʾ����ɻ�ɫˢ��
			
			LCD_ShowChinese(0,		63,	"��������",	BLACK,	LGRAY,24,0);
			
			LCD_Fill(0,		91,LCD_W,120,WHITE); //��ʾ����ɻ�ɫˢ��
			
			LCD_ShowChinese(0,		93,	"����",	BLACK,	WHITE,24,0);
		}
		
		if(Number_of_cycles == 4 && flag__ == 1)
		{
			flag__ = 0; //������Ļˢ��
			
			LCD_Fill(0,		61,LCD_W,90,WHITE); //��ʾ����ɻ�ɫˢ��
			
			LCD_ShowChinese(0,		63,	"��������",	BLACK,	WHITE,24,0);
			
			LCD_Fill(0,		91,LCD_W,120,LGRAY); //��ʾ����ɻ�ɫˢ��
			
			LCD_ShowChinese(0,		93,	"����",	BLACK,	LGRAY,24,0);
			
			LCD_Fill(0,		121,LCD_W,150,WHITE); //��ʾ����ɻ�ɫˢ��
			
			LCD_ShowChinese(0,		123,	"�Ʋ���",	BLACK,	WHITE,24,0);
		}
		
		if(Number_of_cycles == 5 && flag__ == 1)
		{
			flag__ = 0; //������Ļˢ��
			
			LCD_Fill(0,		91,LCD_W,120,WHITE); //��ʾ����ɻ�ɫˢ��
			
			LCD_ShowChinese(0,		93,	"����",	BLACK,	WHITE,24,0);
			
			LCD_Fill(0,		121,LCD_W,150,LGRAY); //��ʾ����ɻ�ɫˢ��
			
			LCD_ShowChinese(0,		123,	"�Ʋ���",	BLACK,	LGRAY,24,0);
			
			LCD_Fill(0,		151,LCD_W,180,WHITE); //��ʾ����ɻ�ɫˢ��
			
			LCD_ShowChinese(0,		153,	"�ƹ�",	BLACK,	WHITE,24,0);
		}
		
		if(Number_of_cycles == 6 && flag__ == 1)
		{
			flag__ = 0; //������Ļˢ��
			
			LCD_Fill(0,		121,LCD_W,150,WHITE); //��ʾ����ɻ�ɫˢ��
			
			LCD_ShowChinese(0,		123,	"�Ʋ���",	BLACK,	WHITE,24,0);
			
			LCD_Fill(0,		151,LCD_W,180,LGRAY); //��ʾ����ɻ�ɫˢ��
			
			LCD_ShowChinese(0,		153,	"�ƹ�",	BLACK,	LGRAY,24,0);
			
			LCD_Fill(0,		181,LCD_W,210,WHITE); //��ʾ����ɻ�ɫˢ��
			
			LCD_ShowChinese(0,		183,	"�������",	BLACK,	WHITE,24,0);
		}
		
		if(Number_of_cycles == 7 && flag__ == 1)
		{
			flag__ = 0; //������Ļˢ��
			
			LCD_Fill(0,		151,LCD_W,180,WHITE); //��ʾ����ɻ�ɫˢ��
			
			LCD_ShowChinese(0,		153,	"�ƹ�",	BLACK,	WHITE,24,0);
			
			LCD_Fill(0,		181,LCD_W,210,LGRAY); //��ʾ����ɻ�ɫˢ��
			
			LCD_ShowChinese(0,		183,	"�������",	BLACK,	LGRAY,24,0);
			
			LCD_Fill(0,		211,LCD_W,240,WHITE); //��ʾ����ɻ�ɫˢ��
			
		}
		
		if(Number_of_cycles == 8 && flag__ == 1)
		{
			flag__ = 0; //������Ļˢ��
			
			LCD_Fill(0,		181,LCD_W,210,WHITE); //��ʾ����ɻ�ɫˢ��
			
			LCD_ShowChinese(0,		183,	"�������",	BLACK,	WHITE,24,0);
			
			LCD_Fill(0,		211,LCD_W,240,LGRAY); //��ʾ����ɻ�ɫˢ��
			
//			LCD_ShowChinese(0,		213,	"�½�",	BLACK,	LGRAY,24,0);
		}
		
		/*************************************
		
		�Թ���ʵ�ֵľ������
		
		*****************************************/
		
		if(switch_value == Button_2_pressed && Number_of_cycles == 1)
		{
			Number_of_cycles = 1;
			
			break;	
		}
		
		if(switch_value == Button_2_pressed && Number_of_cycles == 2) //����ʱ�书��ѡ��
		{
			
			set_time_function(); //����ʱ��ľ��幦�ܺͽ���
			
			setting_function_init_display(); //���°���ʾ������ʾ�����ý����һ��ʼ����
			
			Number_of_cycles = 2; 
			
			flag__ = 1;
			
			
		}
		
		if(switch_value == Button_2_pressed && Number_of_cycles == 3)
		{
			set_data_function();
			
			setting_function_init_display(); //���°���ʾ������ʾ�����ý����һ��ʼ����
			
			Number_of_cycles = 3;
			
			flag__ = 1;
			
			
			
		}
		
		if(switch_value == Button_2_pressed && Number_of_cycles == 4)
		{
			set_sound_function();
			
			setting_function_init_display(); //���°���ʾ������ʾ�����ý����һ��ʼ����
			
			Number_of_cycles = 4;
			
			flag__ = 1;
			
			
		}
	}
}



/*******************************************
* @function: 	��̨�����Ӻ������ǵļƲ������м��
* @input:			��
* @return:		��
* @author:		��С��
* @time:			2020.10.5
*******************************************/


void Background_detection(unsigned char switch_value)
{
	unsigned char i = 0;
	
	static unsigned char stata = 0;
		
	static unsigned char Detection_status = 1;
	
	//printf(" %d  %d  %d   \r\n",clock_time_hour[0],clock_time_min[0],clock_Data[i]);
	
	for(	i=0;	i<7;	i++	)
	{	
		//���ÿ�춼�е�����
		if(clock_Data[i] == 0)
		{
			if(	sTime.Hours ==	clock_time_hour[i]  &&  sTime.Minutes ==	clock_time_min[i]	) //����Ƿ��Ӧ����ʱ��
			{
				if(	Detection_status == 1	)
				{
					stata = 1;
				}
			}
			else
			{
				Detection_status = 1;	//��⵽û�е������ӵ�ʱ��
			}
		}
		//����ܼ�������
		if(clock_Data[i] == sDate.WeekDay)
		{
			if(sTime.Hours ==	clock_time_hour[i]  &&  sTime.Minutes ==	clock_time_min[i]) //����Ƿ��Ӧ����ʱ��
			{
				if(	Detection_status == 1	)
				{
					stata = 1;
				}
			}
			else
			{
				Detection_status = 1;	//��⵽û�е������ӵ�ʱ��
			}
		}
		
	} //forѭ������
	

	//��⵽��������͹ر����ӵ�����
	if(	switch_value == Button_2_pressed || switch_value == Button_1_pressed	||	switch_value == Button_3_pressed	) //��������һ����������ֹͣ����
	{
		stata = 0; //�ر�����
		
		Detection_status = 0;
	
		__HAL_TIM_SET_COMPARE(	&htim2, TIM_CHANNEL_4, 70	); //����PWM��ռ�ձȣ����ڱ��� //����
		
		HAL_GPIO_WritePin(	LED_GPIO_Port, LED_Pin, GPIO_PIN_SET	);	//��⵽����֮�����˸LED //�ر�LED
		
		__HAL_TIM_SET_COMPARE(	&htim4, TIM_CHANNEL_4, 0	); ////�÷�����ֹͣ����
	}
	
	//��⵽�����ӹ涨��ʱ��
	if(	stata == 1	)
	{
		if(	Total_cycle == 25	) //Total_cycle����ѭ���еļ���ֵ����0��100ѭ���ݼ�����Լ��800��������ѭ��һ��
		{
			HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);	//��⵽����֮�����˸LED
			
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, 600); //����PWM��ռ�ձȣ����ڱ��� //����
			
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, 0); //�÷�����ֹͣ����
			
		}
		if(	Total_cycle == 75	) //Total_cycle����ѭ���еļ���ֵ����0��100ѭ���ݼ�����Լ��800��������ѭ��һ��
		{
			HAL_GPIO_WritePin(	LED_GPIO_Port, LED_Pin, GPIO_PIN_SET	);	//��⵽����֮�����˸LED
			
			__HAL_TIM_SET_COMPARE(	&htim2, TIM_CHANNEL_4, 70	); //����PWM��ռ�ձȣ����ڱ���
			
			__HAL_TIM_SET_COMPARE(	&htim4, TIM_CHANNEL_4, 50	); //�÷���������
		}
	}
}


























