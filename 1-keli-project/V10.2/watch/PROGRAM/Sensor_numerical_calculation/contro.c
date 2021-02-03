#include "contro.h"
#include "display.h"
#include "adc.h"
#include "dma.h"
#include "i2c.h"

#include "inv_mpu_dmp_motion_driver.h" 

#include "mpu6050Driver.h"

#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

#include "stdio.h"

#include "sht30_i2c_drv.h"

#include "app.h"

unsigned char usart_print_flag = 1; //�ǲ�����Ҫ������ʾ

unsigned long	STEPS = 0; //����

/*******************************************
* @function: 	����SHT30��ȡ��ʪ��ֵ��ʹ��IIC2������������Ҫע��˴���������Ƶ����ȡ����ֵ�����������޷���ȡ��������ʱ��Լһ����
* @input:			��
* @return:		ȫ�ֱ���
* @author:		��С��
* @time:			2020.10.22
*******************************************/
float temperature = 0.0;

float humidity = 0.0;

unsigned char flag_sht30 = 0;

void SHT30_Get_date(void)
{
	uint8_t recv_dat[6] = {0};
	if(	Total_cycle == 99	)
	{
		flag_sht30  = ! flag_sht30;
	}
	if(	flag_sht30	&& Total_cycle == 99	)
	{
		if(SHT30_Read_Dat(recv_dat) == HAL_OK)
		{
			if(SHT30_Dat_To_Float(recv_dat, &temperature, &humidity)==0)
			{
//				printf("T%f H%f", temperature, humidity);
				temperature = temperature -17; //��ȡ�����¶Ⱥ�ʵ�ʵ��¶���ƫ���ҪУ׼
			}
			else
			{
				printf("crc check fail.");
			}
		}
		else
		{
			printf("read data from sht30 fail.");
		}
	}
}



/*******************************************
* @function: 	����Ƿ���sub���ӣ����ߵ�ƽ���� PB12
* @input:			��
* @return:		����һ����־
* @author:		��С��
* @time:			2020.10.3
*******************************************/

unsigned char USB_in_sign;

void Test_usb_input(void)
{
	if(HAL_GPIO_ReadPin(USB_in_sign_GPIO_Port, USB_in_sign_Pin))//���ߵ�ƽ��Ϊ�ж���USB�豸���ӵ�����
	{
		USB_in_sign = Connected;
		//printf("��������������");
	}
	else
	{
		USB_in_sign = Not_connected;
	//	printf("û������");
	}
		
}

/*******************************************
* @function: 	������������
* @input:			��
* @return:		���������������������ֵ
* @author:		��С��
* @time:			2020.10.2
*******************************************/
unsigned char Screen_off_time = 0;

unsigned char set_Screen_off_flag = 1;

unsigned char	Total_cycle_sleep = 0;

unsigned char	Total_cycle_sleep_flag = 0;

uint8_t Get_Key_value(unsigned char flag)
{	 
	get_time(); //����ʱ����Ϩ����Ļ
	
	read_acc(); //���ݼ��ٶȵĴ�С��������Ļ
		
	/*ҡ��������������Ļ*/
	if(	ACX	>	1.6	&& Total_cycle_sleep_flag == 0 )
	{
		Total_cycle_sleep_flag = 1;
	}	
	if(	Total_cycle_sleep_flag == 1	)
	{
		Total_cycle_sleep++;
		
		if(	Total_cycle_sleep	<	150	&&	Total_cycle_sleep	>	100	&&	ACX	>	1.5)
		{
			Total_cycle_sleep_flag = 0;
			
			Total_cycle_sleep = 0 ;
			
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, 70); //����PWM��ռ�ձȣ����ڱ���

			Screen_off_time = sTime.Seconds + 10; //�����Զ�Ϩ����Ļ��ʱ����20��
			
			if(	Screen_off_time >	59	) //�����Ƶ���ĻϨ��ʵ��������һ���Ӿ͵��˻�ȥ
			{
				Screen_off_time = Screen_off_time -60; //�õ���ȷ��Ϩ��ʱ��
			}
			return 0;
		}
		if(	Total_cycle_sleep	>	150)
		{
			Total_cycle_sleep_flag = 0;
			
			Total_cycle_sleep	= 0;
		}
	}
	
	/*�ж��Ƿ񵽴��趨ʱ����Ϩ����Ļ*/
	if(	Screen_off_time == sTime.Seconds && flag)
	{
		/*Ϩ����Ļ*/
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, 0); //����PWM��ռ�ձȣ����ڱ���
		
		set_Screen_off_flag = 0; //�����Ѿ�Ϩ������Ļ Ϩ����Ļ��״̬�²��԰����Ȳ������з�Ӧ
	}
	
	if(!HAL_GPIO_ReadPin(KEY_1_GPIO_Port, KEY_1_Pin))
	{
		/*���°�����������Ļ*/
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, 70); //����PWM��ռ�ձȣ����ڱ���

		Screen_off_time = sTime.Seconds + 10; //�����Զ�Ϩ����Ļ��ʱ����20��
		
		if(	Screen_off_time >	59	) //�����Ƶ���ĻϨ��ʵ��������һ���Ӿ͵��˻�ȥ
		{
			Screen_off_time = Screen_off_time -60; //�õ���ȷ��Ϩ��ʱ��
		}
		
		
		while(!HAL_GPIO_ReadPin(KEY_1_GPIO_Port, KEY_1_Pin))
		{
			/*���������ж��ǲ�����Ҫ�ڰ��°�����ʱ�������������ʾ*/
			if(	Sound_switch	)	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, 50); 
			
			HAL_Delay(10);//ȥ���� 
			
			if(HAL_GPIO_ReadPin(KEY_1_GPIO_Port, KEY_1_Pin))
			{
				__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, 0);
				
				if( !set_Screen_off_flag ) //��⵽��Ļ����Ϩ���״̬�Ͳ��ܷ��ذ���ֵ
				{
					set_Screen_off_flag = 1; //�а��������ˣ�Ӧ�û�����Ļ
					
					return 0;
				}
				else
				{
					return Button_1_pressed;					
				}	
			}
		}
	}
	
	if(!HAL_GPIO_ReadPin(KEY_2_GPIO_Port, KEY_2_Pin))
	{
		/*���°�����������Ļ*/
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, 70); //����PWM��ռ�ձȣ����ڱ���

		Screen_off_time = sTime.Seconds + 10; //�����Զ�Ϩ����Ļ��ʱ����20��
		
		if(	Screen_off_time >	59	) //�����Ƶ���ĻϨ��ʵ��������һ���Ӿ͵��˻�ȥ
		{
			Screen_off_time = Screen_off_time -60; //�õ���ȷ��Ϩ��ʱ��
		}
		
		while(!HAL_GPIO_ReadPin(KEY_2_GPIO_Port, KEY_2_Pin))
		{
			if(	Sound_switch	)	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, 50);
			
			HAL_Delay(10);//ȥ���� 
			
			if(HAL_GPIO_ReadPin(KEY_2_GPIO_Port, KEY_2_Pin))
			{
				__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, 0);
				
				if( !set_Screen_off_flag ) //��⵽��Ļ����Ϩ���״̬�Ͳ��ܷ��ذ���ֵ
				{
					set_Screen_off_flag = 1; //�а��������ˣ�Ӧ�û�����Ļ
					
					return 0;
				}
				else
				{
					return Button_2_pressed;					
				}	
			}
		}
	}
	
	if(!HAL_GPIO_ReadPin(KEY_3_GPIO_Port, KEY_3_Pin))
	{
		
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, 70); //����PWM��ռ�ձȣ����ڱ���

		Screen_off_time = sTime.Seconds + 10; //�����Զ�Ϩ����Ļ��ʱ����20��
		
		if(	Screen_off_time >	59	) //�����Ƶ���ĻϨ��ʵ��������һ���Ӿ͵��˻�ȥ
		{
			Screen_off_time = Screen_off_time -60; //�õ���ȷ��Ϩ��ʱ��
		}
		
		
		while(!HAL_GPIO_ReadPin(KEY_3_GPIO_Port, KEY_3_Pin))
		{
			if(	Sound_switch	)	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, 50);
			
			HAL_Delay(10);//ȥ���� 
			
			if(HAL_GPIO_ReadPin(KEY_3_GPIO_Port, KEY_3_Pin))
			{
				__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, 0);
				
				if( !set_Screen_off_flag ) //��⵽��Ļ����Ϩ���״̬�Ͳ��ܷ��ذ���ֵ
				{
					set_Screen_off_flag = 1; //�а��������ˣ�Ӧ�û�����Ļ
					
					return 0;
				}
				else
				{
					return Button_3_pressed;					
				}	
			}
		}
	}
	return 0;// �ް�������
}


/*******************************************
* @function: 	ʹ��STM32����ADC��ȡ��ص�ѹֵ������ȡ���ĵ�ѹֵ������ȫ�ֱ����У���ADC1ͨ��10����Ӧ����PA4
* @input:			��
* @return:		�����Ϊȫ�ֱ���ֱ��ʹ��
* @author:		��С��
* @time:			2020.9.1
*******************************************
*/
float ADC_Value_BATTERY;

int Battery_voltage = 0; //��ص�ѹ�İٷֱ� 

float Battery_voltage_[10]; //�����ʷ��ѹ���������л���ƽ���˲� 

float Battery_voltage_history; //�����ʷ��ѹ���������л���ƽ���˲� 


void Obtain_battery_voltage(void)
{
	unsigned char i	=	0;
	
	HAL_ADC_Start(&hadc1);  //��ADC1
		
	HAL_ADC_PollForConversion(&hadc1, 10); //

	if(HAL_IS_BIT_SET(HAL_ADC_GetState(&hadc1), HAL_ADC_STATE_REG_EOC))
	{
		ADC_Value_BATTERY = HAL_ADC_GetValue(&hadc1); //��ȡADCֵ�����ADC_Value_BATTERY��
	}	
	Battery_voltage_history = 0 ; //���ڻ�ȡ�ĵ�ѹֵ���в�����ʹ�û���ƽ���˲���������Ҫ����ʮ�β�����Ч����
	
	
	for(i=0;i<9;i++)
	{
		Battery_voltage_[i] = Battery_voltage_[i+1];
	}
//	Battery_voltage_[9] = 2*ADC_Value_BATTERY*3.3f/4096+0.15;	//��صĵ�ѹֵ
	
	Battery_voltage_[9] = 2*ADC_Value_BATTERY*3.3f/4096;	//��صĵ�ѹֵ
	
//	printf("��ص�ѹ��%.1f",Battery_voltage_[9]);
	
	for(i=0;i<10;i++) //�Ѵ��������ĵ�ص�ѹ����ʷֵ������ƽ��ֵ����
	{
		Battery_voltage_history = Battery_voltage_[i] +	Battery_voltage_history;
	}
	Battery_voltage_history = Battery_voltage_history/10; //���յõ��ĵ�ص�ѹ��ƽ��ֵ
	
	Battery_voltage = Battery_voltage_history*200 - 731; //���յõ��ĵ�ص����İٷֱ�
}

/*******************************************
* @function: 	ʹ��STM32����ADC��ȡ��ص�ѹֵ������ȡ���ĵ�ѹֵ������ȫ�ֱ����У���ADC1ͨ��1 ����Ӧ����PA1
* @input:			��
* @return:		�����Ϊȫ�ֱ���ֱ��ʹ��
* @author:		��С��
* @time:			2020.10.2
*******************************************/
RTC_DateTypeDef sDate; //ȫ�ֱ������ⲿ����ֱ�ӵ���ʹ�� �������������

RTC_TimeTypeDef sTime; //ȫ�ֱ������ⲿ����ֱ�ӵ���ʹ�� �����ʱ������

void get_time(void)
{
	/*ʱ���ȡ����*/
	
	HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN); //��ȡ����
		
	HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN); //��ȡʱ��
}



/*******************************************
* @function: 	�Ը������������ֵ����ݴ��������е��ú�����
* @input:			��
* @return:		�����Ϊȫ�ֱ���ֱ��ʹ��
* @author:		��С��
* @time:			2020.10.2
*******************************************/
void Get_Sensor_data(void)
{
	get_time();//��ȡRTCʱ�ӵ�ʱ��
	
	Obtain_battery_voltage(); //��ȡ��صĵ�ѹֵ
	
	Test_usb_input(); //����ǲ�����USB�豸�Ľ���
	
	SHT30_Get_date(); //�����ʪ��
	
	dmp_get_pedometer_step_count(&STEPS); //�Ʋ�����ȡ������
//				printf("%d\r\n",STEPS);
}




