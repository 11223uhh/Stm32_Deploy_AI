#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"

#include <stdint.h>
#include <stdio.h>
#include "mode1.h"
#include "ai.h"


 const q7_t conv1_wt[CONV_IM_CH_0 * CONV_KER_DIM_0 * CONV_KER_DIM_0 * CONV_OUT_CH_0] = Conv2D_0_weight;
 const q7_t conv1_bias[CONV_OUT_CH_0] = Conv2D_0bias;


const  q7_t conv2_wt[CONV_IM_CH_2 * CONV_KER_DIM_2 * CONV_KER_DIM_2 * CONV_OUT_CH_2] = Conv2D_1_weight;
 const q7_t conv2_bias[CONV_OUT_CH_2] = Conv2D_1bias;


 q7_t ip1_wt[256 * 10] = Dense_2_weight;

q7_t ip1_bias[IP1_OUT_4] = Dense_2bias;


q7_t      scratch_buffer[15*24*240];

 /*
 void corr2d(q7_t *X_TEMP,q7_t *K,q7_t X_shape[2],q7_t K_shape[2],q7_t scale,q15_t *Y,int j2,int ch_im_in,
 		 const q7_t *bias,
 		 const uint16_t bias_shift,
         const uint16_t out_shift,
         q7_t *Im_out,)
  */
	
uint8_t   image_data[CONV_IM_CH_0 * CONV_IM_DIM_0 * CONV_IM_DIM_0] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,66,127,113,5,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,65,123,92,65,22,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,46,126,67,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,29,117,102,2,0,1,0,2,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,78,126,59,1,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,33,124,81,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,54,127,69,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,89,113,20,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,8,115,69,0,0,0,0,0,0,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,67,127,51,0,0,0,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,109,126,13,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,113,97,2,0,0,0,0,0,0,16,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,30,127,57,0,0,0,0,12,70,76,120,118,64,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,30,125,37,1,0,0,41,112,124,78,76,127,106,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,28,126,52,0,0,42,124,108,30,0,19,126,59,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,29,127,36,0,7,124,79,7,0,3,101,127,35,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,19,117,74,2,3,75,37,0,3,96,126,61,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,109,126,46,0,2,5,36,112,126,62,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,38,123,124,112,112,115,127,121,59,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,57,88,127,127,117,75,21,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	q7_t      output_data[IP1_OUT_4];


 int main()
 {
	 	q7_t     *img_buffer1 = scratch_buffer;
  q7_t     *img_buffer2 = img_buffer1 + CONV_OUT_CH_0 * CONV_OUT_DIM_0 * CONV_OUT_DIM_0;//+ CONV1_OUT_CH * CONV1_OUT_DIM * CONV1_OUT_DIM为卷积运算完存数据做的操作
q7_t     *temp_po;
  for (int i=0;i<28*28*1; i++) 
	{
    img_buffer2[i] =(q7_t)image_data[i];//这一步不清楚 应该是往数组存数据
  }
	
	 	arm_convolve_HWC_q7_basic(img_buffer2, 
													CONV_IM_DIM_0, CONV_IM_CH_0, conv1_wt, 
													CONV_OUT_CH_0, 
										      CONV_KER_DIM_0, CONV_PADDING_0,CONV_STRIDE_0, 
													conv1_bias, 
													CONV_BIAS_LSHIFT_0, CONV_OUT_RSHIFT_0, 
													img_buffer1, 
													CONV_OUT_DIM_0,
                          NULL, NULL);	
	
	  arm_relu_q7(img_buffer1, CONV_OUT_DIM_0 * CONV_OUT_DIM_0 * CONV_OUT_CH_0);
 arm_maxpool_q7_HWC(img_buffer1, CONV_OUT_DIM_0, CONV_OUT_CH_0, POOL_KER_DIM_1,
                     POOL_PADDING_1, POOL_STRIDE_1, POOL_OUT_DIM_1, NULL, img_buffer2);
	
	
	 arm_convolve_HWC_q7_basic(img_buffer2, CONV_IM_DIM_2, CONV_IM_CH_2, conv2_wt, CONV_OUT_CH_2, CONV_KER_DIM_2,
                           CONV_PADDING_2, CONV_STRIDE_2, conv2_bias, CONV_BIAS_LSHIFT_2 ,CONV_OUT_RSHIFT_2, img_buffer1,
                           CONV_OUT_DIM_2, NULL, NULL);
	  arm_relu_q7(img_buffer1, CONV_OUT_DIM_2 * CONV_OUT_DIM_2 * CONV_OUT_CH_2);
arm_maxpool_q7_HWC(img_buffer1, CONV_OUT_DIM_2, CONV_OUT_CH_2, POOL_KER_DIM_3,
                     POOL_PADDING_3, POOL_STRIDE_3, POOL_OUT_DIM_3, NULL, img_buffer2);		

  arm_fully_connected_q7(img_buffer2, ip1_wt, IP1_DIM_4, IP1_OUT_4, Dense_BIAS_LSHIFT_4, Dense_OUT_RSHIFT_4, ip1_bias,
                             output_data, (q15_t *) img_buffer1);
		arm_softmax_q7(output_data,10,output_data)		;										 
													 
	for (int i = 0; i < 10; i++)
		{
				printf("%d: %d\n", i, output_data[i]);
		}
		
	
	
	
	
	 

 }

