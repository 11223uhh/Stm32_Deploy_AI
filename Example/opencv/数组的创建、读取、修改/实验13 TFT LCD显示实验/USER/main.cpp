#include "sys.h"

extern "C"{
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
}

#include "cv.h"
#include "cvaux.h"
#include "bu.h"


void test_IplImage()
{
	IplImage* src=cvCreateImage(cvSize(40,40),IPL_DEPTH_8U,3);  

	
	
	uchar* data=(uchar *)src->imageData;
	int step = src->widthStep/sizeof(uchar);
	int channels = src->nChannels;
	for(int i=0;i<src->height;i++)
	{
     for(int j=0;j<src->width;j++)
			{
           data[i*step+j*channels+0]=102;
           data[i*step+j*channels+1]=102;
           data[i*step+j*channels+2]=255;
      }
		 
	}
	int data_test;
	int r,g,b;
	
	LCD_Set_Window(100,100,src->height,src->height);
	LCD_SetCursor(100,100);
	LCD_WriteRAM_Prepare();
	
	for(int i=0;i<src->height;i++)
	{
		for(int j=0;j<src->height;j++)
		{
			
			 b=data[i*step+j*channels+0];
       g=data[i*step+j*channels+1];
       r=data[i*step+j*channels+2];
			
			
			data_test= (((unsigned(r) << 8) & 0xF800) |   
            ((unsigned(g) << 3) & 0x7E0)  |  
            ((unsigned(b) >> 3))); 
						
						
			LCD_WriteRAM(data_test);
		}
	}
}
int main(void)
{ 
 	u8 x=0;
	u8 lcd_id[12];				//存放LCD ID字符串
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);      //初始化延时函数
	uart_init(115200);		//初始化串口波特率为115200
	
	LED_Init();					  //初始化LED
 	LCD_Init();           //初始化LCD FSMC接口
	POINT_COLOR=RED;      //画笔颜色：红色
	LCD_Clear(BLACK);
	
	test_IplImage();
	
 while(1);
}
