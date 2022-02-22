#include "sys.h"

extern "C"{
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
}

#include "cv.h"
#include "cvaux.h"
#include "picture.h"

/*
			给图片赋初值
*/

void picture_read(IplImage* src)
{
	uchar* data=(uchar *)src->imageData;
	int channels = src->nChannels;
	int step = src->widthStep/sizeof(uchar);
	for(int i=0;i<src->height;i++)
	{
     for(int j=0;j<src->width;j++)
			{
				 data[i*step+j*channels+0]=gImage_a[i*src->width*channels+j*channels];
         data[i*step+j*channels+1]=gImage_a[i*src->width*channels+j*channels+1];
         data[i*step+j*channels+2]=gImage_a[i*src->width*channels+j*channels+2];
			}
			
	}
	
}

/*
		显示图片
		src   图片数组
		x,y   图像显示x,y坐标以屏幕左上方为原点
*/
void lcd_show_pic(IplImage* src ,int x,int y)
{
	
	
	uchar* data=(uchar *)src->imageData;
	int channels = src->nChannels;

	int data_test;
	int step = src->widthStep/sizeof(uchar);

	int r,g,b;
	
	LCD_Set_Window(x,y,src->height,src->height);
	LCD_SetCursor(x,y);
	LCD_WriteRAM_Prepare();
	
	for(int i=0;i<src->height;i++)
	{
     for(int j=0;j<src->width;j++)
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

void test_IplImage()
{
	IplImage* src=cvCreateImage(cvSize(100,100),IPL_DEPTH_8U,3);  
	picture_read(src);
	lcd_show_pic(src,0,0);
	
	IplImage* img1 = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);//创建目标图像
	cvCvtColor(src,img1,CV_BGR2GRAY);//灰度化图片
	
	lcd_show_pic(img1,100,100);
	
	cvReleaseImage(&src);
  cvReleaseImage(&img1);
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
