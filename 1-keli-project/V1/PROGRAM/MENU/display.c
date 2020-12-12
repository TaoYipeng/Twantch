
#include "stdio.h"

#include "display.h"

#include "main.h"
#include "adc.h"
#include "dma.h"
#include "i2c.h"

#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

#include "lcd.h"
#include "lcd_init.h"
#include "pic.h"

#include "contro.h"

#include "app.h"

	
/*******************************************
* @function: 	����ʾ��Ļ����ʾ������
* @input:			��
* @return:		���������������������ֵ
* @author:		��С��
* @time:			2020.10.2
*******************************************/
void MENU_init_(void)
{
	//LCD_ShowPicture(0,		0,		13,		15,	gImage_clock);
	
	//LCD_ShowPicture(20,		0,		13,		15,	gImage_play);
	
	LCD_ShowPicture(0,		0,		13,		15,	gImage_play);
	
	LCD_ShowPicture(106,	0,		27,		15,	gImage_power);
	
	LCD_ShowChinese(17+32,		190+24,	"��",	WHITE,	BLACK,	16,	0);
	
	LCD_ShowString (19+32+24+32,		190+24,	"%",	WHITE,	BLACK,	16,	0); //��ʾ�ٷֺ�
	
	//�ѼƲ����Ĳ�����ʾ������Ļ����
	if(	STEPS	>	9999	)
	{
		LCD_ShowIntNum (20,		0,	STEPS,	5,	WHITE,	BLACK,	16); //��ʾ����
	}
	else if(	STEPS	>	999	)
	{
		LCD_ShowIntNum (20,		0,	STEPS,	4,	WHITE,	BLACK,	16); //��ʾ����
	}
	else if(	STEPS	>	99	)
	{
		LCD_ShowIntNum (20,		0,	STEPS,	3,	WHITE,	BLACK,	16); //��ʾ����
	}
	else if(	STEPS	>	9	)	
	{
		LCD_ShowIntNum (20,		0,	STEPS,	2,	WHITE,	BLACK,	16); //��ʾ����
	}
	else
	{
		LCD_ShowIntNum (20,		0,	STEPS,	1,	WHITE,	BLACK,	16); //��ʾ����
	}
}



/*******************************************
* @function: 	����ʾ��Ļ����ʾ������
* @input:			��
* @return:		���������������������ֵ
* @author:		��С��
* @time:			2020.10.2
*******************************************/
void MENU_init(void)
{
	LCD_Init();//LCD��ʼ��
	
	LCD_Fill(0,0,LCD_W,LCD_H,BLACK);
	
	MENU_init_();
}
	


/*******************************************
* @function: 	����ʾ��Ļ����ʾ������
* @input:			��
* @return:		���������������������ֵ
* @author:		��С��
* @time:			2020.10.2
*******************************************/
static unsigned char history_time[6] = {100,100,100,100,100,100}; //����ʱ�����ʷ����

static unsigned char history_temperature ;

static unsigned char history_humidity;

unsigned long	history_STEPS = 0; //����

static	unsigned char Battery_display_flag ;

char Total_cycle = 0;

void MENU_main(void)
{
	/*��������һ����ʱ����ѭ��ѭ��һ�ٴε�ʱ���ԼΪһ�룬С��һ��*/
	Total_cycle--;
		
	if(Total_cycle == 0)
	{
		Total_cycle = 100;
	}
		
	if(history_time[0] != sTime.Hours)
	{
		switch(sTime.Hours/10)
		{
			case  0: LCD_ShowPicture(28,		50,		40,		49,	gImage_a0);	break; //40*49
			case  1: LCD_ShowPicture(28,		50,		39,		50,	gImage_a1);	break; //39*50
			case  2: LCD_ShowPicture(28,		50,		39,		50,	gImage_a2);	break; //39*50
			default:  LCD_ShowPicture(28,		50,		40,		49,	gImage_a0);
		}
		
		switch(sTime.Hours%10)
		{
			case  0: LCD_ShowPicture(68,		50,		40,		49,	gImage_a0);	break; //40*49
			case  1: LCD_ShowPicture(68,		50,		39,		50,	gImage_a1);	break; //39*50
			case  2: LCD_ShowPicture(68,		50,		39,		50,	gImage_a2);	break; //39*50
			case  3: LCD_ShowPicture(68,		50,		40,		49,	gImage_a3);	break; //40*49
			case  4: LCD_ShowPicture(68,		50,		40,		49,	gImage_a4);	break; //40*49
			case  5: LCD_ShowPicture(68,		50,		40,		50,	gImage_a5);	break; //40*50
			case  6: LCD_ShowPicture(68,		50,		39,		50,	gImage_a6);	break; //39*50
			case  7: LCD_ShowPicture(68,		50,		40,		49,	gImage_a7);	break; //40*49
			case  8: LCD_ShowPicture(68,		50,		40,		50,	gImage_a8);	break; //40*50
			case  9: LCD_ShowPicture(68,		50,		39,		50,	gImage_a9);	break; //39*50
			default:  LCD_ShowPicture(68,		50,		40,		49,	gImage_a0);
		}
	}

	if(history_time[1] != sTime.Minutes)
	{
		switch(sTime.Minutes/10)
		{
			case  0: LCD_ShowPicture(0,		120,	40,		50,	gImage_c0);	break; //40*50
			case  1: LCD_ShowPicture(0,		120,	40,		49,	gImage_c1);	break; //40*49
			case  2: LCD_ShowPicture(0,		120,	40,		49,	gImage_c2);	break;  //40*49
			case  3: LCD_ShowPicture(0,		120,	39,		50,	gImage_c3);	break;  //39*50
			case  4: LCD_ShowPicture(0,		120,	39,		50,	gImage_c4);	break;  //39*50
			case  5: LCD_ShowPicture(0,		120,	39,		50,	gImage_c5);	break;  //39*50
			case  6: LCD_ShowPicture(0,		120,	40,		49,	gImage_c6);	break;  //40*49
			case  7: LCD_ShowPicture(0,		120,	40,		50,	gImage_c7);	break;  //40*50
			case  8: LCD_ShowPicture(0,		120,	40,		49,	gImage_c8);	break;  //40*49
			case  9: LCD_ShowPicture(0,		120,	39,		49,	gImage_c9);	break;  //39*49
			default:  LCD_ShowPicture(0,		120,	40,		50,	gImage_c1); //40*50
		}
		
		switch(sTime.Minutes%10)
		{
			case  0: LCD_ShowPicture(40,		120,	40,		50,	gImage_c0);	break; //40*50
			case  1: LCD_ShowPicture(40,		120,	40,		49,	gImage_c1);	break; //40*49
			case  2: LCD_ShowPicture(40,		120,	40,		49,	gImage_c2);	break; //40*49
			case  3: LCD_ShowPicture(40,		120,	39,		50,	gImage_c3);	break; //39*50
			case  4: LCD_ShowPicture(40,		120,	39,		50,	gImage_c4);	break; //39*50
			case  5: LCD_ShowPicture(40,		120,	39,		50,	gImage_c5);	break; //39*50
			case  6: LCD_ShowPicture(40,		120,	40,		49,	gImage_c6);	break; //40*49
			case  7: LCD_ShowPicture(40,		120,	40,		50,	gImage_c7);	break; //40*50
			case  8: LCD_ShowPicture(40,		120,	40,		49,	gImage_c8);	break; //40*49
			case  9: LCD_ShowPicture(40,		120,	39,		50,	gImage_c9);	break; //39*50 
			default:  LCD_ShowPicture(40,		120,	40,		50,	gImage_c0); //40*50
		}
	}

	if(history_time[2] != sDate.Month)
	{
		LCD_ShowIntNum1(65,		190,	sDate.Month,	2,	WHITE,	BLACK,	16); //��ʾ�·�
	}
		
	if(history_time[3] != sDate.Date)
	{
		LCD_ShowString (81,		190,	"/",							WHITE,	BLACK,	16,	0); //��ʾб��
		
		LCD_ShowIntNum1(89,		190,	sDate.Date,		2,	WHITE,	BLACK,	16); //��ʾ����
	}

	if(history_time[4] != sTime.Seconds)
	{
		LCD_ShowIntNum1 (85,		120,	sTime.Seconds,	2,	WHITE,	BLACK,	32); //��ʾ��������
	}

	if(history_time[5] != sDate.WeekDay)
	{
		if(sDate.WeekDay == RTC_WEEKDAY_MONDAY) 		LCD_ShowChinese(26,		190,	"��һ",WHITE,BLACK,16,0);
		if(sDate.WeekDay == RTC_WEEKDAY_TUESDAY) 		LCD_ShowChinese(26,		190,	"�ܶ�",WHITE,BLACK,16,0);
		if(sDate.WeekDay == RTC_WEEKDAY_WEDNESDAY) 	LCD_ShowChinese(26,		190,	"����",WHITE,BLACK,16,0);
		if(sDate.WeekDay == RTC_WEEKDAY_THURSDAY) 	LCD_ShowChinese(26,		190,	"����",WHITE,BLACK,16,0);
		if(sDate.WeekDay == RTC_WEEKDAY_FRIDAY) 		LCD_ShowChinese(26,		190,	"����",WHITE,BLACK,16,0);
		if(sDate.WeekDay == RTC_WEEKDAY_SATURDAY) 	LCD_ShowChinese(26,		190,	"����",WHITE,BLACK,16,0);
		if(sDate.WeekDay == RTC_WEEKDAY_SUNDAY) 		LCD_ShowChinese(26,		190,	"����",WHITE,BLACK,16,0);
	}
	
	if(	history_temperature != temperature || history_humidity != humidity	)
	{
			LCD_ShowFloatNum(15,		190+24,	temperature,	3,	WHITE,	BLACK,	16); //��ʾ�¶�
	
			//LCD_ShowChinese(17+32,		190+24,	"��",	WHITE,	BLACK,	16,	0);
	
			LCD_ShowFloatNum(19+32+24,		190+24,	humidity,		3,	WHITE,	BLACK,	16); //��ʾʪ��
	
			//LCD_ShowString (19+32+24+32,		190+24,	"%",	WHITE,	BLACK,	16,	0); //��ʾ�ٷֺ�	
	}
	
	//�ѼƲ����Ĳ�����ʾ������Ļ����
	if(	history_STEPS != STEPS)
	{
		if(	STEPS	>	9999	)
		{
			LCD_ShowIntNum (20,		0,	STEPS,	5,	WHITE,	BLACK,	16); //��ʾ����
		}
		else if(	STEPS	>	999	)
		{
			LCD_ShowIntNum (20,		0,	STEPS,	4,	WHITE,	BLACK,	16); //��ʾ����
		}
		else if(	STEPS	>	99	)
		{
			LCD_ShowIntNum (20,		0,	STEPS,	3,	WHITE,	BLACK,	16); //��ʾ����
		}
		else if(	STEPS	>	9	)	
		{
			LCD_ShowIntNum (20,		0,	STEPS,	2,	WHITE,	BLACK,	16); //��ʾ����
		}
		else
		{
			LCD_ShowIntNum (20,		0,	STEPS,	1,	WHITE,	BLACK,	16); //��ʾ����
		}
	}
	
	
	history_time[0] = sTime.Hours;

	history_time[1] = sTime.Minutes;

	history_time[2] = sDate.Month;

	history_time[3] = sDate.Date;

	history_time[4] = sTime.Seconds;	

	history_time[5] = sDate.WeekDay;

	history_temperature = temperature;
	
	history_humidity = humidity;
	
	history_STEPS = STEPS;
	
	if(	USB_in_sign == Not_connected	)
	{
//		printf("û���豸���� \t");
		if(Battery_voltage>90)
		{
			if(	Battery_display_flag != 9	)
			{
				LCD_Fill(	110,4,110+17,11,WHITE); //�����������	
			}
			Battery_display_flag = 9;
		}
		if(Battery_voltage<90 && Battery_voltage>80)
		{
			if(Battery_display_flag != 8)
			{
				LCD_Fill(110,4,110+17-2,11,WHITE); //�����������	
				
				LCD_Fill(110+17-2,4,110+17,11,BLACK); //�����������	
			}
			Battery_display_flag = 8;
		}
		if(Battery_voltage<80 && Battery_voltage>70)
		{
			if(Battery_display_flag != 7)
			{
				LCD_Fill(110,4,110+17-4,11,WHITE); //�����������	
				
				LCD_Fill(110+17-4,4,110+17,11,BLACK); //�����������	
			}
			Battery_display_flag = 7;
		}
		if(Battery_voltage<70 && Battery_voltage>60)
		{
			if(Battery_display_flag != 6)
			{
				LCD_Fill(110,4,110+17-6,11,WHITE); //�����������	
				
				LCD_Fill(110+17-6,4,110+17,11,BLACK); //�����������	
			}
			Battery_display_flag = 6;
		}
		if(Battery_voltage<60 && Battery_voltage>50)
		{
			if(Battery_display_flag != 5)
			{
				LCD_Fill(110,4,110+17-8,11,WHITE); //�����������	
				
				LCD_Fill(110+17-8,4,110+17,11,BLACK); //�����������	
			}
			Battery_display_flag = 5;
		}
		if(Battery_voltage<50 && Battery_voltage>40)
		{
			if(Battery_display_flag != 4)
			{
				LCD_Fill(110,4,110+17-10,11,WHITE); //�����������	
				
				LCD_Fill(110+17-10,4,110+17,11,BLACK); //�����������	
			}
			Battery_display_flag = 4;
		}
		if(Battery_voltage<40 && Battery_voltage>30)
		{
			if(Battery_display_flag != 3)
			{
				LCD_Fill(110,4,110+17-12,11,WHITE); //�����������	
				
				LCD_Fill(110+17-12,4,110+17,11,BLACK); //�����������	
			}
			Battery_display_flag = 3;
		}
		if(Battery_voltage<30 && Battery_voltage>20)
		{
			if(Battery_display_flag != 2)
			{
				LCD_Fill(110,4,110+17-14,11,WHITE); //�����������	
				
				LCD_Fill(110+17-14,4,110+17,11,BLACK); //�����������	
			}
			Battery_display_flag = 2;
		}
		if(Battery_voltage<20 && Battery_voltage>10)
		{
			if(Battery_display_flag != 1)
			{
				LCD_Fill(110,4,110+17-16,11,WHITE); //�����������	
				
				LCD_Fill(110+17-16,4,110+17,11,BLACK); //�����������	
			}
			Battery_display_flag = 1;
		}
		if(Battery_voltage<10)
		{
			if(Battery_display_flag != 0)
			{
				LCD_Fill(110,4,110+17-17,11,WHITE); //�����������	
				
				LCD_Fill(110+17-17,4,110+17,11,BLACK); //�����������	
			}
			Battery_display_flag = 0;
		}
	}
	if(USB_in_sign == Connected)
	{
//		printf("��usb������� �����һ��ѭ�� %d \t",Total_cycle);
		
		Battery_display_flag = 100;
		// /
		if(Total_cycle<8)
		{
			LCD_Fill(110,4,110+17,11,WHITE); //�����������	
		}
		if(Total_cycle<16 && Total_cycle>8)
		{
			LCD_Fill(110,4,110+17-2,11,WHITE); //�����������	
				
			LCD_Fill(110+17-2,4,110+17,11,BLACK); //�����������	
		}
		if(Total_cycle<24 && Total_cycle>16)
		{
			LCD_Fill(110,4,110+17-4,11,WHITE); //�����������	
				
			LCD_Fill(110+17-4,4,110+17,11,BLACK); //�����������	
		}
		if(Total_cycle<32 && Total_cycle>24)
		{
			LCD_Fill(110,4,110+17-6,11,WHITE); //�����������	
				
			LCD_Fill(110+17-6,4,110+17,11,BLACK); //�����������	
		}
		if(Total_cycle<40 && Total_cycle>32)
		{
			LCD_Fill(110,4,110+17-8,11,WHITE); //�����������	
				
			LCD_Fill(110+17-8,4,110+17,11,BLACK); //�����������	
		}
		if(Total_cycle<48 && Total_cycle>40)
		{
			LCD_Fill(110,4,110+17-10,11,WHITE); //�����������	
				
			LCD_Fill(110+17-10,4,110+17,11,BLACK); //�����������	
		}
		if(Total_cycle<56 && Total_cycle>48)
		{
			LCD_Fill(110,4,110+17-12,11,WHITE); //�����������	
				
			LCD_Fill(110+17-12,4,110+17,11,BLACK); //�����������
		}
		if(Total_cycle<64 && Total_cycle>56)
		{
			LCD_Fill(110,4,110+17-14,11,WHITE); //�����������	
				
			LCD_Fill(110+17-14,4,110+17,11,BLACK); //�����������	
		}
		if(Total_cycle<72 && Total_cycle>64)
		{
			LCD_Fill(110,4,110+17-16,11,WHITE); //�����������	
				
			LCD_Fill(110+17-16,4,110+17,11,BLACK); //�����������	
		}
		if(Total_cycle<80 && Total_cycle>72)
		{
			LCD_Fill(110,4,110+17-17,11,WHITE); //�����������	
				
			LCD_Fill(110+17-17,4,110+17,11,BLACK); //�����������	
		}
	}
}

/*******************************************
* @function: 	����ʾ��Ļ����ʾ���ý���
* @input:			��
* @return:		��
* @author:		��С��
* @time:			2020.10.2
*******************************************/
void MENU_SETTING(void )
{

		LCD_Fill(0,0,LCD_W,LCD_H,WHITE); //�����������	
		
		LCD_ShowPicture(18,		50,		100,		100,	gImage_setting); //40*49
		
		LCD_ShowChinese(42,		170,	"����",	LBBLUE,	WHITE,24,0);
}

/*******************************************
* @function: 	����ʾ��Ļ����ʾ�ֵ�Ͳ����
* @input:			��
* @return:		��
* @author:		��С��
* @time:			2020.10.2
*******************************************/
void MENU_light(void )
{

		LCD_Fill(0,0,LCD_W,LCD_H,WHITE); //�����������	
		
		LCD_ShowPicture(18,		50,		100,		100,	gImage_light); //40*49
		
		LCD_ShowChinese(42,		170,	"����",	LGRAY,	WHITE,24,0);
}

/*******************************************
* @function: 	����ʾ��Ļ����ʾ����
* @input:			��
* @return:		��
* @author:		��С��
* @time:			2020.10.2
*******************************************/
void MENU_clock(void )
{

		LCD_Fill(0,0,LCD_W,LCD_H,WHITE); //�����������	
		
		LCD_ShowPicture(18,		50,		100,		100,	gImage_P_clock); //40*49
		
		LCD_ShowChinese(42,		170,	"����",	BRRED,	WHITE,24,0);
}


/*******************************************
* @function: 	����ʾ��Ļ����ʾ��Ϸ
* @input:			��
* @return:		��
* @author:		��С��
* @time:			2020.10.2
*******************************************/
void MENU_Game(void )
{

		LCD_Fill(0,0,LCD_W,LCD_H,WHITE); //�����������	
		
		LCD_ShowPicture(18,		50,		100,		100,	gImage_game); //40*49
		
		LCD_ShowChinese(42,		170,	"��Ϸ",	MAGENTA,	WHITE,24,0);
}

/*******************************************
* @function: 	����ʾ��Ļ����ʾ�˳�
* @input:			��
* @return:		��
* @author:		��С��
* @time:			2020.10.2
*******************************************/
void MENU_quit(void )
{

		LCD_Fill(0,0,LCD_W,LCD_H,WHITE); //�����������	
		
		LCD_ShowPicture(18,		50,		100,		100,	gImage_quit); //40*49
		
		LCD_ShowChinese(42,		170,	"����",	MAGENTA,	WHITE,24,0);
}

/*******************************************
* @function: 	����ʾ��Ļ����ʾ������
* @input:			��
* @return:		���������������������ֵ
* @author:		��С��
* @time:			2020.10.2
*******************************************/
void Refresh(void)
{
	unsigned char i;
	
	for (i=0;i<6;i++)
	{
		history_time[i] = 100;
	}
	
	Battery_display_flag = 100;
	
	MENU_init_();
	
	MENU_main();
}

/*******************************************
* @function: 	����ʾ��Ļ����ʾ������
* @input:			��
* @return:		���������������������ֵ
* @author:		��С��
* @time:			2020.10.2
*******************************************/
void MENU_APP(unsigned char switch_value)
{
	static unsigned char Number_of_cycles = function_clock;
	
	static unsigned char flag = 0;
	
//	static unsigned char flag__ = 0;
	
//	unsigned char i = 1;
	
	if(switch_value == Button_3_pressed || switch_value == Button_1_pressed)
	{

		flag = 1; //Ϊ�˷�ֹ���õ���Ļˢ�½�����ʾ�����ˢ�´������� //ֻ���ڰ�������֮���о�������˲Ż�ˢ��
		
		Number_of_cycles = function_clock;
		
		while(1)
		{
			switch_value = Get_Key_value(1);

			if(switch_value == Button_3_pressed) //����İ���
			{
				Number_of_cycles++;
				
				flag = 1; //Ϊ�˷�ֹ���õ���Ļˢ�½�����ʾ�����ˢ�´������� //ֻ���ڰ�������֮���о�������˲Ż�ˢ��
				
				if(Number_of_cycles > 5)
				{
					Number_of_cycles = 1;
				}
			}
			
			if(switch_value == 1)
			{
				Number_of_cycles--;
				
				flag = 1; //Ϊ�˷�ֹ���õ���Ļˢ�½�����ʾ�����ˢ�´������� //ֻ���ڰ�������֮���о�������˲Ż�ˢ��
				
				if(Number_of_cycles < 1)
				{
					Number_of_cycles = 5;
				}
			}
			///////////////////////////////////////////////////////////
			//��ʾ���ӽ���
			
			
			
			
			
			
			if(Number_of_cycles == function_clock && flag == 1)
			{
				MENU_clock();
				
				flag = 0; //Ϊ�˷�ֹ���õ���Ļˢ�½�����ʾ�����ˢ�´������� //��û�а�������ʱ�����Լ�ˢ����ʾ
			}
			//��ʾ��������
			if(Number_of_cycles == function_light  && flag == 1)
			{
				MENU_light();
				
				flag = 0; //Ϊ�˷�ֹ���õ���Ļˢ�½�����ʾ�����ˢ�´������� //��û�а�������ʱ�����Լ�ˢ����ʾ
			}
			//��ʾ��Ϸ����
			if(Number_of_cycles == function_game && flag == 1)
			{
				MENU_Game();
				
				flag = 0; //Ϊ�˷�ֹ���õ���Ļˢ�½�����ʾ�����ˢ�´������� //��û�а�������ʱ�����Լ�ˢ����ʾ
			}
			//��ʾ���ý���
			if(Number_of_cycles == function_set  && flag == 1)
			{
				MENU_SETTING();
				
				flag = 0; //Ϊ�˷�ֹ���õ���Ļˢ�½�����ʾ�����ˢ�´������� //��û�а�������ʱ�����Լ�ˢ����ʾ
			}
			//��ʾ�˳�����
			if(Number_of_cycles == function_quit && flag == 1)
			{
				MENU_quit();
				
				flag = 0; //Ϊ�˷�ֹ���õ���Ļˢ�½�����ʾ�����ˢ�´������� //��û�а�������ʱ�����Լ�ˢ����ʾ
			}
			
			
			//ѡ������Ҫ��ʾ�Ĺ���
			//flag = clock_function(Number_of_cycles,switch_value);
			if(Number_of_cycles == function_clock && switch_value == Button_2_pressed)
			{
				clock_function();
				
				flag = 1;
			}
			
			//ѡ������Ҫ��ʾ�Ĺ���
			if(Number_of_cycles == function_light  && switch_value == Button_2_pressed)
			{
				printf("����������app\r\n");
				
				light_function();
			}
			
			//ѡ����ϷҪ��ʾ�Ĺ���
			if(Number_of_cycles == function_game  && switch_value == Button_2_pressed)
			{
				printf("��������Ϸapp\r\n");
				
				APP_GAME();
				
				flag = 1;
			}
			
			//ѡ������Ҫ��ʾ�Ĺ��� //����ʱ�䡢�������ڡ����ñ��⡢��������������LED�����üƲ���
			if(Number_of_cycles == function_set && switch_value == Button_2_pressed)
			{
				//LCD_Fill(0,0,LCD_W,LCD_H,BLACK); //�����������
				printf("����������app\r\n");
				
				setting_function();
				
				flag = 1;
	
			}
						
			//���ص�������
			if(Number_of_cycles == function_quit && switch_value == Button_2_pressed)
			{
				LCD_Fill(0,0,LCD_W,LCD_H,BLACK); //�����������

				Refresh(); //ˢ�����������ʾ
				
				break;
			}
		}
	}
}




//void LOW_SystemClock_Config(void)
//{
//  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
//  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
//  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

//  /** Configure the main internal regulator output voltage 
//  */
//  __HAL_RCC_PWR_CLK_ENABLE();
//  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
//  /** Initializes the CPU, AHB and APB busses clocks 
//  */
//  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE|RCC_OSCILLATORTYPE_LSE;
//  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
//  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
//  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
//  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
//  RCC_OscInitStruct.PLL.PLLM = 15;
//  RCC_OscInitStruct.PLL.PLLN = 144;
//  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
//  RCC_OscInitStruct.PLL.PLLQ = 5;
//  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
//  {
//    Error_Handler();
//  }
//  /** Initializes the CPU, AHB and APB busses clocks 
//  */
//  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
//                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
//  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
//  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV4;
//  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
//  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

//  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
//  {
//    Error_Handler();
//  }
//  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
//  PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
//  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
//  {
//    Error_Handler();
//  }
//}

//void fun0()
{
	/**************���ܵľ���ʵ��****************/
	
	//__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, 0); //����PWM��ռ�ձȣ����ڱ���
	
	/*****************��������ʾ����***********************/
	
	/****************����͹���ģʽ���رմ󲿷���������Լ����*************************/	
	
	LCD_RES_Clr();//��ʾ��Ļ��λ
	
	 LOW_SystemClock_Config();
	/****************�ر�GPIO*********************/
	__HAL_RCC_DMA2_CLK_DISABLE(); //�ر�PWM�������
	__HAL_RCC_ADC1_CLK_DISABLE();	//�ر�ADC
	__HAL_RCC_I2C1_CLK_DISABLE();  //�ر�IICͨѶ
	__HAL_RCC_SPI1_CLK_DISABLE(); 	//�ر���Ļ��SPIͨѶ
	__HAL_RCC_TIM2_CLK_DISABLE();	//�ر�PWM���
	__HAL_RCC_TIM4_CLK_DISABLE();	//�ر�PWM���
	__HAL_RCC_USART1_CLK_DISABLE();//�رմ���ͨѶ
	
//	SystemClock_Config();
	
	//���뵽��ѭ���У����ҽ���ϵͳʱ��Ƶ�ʽ�һ������������
	while(1)
	{
		if(!HAL_GPIO_ReadPin(KEY_2_GPIO_Port, KEY_2_Pin)) break;
	}	
	
	SystemClock_Config();
	
	__HAL_RCC_DMA2_CLK_ENABLE(); //�ر�PWM�������
	__HAL_RCC_ADC1_CLK_ENABLE();	//�ر�ADC
	__HAL_RCC_I2C1_CLK_ENABLE();  //�ر�IICͨѶ
	__HAL_RCC_SPI1_CLK_ENABLE(); 	//�ر���Ļ��SPIͨѶ
	__HAL_RCC_TIM2_CLK_ENABLE();	//�ر�PWM���
	__HAL_RCC_TIM4_CLK_ENABLE();	//�ر�PWM���
	__HAL_RCC_USART1_CLK_ENABLE();//�رմ���ͨѶ
	
	LCD_Init();//LCD��ʼ��

//	LCD_ShowPicture(0,0,134,103,gImage_0);

//	key_choose = 0; //�Ѱ���ѡ����ԭλ
//	
//	function = -1; //�ѹ������»ص�������
//	
//	key_confirm = 0; //��ȷ�ϰ�������
	
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, 80); //����PWM��ռ�ձȣ����ڱ���
	
	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
			
}



