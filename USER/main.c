#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 
#include "24cxx.h"
#include "w25qxx.h"
#include "touch.h"
#include "timer.h"
#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "lv_apps\demo\demo.h" 
#include "lv_tests\lv_test_theme\lv_test_theme_1.h" 
#include "lv_tests\lv_test_theme\lv_test_theme_2.h"

#define TEST_NUM		1   //1,2,3�ֱ��Ӧ������ʾ����

int main(void)
{	 		    
	delay_init();	    	 				//��ʱ������ʼ��	  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 				//���ڳ�ʼ��Ϊ115200
	 
 	LED_Init();			     				//LED�˿ڳ�ʼ��
	LCD_Init();					 				//LCDҺ����ʼ��
	KEY_Init();	 				 				//������ʼ��
	TIM3_Int_Init(999,71);		 	//��ʱ����ʼ��(1ms�ж�),���ڸ�lvgl�ṩ��������	
 	tp_dev.init();							//������ʼ��
	 
	lv_init();									//lvglϵͳ��ʼ��
	lv_port_disp_init();				//lvgl��ʾ�ӿڳ�ʼ��,����lv_init()�ĺ���
	// 输入设备初始化
	lv_port_indev_init();				//lvgl����ӿڳ�ʼ��,����lv_init()�ĺ���
	
	//ͨ��TEST_NUM��ֵ��ѡ��ͬ������
	#if(TEST_NUM==1)
		demo_create();			
	#elif(TEST_NUM==2)
		lv_test_theme_1(lv_theme_night_init(210, NULL));
	#else
		lv_test_theme_2();
	#endif
	
	while(1)
	{
		tp_dev.scan(0);
		lv_task_handler();
	}
}


