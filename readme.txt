

本项目基本上基于ARM CMISIS NN库，相当于CMISIS NN的一个应用,但对NN库进行了一定裁剪和扩充，也可以单片机运行Opencv1.0。若有不足，敬请原谅。更多资料可查看ARM CMIS NN库
python环境要求:
  1. mxnet-cu100          1.5.0
  2. d2lzh                1.0.0
  3. opencv-python        4.5.4.60
  4. Pillow               8.4.0
  备注:并非在其他版本,不能使用,只是在此环境下成功运行了,其他神经网络框架如Keras也可以实现，有点麻烦。
 
STM32 要求:
  1. STM32F407ZGT6,其他芯片亦可,但仅在此芯片进行了测试.
  2. TFT屏幕
  3. ARM仿真下载器,有其他下载器亦可.
  备注:如果嫌麻烦，可以在淘宝购买STM32F4mini探索版开发板，其他芯片和开发版也可以简单移植,本项目有STM32例程和arduino(不支持opencv)例程。
 
 特点:
  1 . 可以将Mxnet训练好的模型，量化之后，部署在单片机。
  2 . 有仿真平台可以模拟实际运行数据，精确度，所需RAM和ROM。
  3 . 可以使用一些Opencv 1.0的简单函数,如图片缩放,灰度化,边缘检测,霍夫变换,腐蚀,膨胀等.
  4 . 可以查看每一层的输出。
  5 . 目前仅支持VGG块，不支持Resnet，nin，googlenet，mobbilenet，未来可以更新，敬请期待。
  6 . 使用CMISIS NN库加快单片机运行模型速度。
  7.  带有例程方便理解。
例子:
 STM32例子:
  	基于ARM CMISI NN 库，识别一张给定的mnist图片，图片已经写入代码。
 Arduino例子:
 	基于ARM CMISI NN 库，识别一张给定的mnist图片，可以通过串口发送图片识别。
 opencv 例子:
 	
使用本项目方法:(仅介绍基于ARM CMISI NN),若嫌麻烦，可以直接下载项目例子，配合理解。
  1 .模型训练完毕，使用net.save_parameters("file_name") 
     net       为训练的模型
     file_name 任意即可，没有后缀名要求
  2. 模型量化，类似下方代码。全部代码在量化并存储模型4.0和测试.ipynb中，根据需要进行修改，模型量化采用手动最大量化。
      net = nn.Sequential()
      ///////////////////////////////////模型结构搭建
      net.add(nn.Conv2D(channels=1, kernel_size=3, activation='relu'),
              nn.MaxPool2D(pool_size=2, strides=2),
              nn.Conv2D(channels=4, kernel_size=3, activation='relu'),
              nn.MaxPool2D(pool_size=2, strides=2),
              nn.Dense(8))
      net.load_parameters("file_name")
      /////////////////////////////////////模型输入假设，这个只是为了确定一些量化参数 ,四个参数依次为 数量,通道数，高度和宽度。数量必须为1 
      X=nd.zeros((1,1,100,100))
      ////////////////////////////////////BIAS_LSHIFT OUT_RSHIFT为网络每层量化参数(池化层无此参数)，需要手动调参。方法在另外一篇博客
      BIAS_LSHIFT=[6,5,5]
      OUT_RSHIFT =[9,9,8]
      net_int8=INT8_net_pranms_Init(net,BIAS_LSHIFT)//生成量化模型
      RAM_ROM_calculate(X,net)                      //获取所需RAM和ROM大小
      net_get_data(X,"h_file",net_int8,BIAS_LSHIFT,OUT_RSHIFT)//h_file 生成.h文件路径

  3.模型部署
       1. 将生成的.h文件和ai.c，ai.h添加到项目中.
       2. 添加以下代码 根据自己模型层数，添加。
         const q7_t conv1_wt[CONV_IM_CH_0 * CONV_KER_DIM_0 * CONV_KER_DIM_0 * CONV_OUT_CH_0] = Conv2D_0_weight;
         const q7_t conv1_bias[CONV_OUT_CH_0] = Conv2D_0bias;
         q7_t ip1_wt[256 * 10] = Dense_2_weight;
         q7_t ip1_bias[IP1_OUT_4] = Dense_2bias;
         备注:以下仅仅是一层卷积，一层全连接的例子，变量均在生成的.h文件中。
        3.添加缓冲区 col_buffer缓存大小。具体值可以参考以下博客。
            q7_t      col_buffer[256*120];//存储的是卷积层的输出
        4.添加输入，输出
          q7_t      output_data[IP1_OUT_4];//IP1_OUT_4 模型识别类数
          uint8_t   image_data[CONV_IM_CH_0 * CONV_IM_DIM_0 * CONV_IM_DIM_0] = { };
                    image_data模型输入数据数组。
          q7_t     *img_buffer1 = scratch_buffer;
	        q7_t     *img_buffer2 = img_buffer1 + CONV_OUT_CH_0 * CONV_OUT_DIM_0 * CONV_OUT_DIM_0;//+ CONV1_OUT_CH * CONV1_OUT_DIM * CONV1_OUT_DIM为卷积运算完存数据做的操作
          for (int i=0;i<28*28*1; i++) 
             img_buffer2[i] =(q7_t)image_data[i];//往数组存数据，根据实际情况，添加数据。需要将三维数组reshape一维，添加。这只是一个例子
             // 28 *28 *1为输入数据维度。
         5.添加以下代码，模型开始迭代。需要根据自己情况进行修改，以下只是一层relu卷积，一层池化，一层全连接。变量均在生成的.h文件中。
       arm_convolve_HWC_q7_basic(img_buffer2, CONV_IM_DIM_0, CONV_IM_CH_0, conv1_wt, CONV_OUT_CH_0, CONV_KER_DIM_0, CONV_PADDING_0,CONV_STRIDE_0, conv1_bias, 
CONV_BIAS_LSHIFT_0, CONV_OUT_RSHIFT_0, img_buffer1, CONV_OUT_DIM_0,(q15_t *) col_buffer, NULL);	//基础卷积层
       arm_relu_q7(img_buffer1, CONV_OUT_DIM_0 * CONV_OUT_DIM_0 * CONV_OUT_CH_0);///relu激活
       arm_maxpool_q7_HWC(img_buffer1, CONV_OUT_DIM_0, CONV_OUT_CH_0, POOL_KER_DIM_1,
                       POOL_PADDING_1, POOL_STRIDE_1, POOL_OUT_DIM_1, NULL, img_buffer2);//池化层
       
      arm_fully_connected_q7(img_buffer2, ip1_wt, IP1_DIM_4, IP1_OUT_4, Dense_BIAS_LSHIFT_4, Dense_OUT_RSHIFT_4, ip1_bias,
                                 output_data, (q15_t *) img_buffer1);                
  4. 模型仿真,类似下方代码。全部代码在CMSIS 仿真3.0.ipynb中，根据需要进行修改
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
Opencv 在STM32使用方法:
    1.将项目中opencv文件夹添入你项目中。
    2.根据项目所带KEIL5例子，依次将Groups opencv 中.cpp文件添加到你项目中。
    3.添加bu.c,malloc.c到你项目中。
    备注:由于Stm32无操作系统，故图片输入采用一种特殊方法，先创建空白图片然后填写。以下为例子.
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
     4.开始使用。相关函数介绍及文件位置，可自行搜索Opencv1.0 API介绍。
