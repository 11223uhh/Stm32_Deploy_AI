/*
   Serial
   串口通讯实验
*/
int incomedate = 0;


#define CONV_IM_DIM_0 28
#define CONV_IM_CH_0 1
#define CONV_OUT_DIM_0 8
#define CONV_OUT_CH_0 1
#define CONV_KER_DIM_0 21
#define CONV_STRIDE_0 1
#define CONV_PADDING_0 0
#define CONV_BIAS_LSHIFT_0 7
#define CONV_OUT_RSHIFT_0 9

#define POOL_OUT_DIM_1 4
#define POOL_KER_DIM_1 2
#define POOL_STRIDE_1 2
#define POOL_PADDING_1 0


#define IP1_DIM_2 16
#define IP1_OUT_2 10
#define Dense_BIAS_LSHIFT_2 7
#define Dense_OUT_RSHIFT_2 9

#define Conv2D_0_weight {24,37,39,35,31,27,8,7,11,4,-5,5,-7,-10,-20,-8,-3,0,10,8,-5,13,11,6,-2,-2,5,-7,8,10,7,2,0,-9,-5,-2,-1,-16,-24,-21,-29,-42,3,-2,-7,-24,-16,-23,-22,-31,-23,-11,-13,-19,-4,6,16,33,32,16,12,1,-39,15,-2,4,2,-6,-3,1,7,0,11,4,21,15,10,7,8,7,11,10,13,4,31,14,15,18,15,23,26,26,39,29,38,28,14,21,11,0,-4,9,16,-3,28,46,17,37,25,29,44,26,26,33,32,45,22,18,10,7,11,7,5,16,3,51,36,19,21,30,26,24,35,33,22,16,25,20,24,12,13,5,2,6,16,5,47,38,14,20,16,17,25,32,21,11,14,19,32,25,23,18,20,17,11,11,0,17,35,6,13,3,7,12,9,10,11,13,18,23,36,33,23,16,2,4,-3,-20,-18,6,-3,-2,-3,-8,-10,-9,-11,-4,1,11,40,54,28,6,11,10,1,-13,-6,-33,-8,-13,-17,-20,-33,-43,-25,-20,-8,2,10,46,44,26,8,7,11,-5,-18,-10,-46,-42,-41,-41,-38,-37,-37,-26,-20,-25,-4,14,39,28,6,6,-2,-20,-12,-8,-13,-39,-36,-44,-55,-50,-45,-42,-42,-34,-30,-10,0,36,14,6,9,-19,-10,4,-16,-8,-22,-34,-50,-44,-48,-34,-31,-40,-21,-32,-8,-10,15,0,-4,-6,-5,-4,-17,-7,7,-11,-23,-10,-21,-33,-38,-27,-13,-13,-13,2,0,2,-2,2,0,4,-6,-9,-10,-11,-3,-10,1,-2,-4,-14,-12,-11,-10,-2,-8,-8,-6,5,-9,-3,-1,-4,-4,-5,-4,0,3,11,17,-5,7,0,-16,-8,-7,-15,0,-14,-8,-7,-9,-7,-6,-5,2,-15,8,3,4,10,-17,2,-3,4,-1,1,3,-6,3,4,13,5,8,13,7,14,10,30,10,19,-8,-5,7,2,11,2,1,-2,-2,-2,1,-16,2,10,12,23,26,20,44,20,6,-18,-7,-2,7,15,17,12,17,16,5,8,2,3,7,12,20,26,27,64,35,17,4,10,7,3,8,8,16,14,32,41,54,61,52,50,47,61,46,56,72}



#define Conv2D_0bias {29}

#define Dense_1_weight {40,-20,-63,14,127,-82,-89,113,67,-105,-65,121,2,-51,-59,-10,-110,127,20,-18,-47,56,18,-127,-60,110,37,-55,-38,77,-47,-75,46,5,67,78,-66,18,-48,-14,17,9,10,-23,28,-40,-22,-6,-70,89,60,16,8,24,-63,-22,23,27,18,14,-99,-4,9,53,-19,-98,-1,1,68,-42,64,-29,-57,-75,25,-56,51,55,82,32,59,-34,-90,-29,73,37,-16,3,23,6,-23,62,-50,-16,-21,-10,127,7,-41,-18,-46,-7,8,-21,-15,-40,-85,-29,94,-8,-14,26,-106,29,59,-35,-55,-22,55,45,-67,28,59,61,-46,78,-6,-8,14,-57,-26,35,60,58,-7,-16,-16,37,1,-8,67,-47,-37,-10,2,-25,-5,-49,-120,-15,84,92,98,-20,-4,-67,10,-34,90,15}




#define Dense_1bias {0,6,2,-30,18,78,4,-22,-46,-9}




typedef int8_t q7_t;
typedef int16_t q15_t;
typedef int32_t q31_t;
typedef int64_t q63_t;
typedef float float32_t;
typedef double float64_t;
#define NN_ROUND(out_shift) ((0x1u << out_shift) >> 1)


typedef enum
{
  ARM_MATH_SUCCESS                 =  0,        /**< No error */
  ARM_MATH_ARGUMENT_ERROR          = -1,        /**< One or more arguments are incorrect */
  ARM_MATH_LENGTH_ERROR            = -2,        /**< Length of data buffer is incorrect */
  ARM_MATH_SIZE_MISMATCH           = -3,        /**< Size of matrices is not compatible with the operation */
  ARM_MATH_NANINF                  = -4,        /**< Not-a-number (NaN) or infinity is generated */
  ARM_MATH_SINGULAR                = -5,        /**< Input matrix is singular and cannot be inverted */
  ARM_MATH_TEST_FAILURE            = -6,        /**< Test Failed */
  ARM_MATH_DECOMPOSITION_FAILURE   = -7         /**< Decomposition Failed */
} arm_status;


const q7_t conv1_wt[CONV_IM_CH_0 * CONV_KER_DIM_0 * CONV_KER_DIM_0 * CONV_OUT_CH_0] = Conv2D_0_weight;
const q7_t conv1_bias[CONV_OUT_CH_0] = Conv2D_0bias;


q7_t ip1_wt[IP1_DIM_2 * IP1_OUT_2] = Dense_1_weight;

q7_t ip1_bias[IP1_OUT_2] = Dense_1bias;





q7_t      output_data[IP1_OUT_2];
q7_t      scratch_buffer[848];

#define RXBUFFERSIZE  5     //最大接收字节数
uint8_t RxBuffer[RXBUFFERSIZE];   //接收数据
int aRxBuffer;      //接收中断缓冲

uint8_t Uart1_Rx_Cnt = 0;   //接收缓冲计数

int data_actu;
int count;
int run_flag = 0;
  q7_t     *img_buffer1 = scratch_buffer;
  q7_t     *img_buffer2 = img_buffer1 + CONV_OUT_CH_0 * CONV_OUT_DIM_0 * CONV_OUT_DIM_0;

void setup() {

  Serial.begin(9600); //设置串口波特率9600

}

void loop() {

  if (run_flag == 1)
  {
    run_flag = 0;
    AI_Run();

  }


}


void AI_Run()
{

  unsigned int ALL_timecnt;

  unsigned int timecnt1;
  unsigned int timecnt2;

  unsigned int timecnt3;
  unsigned int timecnt4;
  unsigned int timecnt5;

  ALL_timecnt = micros();//us


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
      
     timecnt1 = micros();    //conv OPS 3.19M


   arm_maxpool_q7_HWC(img_buffer1, CONV_OUT_DIM_0, CONV_OUT_CH_0, POOL_KER_DIM_1,
                     POOL_PADDING_1, POOL_STRIDE_1, POOL_OUT_DIM_1, NULL, img_buffer2);
   

      
 
  timecnt2 = micros();//us

   arm_fully_connected_q7(img_buffer2, ip1_wt, IP1_DIM_2, IP1_OUT_2, Dense_BIAS_LSHIFT_2, Dense_OUT_RSHIFT_2, ip1_bias,
                             output_data, (q15_t *) img_buffer1);

  timecnt3 = micros();
  
          
  arm_softmax_q7(output_data, 10, output_data);
  
  timecnt4 = micros();
  

  int max_temp=0;
  int lable=0;                             
  for (int i = 0; i < 10; i++)
    {
      if(output_data[i]>max_temp)
      {
        lable=i;
        max_temp=output_data[i];
      }
    }
  Serial.print("Conv_time=");
  Serial.print((timecnt1-ALL_timecnt)/1000); 
  Serial.print("  |");   
  Serial.print((56448*1000/(3.70*1000*1000)));   //CONV OPS 1.25M

 Serial.println("  ms");    
  Serial.print("den_time=");
  Serial.print("0."); 
  Serial.print((timecnt3-timecnt2));   
  Serial.print("|"); 
  
  Serial.print("0."); 
  Serial.print(int (320/(1.6)));   
     
  Serial.println("  ms");   
  Serial.print("time "); 
  Serial.print((timecnt4-ALL_timecnt)/1000);   //Dense OPS 1.6M
    Serial.println(" ms");   

   Serial.print("result ");
   Serial.println(lable);
   timecnt1=0;
   timecnt2=0;
   timecnt3=0;
   timecnt4=0;
   timecnt5=0;
}


void serialEvent()
{
  while (Serial.available())
  {

    data_actu = (char)Serial.read();

    RxBuffer[Uart1_Rx_Cnt++] = data_actu;   //接收数据转存

    if ((Uart1_Rx_Cnt>=3)&&(RxBuffer[Uart1_Rx_Cnt - 1] == 0x0A) && (RxBuffer[Uart1_Rx_Cnt - 2] == 0x0D)) //判断结束位
    {


      switch (Uart1_Rx_Cnt) {
        case 5: data_actu = (RxBuffer[Uart1_Rx_Cnt - 3] - 48) + (RxBuffer[Uart1_Rx_Cnt - 4] - 48) * 10 + (RxBuffer[Uart1_Rx_Cnt - 5] - 48) * 100; break;
        case 4: data_actu = (RxBuffer[Uart1_Rx_Cnt - 3] - 48) + (RxBuffer[Uart1_Rx_Cnt - 4] - 48) * 10; break;
        case 3: data_actu = (RxBuffer[Uart1_Rx_Cnt - 3] - 48); break;

      }
      img_buffer2[count] = data_actu;

      count++;
      if (count == (28 * 28 ))
      {

        run_flag = 1;

        count = 0;
      }
     
      Uart1_Rx_Cnt = 0;
      memset(RxBuffer, 0x00, sizeof(RxBuffer)); //清空数组
    }
  }


}

int32_t __SSAD(int32_t val, uint32_t sat)
{
  if ((sat >= 1U) && (sat <= 32U))
  {
    const int32_t max = (int32_t)((1U << (sat - 1U)) - 1U);
    const int32_t min = -1 - max ;
    if (val > max)
    {
      return max;
    }
    else if (val < min)
    {
      return min;
    }
  }
  return val;
}
uint32_t __USAT(int32_t val, uint32_t sat)
{
  if (sat <= 31U)
  {
    const uint32_t max = ((1U << sat) - 1U);
    if (val > (int32_t)max)
    {
      return max;
    }
    else if (val < 0)
    {
      return 0U;
    }
  }
  return (uint32_t)val;
}
arm_status arm_convolve_HWC_q7_basic(const q7_t *Im_in,
                                     const uint16_t dim_im_in,
                                     const uint16_t ch_im_in,
                                     const q7_t *wt,
                                     const uint16_t ch_im_out,
                                     const uint16_t dim_kernel,
                                     const uint16_t padding,
                                     const uint16_t stride,
                                     const q7_t *bias,
                                     const uint16_t bias_shift,
                                     const uint16_t out_shift,
                                     q7_t *Im_out,
                                     const uint16_t dim_im_out,
                                     q15_t *bufferA,
                                     q7_t *bufferB)
{
    

    int i, j, k, l, m, n;
    long int conv_out;
    int in_row, in_col;

    for (i = 0; i < ch_im_out; i++)
    {
        for (j = 0; j < dim_im_out; j++)
        {
            for (k = 0; k < dim_im_out; k++)
            {
                conv_out = ((q31_t)bias[i] << bias_shift) + NN_ROUND(out_shift);
                for (m = 0; m < dim_kernel; m++)
                {
                    for (n = 0; n < dim_kernel; n++)
                    {
                        // if-for implementation
                        in_row = stride * j + m - padding;
                        in_col = stride * k + n - padding;
                        if (in_row >= 0 && in_col >= 0 && in_row < dim_im_in && in_col < dim_im_in)
                        {
                            for (l = 0; l < ch_im_in; l++)
                            {
                                conv_out += Im_in[(in_row * dim_im_in + in_col) * ch_im_in + l] *
                                    wt[i * ch_im_in * dim_kernel * dim_kernel + (m * dim_kernel + n) * ch_im_in + l];
                            }
                        }
                    }
                }
                Im_out[i + (j * dim_im_out + k) * ch_im_out] = (q7_t)__SSAD((conv_out >> out_shift), 8);
            }
        }
    }


    /* Return to application */
    return ARM_MATH_SUCCESS;
}
arm_status arm_convolve_HWC_q7_fast(const q7_t *Im_in,
                                    const uint16_t dim_im_in,
                                    const uint16_t ch_im_in,
                                    const q7_t *wt,
                                    const uint16_t ch_im_out,
                                    const uint16_t dim_kernel,
                                    const uint16_t padding,
                                    const uint16_t stride,
                                    const q7_t *bias,
                                    const uint16_t bias_shift,
                                    const uint16_t out_shift,
                                    q7_t *Im_out,
                                    const uint16_t dim_im_out,
                                    q15_t *bufferA,
                                    q7_t *bufferB)
{
    (void)bufferB;

    (void)bufferA;
    /* Run the following code as reference implementation for Cortex-M0 and Cortex-M3 */
    int i, j, k, l, m, n;
    long int conv_out;
    int in_row, in_col;

    if (ch_im_in % 4 != 0 || ch_im_out % 2 != 0)
    {
        /* check if the input dimension meets the constraints */
        return ARM_MATH_SIZE_MISMATCH;
    }

    for (i = 0; i < ch_im_out; i++)
    {
        for (j = 0; j < dim_im_out; j++)
        {
            for (k = 0; k < dim_im_out; k++)
            {
                conv_out = (bias[i] << bias_shift) + NN_ROUND(out_shift);
                for (m = 0; m < dim_kernel; m++)
                {
                    for (n = 0; n < dim_kernel; n++)
                    {
                        // if-for implementation
                        in_row = stride * j + m - padding;
                        in_col = stride * k + n - padding;
                        if (in_row >= 0 && in_col >= 0 && in_row < dim_im_in && in_col < dim_im_in)
                        {
                            for (l = 0; l < ch_im_in; l++)
                            {
                                conv_out += Im_in[(in_row * dim_im_in + in_col) * ch_im_in + l] *
                                    wt[i * ch_im_in * dim_kernel * dim_kernel + (m * dim_kernel + n) * ch_im_in + l];
                            }
                        }
                    }
                }
                Im_out[i + (j * dim_im_out + k) * ch_im_out] = (q7_t)__SSAD((conv_out >> out_shift), 8);
            }
        }
    }


    /* Return to application */
    return ARM_MATH_SUCCESS;
}
void arm_relu_q7(q7_t *data, uint16_t size)
{

    uint16_t i;

    for (i = 0; i < size; i++)
    {
        if (data[i] < 0)
            data[i] = 0;
    }


}
void arm_maxpool_q7_HWC(q7_t *Im_in,
                        const uint16_t dim_im_in,
                        const uint16_t ch_im_in,
                        const uint16_t dim_kernel,
                        const uint16_t padding,
                        const uint16_t stride,
                        const uint16_t dim_im_out,
                        q7_t *bufferA,
                        q7_t *Im_out)
{
    (void)bufferA;

    int16_t i_ch_in, i_x, i_y;
    int16_t k_x, k_y;

    for (i_ch_in = 0; i_ch_in < ch_im_in; i_ch_in++)
    {
        for (i_y = 0; i_y < dim_im_out; i_y++)
        {
            for (i_x = 0; i_x < dim_im_out; i_x++)
            {
                int max = -129;
                for (k_y = i_y * stride - padding; k_y < i_y * stride - padding + dim_kernel; k_y++)
                {
                    for (k_x = i_x * stride - padding; k_x < i_x * stride - padding + dim_kernel; k_x++)
                    {
                        if (k_y >= 0 && k_x >= 0 && k_y < dim_im_in && k_x < dim_im_in)
                        {
                            if (Im_in[i_ch_in + ch_im_in * (k_x + k_y * dim_im_in)] > max)
                            {
                                max = Im_in[i_ch_in + ch_im_in * (k_x + k_y * dim_im_in)];
                            }
                        }
                    }
                }
                Im_out[i_ch_in + ch_im_in * (i_x + i_y * dim_im_out)] = max;
            }
        }
    }

}
void arm_avepool_q7_HWC(q7_t *Im_in,
                        const uint16_t dim_im_in,
                        const uint16_t ch_im_in,
                        const uint16_t dim_kernel,
                        const uint16_t padding,
                        const uint16_t stride,
                        const uint16_t dim_im_out,
                        q7_t *bufferA,
                        q7_t *Im_out)
{

    (void)bufferA;
    int16_t i_ch_in, i_x, i_y;
    int16_t k_x, k_y;

    for (i_ch_in = 0; i_ch_in < ch_im_in; i_ch_in++)
    {
        for (i_y = 0; i_y < dim_im_out; i_y++)
        {
            for (i_x = 0; i_x < dim_im_out; i_x++)
            {
                int sum = 0;
                int count = 0;
                for (k_y = i_y * stride - padding; k_y < i_y * stride - padding + dim_kernel; k_y++)
                {
                    for (k_x = i_x * stride - padding; k_x < i_x * stride - padding + dim_kernel; k_x++)
                    {
                        if (k_y >= 0 && k_x >= 0 && k_y < dim_im_in && k_x < dim_im_in)
                        {
                            sum += Im_in[i_ch_in + ch_im_in * (k_x + k_y * dim_im_in)];
                            count++;
                        }
                    }
                }
                Im_out[i_ch_in + ch_im_in * (i_x + i_y * dim_im_out)] = sum / count;
            }
        }
    }

}
arm_status arm_fully_connected_q7(const q7_t *pV,
                                  const q7_t *pM,
                                  const uint16_t dim_vec,
                                  const uint16_t num_of_rows,
                                  const uint16_t bias_shift,
                                  const uint16_t out_shift,
                                  const q7_t *bias,
                                  q7_t *pOut,
                                  q15_t *vec_buffer)
{


    (void)vec_buffer;
    int i, j;

    /* Run the following code as reference implementation for Cortex-M0 and Cortex-M3 */
    for (i = 0; i < num_of_rows; i++)
    {
        int ip_out = ((q31_t)(bias[i]) << bias_shift) + NN_ROUND(out_shift);
        for (j = 0; j < dim_vec; j++)
        {
          
            ip_out += pV[j] * pM[i * dim_vec + j];
        }
        pOut[i] = (q7_t)__SSAD((ip_out >> out_shift), 8);
    }


    /* Return to ARM_MATH_SUCCESS */
    return (ARM_MATH_SUCCESS);
}
void arm_softmax_q7(const q7_t *vec_in, const uint16_t dim_vec, q7_t *p_out)
{
    q31_t sum;
    int16_t i;
    uint8_t shift;
    q15_t base;
    base = -128;

    /* We first search for the maximum */
    for (i = 0; i < dim_vec; i++)
    {
        if (vec_in[i] > base)
        {
            base = vec_in[i];
        }
    }

    /*
     * So the base is set to max-8, meaning
     * that we ignore really small values.
     * anyway, they will be 0 after shrinking to q7_t.
     */
    base = base - (1 << 3);

    sum = 0;

    for (i = 0; i < dim_vec; i++)
    {
        shift = (uint8_t)__USAT(vec_in[i] - base, 3);
        sum += 0x1 << shift;
    }

    /* This is effectively (0x1 << 20) / sum */
    long int output_base = (1048576) / sum;

    for (i = 0; i < dim_vec; i++)
    {

        /* Here minimum value of 13+base-vec_in[i] will be 5 */
        shift = (uint8_t)__USAT(13 + base - vec_in[i], 5);
        p_out[i] = (q7_t)__SSAD((output_base >> shift), 8);
    }
}
