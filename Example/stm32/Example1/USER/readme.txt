//bias 偏移和output偏移 右移为正 左移为负值
//arm_convolve_HWC_q7_basic(img_buffer2, CONV_IM_DIM_0, CONV_IM_CH_0, conv1_wt, CONV_OUT_CH_0, CONV_KER_DIM_0, CONV_PADDING_0,
                          CONV_STRIDE_0, conv1_bias, CONV_BIAS_LSHIFT_0, CONV_OUT_RSHIFT_0, img_buffer1, CONV_OUT_DIM_0,
                          (q15_t *) col_buffer, NULL);



卷积在输出到指定位置时，存放数据的顺序并非是顺序一个通道存完再存另外一个通道正常的，假如输出的数据格式是2个(2*2)  输出通道为2输出维度为2
多通道卷积结果是求和而非取平均值
则每次取通道一个值存 紧接着再取同一位置下另外一个通道的值存，接着更换位置

同样在参数赋值时给定的参数 W也不能是顺序的

W的矩阵形状 如  N x A x B x C  相当于有 N个   A*B*C的卷积块
则W的值是先按照卷积块的顺序一个接一个填充 ，对每一个卷积块按照通道顺序先填的(和传统我们想的不一样，所以他的输入仅仅只能用它的卷积函数输出的数据) 先放入第一个通道的第一个值，紧接着放入处于同样位置的第二个通道的第二个值，依此类推 ，通道到最后的，然后换位置再填充，这一个W块填完 再填另外一个

arm这些卷积函数有些Bug 比如 X 转为整数 与W转为整数 卷积的结果存在 一个q15中 但不知道为什么如果卷积的结果大于3万或者2点几万，程序结果就出问题了，卷积的结果
会比实际结果低且误差极大 极大影响后续结果 
偏移计算 
假设每个变量Q格式如下
X Q a.b    W Q c.d   b Q e.f   ouput Q m.n

OUT_RSHIFT_=b+d-n
BIAS_LSHIFT=b+d-f

BIAS_LSHIFT和OUT_RSHIFT 大于0意义不同 OUT_RSHIFT大于0右移 ，BIAS_LSHIFT大于0左移

BIAS_LSHIFT_    只能左移    否则模型出问题 可以等于0
OUT_RSHIFT_    只能右移即  否则模型出问题 可以等于0

BIAS_LSHIFT_  小于0  BIAS_LSHIFT_ 在计算中会直接等效为Bias =0
OUT_RSHIFT    小于0                  输出会直接变为0
对arm_convolve_HWC_q7_fast 
对arm_convolve_HWC_q7_basic  已经做了相关测试 确保以上描述正确
relu 最大池化层 有测试代码
方法为给定一个简单的输入 且各个层的参数也已知且较为简单 人工计算结果 与输出结果比对 

	如果 实际使用过程中模型输出与python 网络输出差值较大 一般是量化范围 考虑Int16或者量化算法
 