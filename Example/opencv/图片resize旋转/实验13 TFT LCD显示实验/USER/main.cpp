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
			��ͼƬ����ֵ
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
		��ʾͼƬ
		src   ͼƬ����
		x,y   ͼ����ʾx,y��������Ļ���Ϸ�Ϊԭ��
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
void rotateImage(IplImage* img, IplImage *img_rotate,int degree)  
{  
    //��ת����Ϊͼ������  
    CvPoint2D32f center;    
    center.x=float (img->width/2.0+0.5);  
    center.y=float (img->height/2.0+0.5);  
    //�����ά��ת�ķ���任����  
    float m[6];              
    CvMat M = cvMat( 2, 3, CV_32F, m );  
    cv2DRotationMatrix( center, degree,1, &M);  
    //�任ͼ�񣬲��ú�ɫ�������ֵ  
 cvWarpAffine(img,img_rotate, 
&M,CV_INTER_LINEAR+CV_WARP_FILL_OUTLIERS,
cvScalarAll(0) );  
}

void test_IplImage()
{
	IplImage* src=cvCreateImage(cvSize(100,100),IPL_DEPTH_8U,3);  
	picture_read(src);
	lcd_show_pic(src,0,0);
	
	IplImage* img1 =cvCreateImage(cvSize(50,50), IPL_DEPTH_8U, 3);//����Ŀ��ͼ��
	
	cvResize(src,img1,CV_INTER_LINEAR );//resizeͼƬ
	cvReleaseImage(&src);//�ͷ��ڴ�

	lcd_show_pic(img1,100,0);

	IplImage* img2 =cvCreateImage(cvSize(50,50), IPL_DEPTH_8U, 3);//����Ŀ��ͼ��

	rotateImage(img1,img2,90);
	lcd_show_pic(img2,100,100);
	
  cvReleaseImage(&img1);
	cvReleaseImage(&img2);

}
int main(void)
{ 
 	u8 x=0;
	u8 lcd_id[12];				//���LCD ID�ַ���
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);      //��ʼ����ʱ����
	uart_init(115200);		//��ʼ�����ڲ�����Ϊ115200
	
	LED_Init();					  //��ʼ��LED
 	LCD_Init();           //��ʼ��LCD FSMC�ӿ�
	POINT_COLOR=RED;      //������ɫ����ɫ
	LCD_Clear(BLACK);
	
	test_IplImage();
	
 while(1);
}
//..\OBJ\LCD.axf: Error: L6218E: Undefined symbol cvRandArr (referred from cxutils.o).
//..\OBJ\LCD.axf: Error: L6218E: Undefined symbol cvNorm (referred from cxutils.o).
//..\OBJ\LCD.axf: Error: L6218E: Undefined symbol cvMinMaxLoc (referred from cxutils.o).
//..\OBJ\LCD.axf: Error: L6218E: Undefined symbol cvSVBkSb (referred from cxmatrix.o).
//..\OBJ\LCD.axf: Error: L6218E: Undefined symbol cvNormalize (referred from cxmatrix.o).
//..\OBJ\LCD.axf: Error: L6218E: Undefined symbol cvTranspose (referred from cxmatmul.o).
//..\OBJ\LCD.axf: Error: L6218E: Undefined symbol cvReduce (referred from cxmatmul.o).
//..\OBJ\LCD.axf: Error: L6218E: Undefined symbol cvGEMM (referred from cvimgwarp.o).
