**Opencv 在STM32使用方法.**
>1.将项目中opencv文件夹添入你项目中。  
  2.根据项目所带KEIL5例子，依次将Groups opencv 中.cpp文件添加到你项目中。  
  3.添加bu.c,malloc.c到你项目中。  
  4.开始使用。相关函数介绍及文件位置，可自行搜索Opencv1.0 API介绍。

  **备注**:由于Stm32无操作系统，故图片输入采用一种特殊方法，先创建空白图片然后填写。以下为例子.    
``` c
 	IplImage* src=cvCreateImage(cvSize(40,40),IPL_DEPTH_8U,3);   // 40 40  3   图片维度
	uchar* data=(uchar *)src->imageData;
	int step = src->widthStep/sizeof(uchar);
	int channels = src->nChannels;
	for(int i=0;i<src->height;i++){
	     for(int j=0;j<src->width;j++){
		   data[i*step+j*channels+0]=102;
		   data[i*step+j*channels+1]=102;
		   data[i*step+j*channels+2]=255;
	      }		 
	}



