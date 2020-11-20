#ifndef __CONTRO_H
#define __CONTRO_H 	   

#include "rtc.h"

#define Connected 0
#define Not_connected 1

#define function_clock 	1
#define function_light 	2
#define function_game  	3
#define function_set 		4
#define function_quit 	5

#define Button_1_pressed 	1
#define Button_2_pressed 	2
#define Button_3_pressed 	3


extern	unsigned char set_Screen_off_flag ; //��Ļ�ǲ����Ѿ�Ϩ����

extern unsigned char usart_print_flag; //�ǲ�����Ҫ������ʾ
                                                                                          
extern	unsigned long	STEPS; //����

extern float temperature ; //�¶�ֵ

extern float humidity ; //ʪ��ֵ

	
extern unsigned char USB_in_sign;

/*******************************************
* @function: 	������������
* @input:			��
* @return:		���������������������ֵ
* @author:		��С��
* @time:			2020.10.2
*******************************************/

extern	unsigned char Screen_off_time;

uint8_t Get_Key_value(unsigned char flag);



extern	float ADC_Value_BATTERY;
extern	int Battery_voltage; //��ص�ѹ�İٷֱ� 
extern	float Battery_voltage_[10]; //�����ʷ��ѹ���������л���ƽ���˲� 
extern	float Battery_voltage_history; //�����ʷ��ѹ���������л���ƽ���˲� 
	
/*******************************************
* @function: 	ʹ��STM32����ADC��ȡ��ص�ѹֵ������ȡ���ĵ�ѹֵ������ȫ�ֱ����У���ADC1ͨ��10����Ӧ����PA4
* @input:			��
* @return:		�����Ϊȫ�ֱ���ֱ��ʹ��
* @author:		��С��
* @time:			2020.9.1
*******************************************
*/
void Obtain_battery_voltage(void);



/*******************************************
* @function: 	ʹ��STM32����ADC��ȡ��ص�ѹֵ������ȡ���ĵ�ѹֵ������ȫ�ֱ����У���ADC1ͨ��1 ����Ӧ����PA1
* @input:			��
* @return:		�����Ϊȫ�ֱ���ֱ��ʹ��
* @author:		��С��
* @time:			2020.10.2
*******************************************/
extern RTC_DateTypeDef sDate; //ȫ�ֱ������ⲿ����ֱ�ӵ���ʹ�� �������������

extern RTC_TimeTypeDef sTime; //ȫ�ֱ������ⲿ����ֱ�ӵ���ʹ�� �����ʱ������

void get_time(void);


/*******************************************
* @function: 	�Ը������������ֵ����ݴ��������е��ú�����
* @input:			��
* @return:		�����Ϊȫ�ֱ���ֱ��ʹ��
* @author:		��С��
* @time:			2020.10.2
*******************************************/
void Get_Sensor_data(void);
	

#endif



