
#include "ai.h"


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
    int conv_out;
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
    int conv_out;
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


  
    /* Run the following code as reference implementation for Cortex-M0 and Cortex-M3 */
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
    int output_base = (1 << 20) / sum;

    for (i = 0; i < dim_vec; i++)
    {

        /* Here minimum value of 13+base-vec_in[i] will be 5 */
        shift = (uint8_t)__USAT(13 + base - vec_in[i], 5);
        p_out[i] = (q7_t)__SSAD((output_base >> shift), 8);
    }
}
