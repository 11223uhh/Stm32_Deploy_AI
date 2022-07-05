**本项目为本科毕业设计作品，为智能分类垃圾桶，能自动识别40种物品并进行垃圾分类**
## python环境要求
- albumentations         =1.1.0
- h5py                   =2.10.0
- Keras-Applications     = 1.0.8
- opencv-python           =4.5.5.64
- Pillow                  =9.1.0
- tensorflow-gpu          =2.4.0
## c++环境要求
- esp32 ov2640驱动包(esp32-camera)
- tensorflow lite mirco包(tfmirco)
## 硬件要求
- ESP32CAM模组
- 二相四线步进电机
- 步进电机驱动模块(型号忘记了)
- 180度舵机
- 电池
## 其他要求
- cuda 11.0
- cudnn 忘记了
- cuda和显卡版本见https://docs.nvidia.com/cuda/cuda-toolkit-release-notes/index.html
## 文件介绍
* main.cpp  
  >主文件 模型的加载，图像传感器和电机的初始化，模型的载入，识别，电机控制  
* model.cc
  >模型文件  
  由xxd -i converted_model.tflite > model_data.cc生成
* pwm_motor.c
  >舵机pwm初始化
* gpio_motor.c
  >步进电机初始化
* componets
  >esp32摄像头驱动，和tensorflow lite mirco包
* partitions.csv 
  >分区表
