#ifndef __APP_H
#define __APP_H



/*******************************************
* @function: 	��Ϸ
* @input:			��
* @return:		��
* @author:		��С��
* @time:			2020.10.25
*******************************************/

void APP_GAME(void);
	

extern unsigned char Sound_switch;

/*******************************************
* @function: 	���ӵĹ���
* @input:			��
* @return:		��
* @author:		��С��
* @time:			2020.10.3
*******************************************/
void clock_function(void);


/*******************************************
* @function: 	���ӵĹ���
* @input:			��
* @return:		��
* @author:		��С��
* @time:			2020.10.3
*******************************************/
void light_function(void);
	

/*******************************************
* @function: 	���õĹ���
* @input:			��
* @return:		��
* @author:		��С��
* @time:			2020.10.3
*******************************************/
void setting_function(void);
	
	
	
/*******************************************
* @function: 	��̨�����Ӻ������ǵļƲ������м��
* @input:			��
* @return:		��
* @author:		��С��
* @time:			2020.10.5
*******************************************/
void Background_detection(unsigned char switch_value);



#endif


