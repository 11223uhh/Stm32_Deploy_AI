**本项目基本上基于ARM CMISIS NN库，相当于CMISIS NN的一个应用,但对NN库进行了一定裁剪，扩充，解释，也可以单片机运行Opencv1.0。若有不足，敬请原谅。更多资料可查看ARM CMIS NN库**
## 特点
- 可以将Mxnet训练好的模型，量化之后，部署在单片机。
- 有仿真平台可以模拟实际运行数据，精确度，所需RAM和ROM。
- 可以使用一些Opencv 1.0的简单函数,如图片缩放,灰度化,边缘检测,霍夫变换,腐蚀,膨胀等.
- 可以查看每一层的输出。
- 目前仅支持VGG块，不支持Resnet，nin，googlenet，mobbilenet，未来可以更新，敬请期待。
- 使用CMISIS NN库加快单片机运行模型速度。
- 带有例程方便理解。
##
## python环境要求
- mxnet-cu100    =1.5.0 
- d2lzh          =1.0.0
- opencv-python =4.5.4.60
- Pillow         =   8.4.0  

**备注**：并非在其他版本,不能使用,只是在此环境下成功运行了,其他神经网络框架如Keras也可以实现，有点麻烦。
##   

## STM32要求
- STM32F407ZGT6,其他芯片亦可,但仅在此芯片进行了测试.
- TFT屏幕
- ARM仿真下载器,有其他下载器亦可.  

**备注**：如果嫌麻烦，可以在淘宝购买STM32F4mini探索版开发板(带屏幕,f407zgt6)，其他芯片和开发版也可以简单移植,本项目有STM32例程和arduino(不支持opencv)例程。。
##



## 例程
>STM32例子:
>>Example1 基于ARM CMISI NN 库，识别一张给定的mnist图片，图片已经写入代码。  
>>Example2 基于Tenorflow lite 库，拟合正弦曲线，显示在屏幕。   

> Arduino UNO R3例子:  
>> 基于ARM CMISI NN 库，识别一张给定的mnist图片，可以通过串口发送图片识别。  
  
> opencv 例子:
>>一些opencv的函数使用，例子


##

## 文件介绍:  
- python  模型量化，仿真
- Example 相关例子
## 
## 使用方法(仅仅介绍基于ARM CMISI NN)
参考  get_start.md
##