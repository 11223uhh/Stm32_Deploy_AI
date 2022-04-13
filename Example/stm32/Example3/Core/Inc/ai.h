#ifndef __ai_h
#define __ai_h
#include <stdint.h>
#include <stdio.h>

typedef int8_t q7_t;
typedef int16_t q15_t;
typedef int32_t q31_t;
typedef int64_t q63_t;
typedef float float32_t;
typedef double float64_t;
#define NN_ROUND(out_shift) ((0x1u << out_shift) >> 1)
#define __SSAT                            __ssat


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
                                     q7_t *bufferB);
void arm_relu_q7(q7_t *data, uint16_t size);
void arm_maxpool_q7_HWC(q7_t *Im_in,
                        const uint16_t dim_im_in,
                        const uint16_t ch_im_in,
                        const uint16_t dim_kernel,
                        const uint16_t padding,
                        const uint16_t stride,
                        const uint16_t dim_im_out,
                        q7_t *bufferA,
                        q7_t *Im_out);
void arm_avepool_q7_HWC(q7_t *Im_in,
                        const uint16_t dim_im_in,
                        const uint16_t ch_im_in,
                        const uint16_t dim_kernel,
                        const uint16_t padding,
                        const uint16_t stride,
                        const uint16_t dim_im_out,
                        q7_t *bufferA,
                        q7_t *Im_out);										
arm_status arm_fully_connected_q7(const q7_t *pV,
                                  const q7_t *pM,
                                  const uint16_t dim_vec,
                                  const uint16_t num_of_rows,
                                  const uint16_t bias_shift,
                                  const uint16_t out_shift,
                                  const q7_t *bias,
                                  q7_t *pOut,
                                  q15_t *vec_buffer);			

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
                                    q7_t *bufferB);					

void arm_softmax_q7(const q7_t *vec_in, const uint16_t dim_vec, q7_t *p_out);
																		
#endif
