## 开始使用

### 模型训练完毕
    使用net.save_parameters("file_name") 保存模型
    net         为训练的模型
    file_name   任意即可，没有后缀名要求
###

### 模型量化
    net = nn.Sequential()
    ///////////////////////////////////模型结构搭建
    net.add(nn.Conv2D(channels=1, kernel_size=3, activation='relu'),
              nn.MaxPool2D(pool_size=2, strides=2),
              nn.Conv2D(channels=4, kernel_size=3, activation='relu'),
              nn.MaxPool2D(pool_size=2, strides=2),
              nn.Dense(8))
    net.load_parameters("file_name")
    /////////////////////////////////////模型输入假设，这个只是为了确定一些化参数 ,四个参数依次为 数量,通道数，高度和宽度。数量必须为1 
    X=nd.zeros((1,1,100,100))
    ////////////////////////////////////BIAS_LSHIFT OUT_RSHIFT为网络每层量化参数(池化层无此参数)，需要手动调参。方法在另外一篇博客
    BIAS_LSHIFT=[6,5,5]
    OUT_RSHIFT =[9,9,8]
    net_int8=INT8_net_pranms_Init(net,BIAS_LSHIFT)//生成量化模型
    RAM_ROM_calculate(X,net)                      //获取所需RAM和ROM大小
    net_get_data(X,"h_file",net_int8,BIAS_LSHIFT,OUT_RSHIFT)//h_file 生成.h文件路径
**备注:** 以上仅为示例，根据需要进行修改，模型量化采用手动最大量化。全部代码在量化并存储模型.ipynb中。量化参数手动设置，参考**量化.md.**
###

### 模型部署
    1 将生成的.h文件和ai.c，ai.h添加到项目中.
    2 添加以下代码 根据自己模型层数，添加,以下仅为示例。
```c
const q7_t conv1_wt[CONV_IM_CH_0 * CONV_KER_DIM_0 * CONV_KER_DIM_0 * CONV_OUT_CH_0] = Conv2D_0_weight;  
const q7_t conv1_bias[CONV_OUT_CH_0] = Conv2D_0bias;  
q7_t ip1_wt[256 * 10] = Dense_2_weight;  
q7_t ip1_bias[IP1_OUT_4] = Dense_2bias;  
```
     3 添加缓冲区 col_buffer缓存大小。具体值可以参考以下博客。https://zhuanlan.zhihu.com/p/95374816
```c
    q7_t      col_buffer[256*120];//存储的是卷积层的输出
```
     4 添加输入，输出
```c
    q7_t      output_data[IP1_OUT_4];//IP1_OUT_4 模型识别类数
    uint8_t   image_data[CONV_IM_CH_0 * CONV_IM_DIM_0 * CONV_IM_DIM_0] = { };//image_data模型输入数据数组。
    q7_t     *img_buffer1 = scratch_buffer;
    q7_t     *img_buffer2 = img_buffer1 + CONV_OUT_CH_0 * CONV_OUT_DIM_0 * CONV_OUT_DIM_0;//+ CONV1_OUT_CH * CONV1_OUT_DIM * CONV1_OUT_DIM为卷积运算完存数据做的操作 

 **备注:**  图片在进行卷积和其他操作时都是在同一缓存区，进行的。一般是从img_buffer1拿数据，然后操作写入img_buffer2，或者相反。img_buffer1和img_buffer2都是在同一数组，只是位置不同。所以二者最好间隔远一些，否则会出现问题。比如y=x*w+b.如果img_buffer1和img_buffer2间隔太近，有可能输出的y会覆盖x,导致卷积错误。 CONV1_OUT_CH * CONV1_OUT_DIM * CONV1_OUT_DIM这个绝对不能直接使用，需要自己计算，判断使用img_buffer1所需的最大空间，假如空间为W_K则
 img_buffer2=img_buffer1+w_K



    for (int i=0;i<28*28*1; i++) 
        img_buffer2[i] =(q7_t)image_data[i];//往数组存数据，根据实际情况，添加数据。需要将三维数组reshape一维，添加。这只是一个例子
```
     5 添加以下代码，模型开始迭代。需要根据自己情况进行修改，以下只是一层relu卷积，一层池化，一层全连接。变量均在生成的.h文件中。
```c
    arm_convolve_HWC_q7_basic(img_buffer2, CONV_IM_DIM_0, CONV_IM_CH_0, conv1_wt, CONV_OUT_CH_0, CONV_KER_DIM_0, CONV_PADDING_0,CONV_STRIDE_0, conv1_bias, 
CONV_BIAS_LSHIFT_0, CONV_OUT_RSHIFT_0, img_buffer1, CONV_OUT_DIM_0,(q15_t *) col_buffer, NULL);	//基础卷积层

    arm_relu_q7(img_buffer1, CONV_OUT_DIM_0 * CONV_OUT_DIM_0 * CONV_OUT_CH_0);///relu激活

    arm_maxpool_q7_HWC(img_buffer1, CONV_OUT_DIM_0, CONV_OUT_CH_0, POOL_KER_DIM_1,
                       POOL_PADDING_1, POOL_STRIDE_1, POOL_OUT_DIM_1, NULL, img_buffer2);//池化层
       
    arm_fully_connected_q7(img_buffer2, ip1_wt, IP1_DIM_4, IP1_OUT_4, Dense_BIAS_LSHIFT_4, Dense_OUT_RSHIFT_4, ip1_bias,
                                 output_data, (q15_t *) img_buffer1);             
```     
### 模型仿真
```python 
    net = nn.Sequential()
        ///////////////////////////////////模型结构搭建
    net.add(nn.Conv2D(channels=1, kernel_size=3, activation='relu'),
                nn.MaxPool2D(pool_size=2, strides=2),
                nn.Conv2D(channels=4, kernel_size=3, activation='relu'),
                nn.MaxPool2D(pool_size=2, strides=2),
                nn.Dense(8))
    net.load_parameters("file_name")
    BIAS_LSHIFT=[6,5,5]
    OUT_RSHIFT =[9,9,8]
    net_int8=INT8_net_pranms_Init(net,BIAS_LSHIFT)//生成量化模型 BIAS_LSHIFT 卷积层Bias 偏移
        ///////////////////////////////////////////////////////////以下是一些API
    net_Int8_evaluate_accuracy(data_iter, ctx): 
            仿真测试，输出测试集准确率
            data_iter模型测试集，ctx模型训练平台是GPU还是CPU
    INT_8_net_4_test_s(net,X,OUT_RSHIFT):
            仿真运行模型 
            net量化模型
            X  测试数据，numpy数组 维度依次为数量,通道数，高度和宽度
            OUT_RSHIFT 输出偏移       
```
**备注:** 以上仅为示例，根据需要进行修改,全部代码在CMSIS 仿真.ipynb中.

### opencv移植
  参考Example中opencv文件夹里的readme.md
