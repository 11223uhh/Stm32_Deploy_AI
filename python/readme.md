## 文件介绍
>CMSIS 仿真.py
>>模型仿真平台，可以在电脑模拟单片机运行神经网络情况，有一些API可供查看，该文件会先自动按照量化方法，量化模型，然后再进行模型运行。  
**备注:    模型量化最重要是模型偏移如　<font color='red'> BIAS_LSHIFT OUT_RSHIFT </font>，这几乎决定了模型量化准确率，模型参数W和b量化很简单，没有太多问题和选择空间。**  
  
>量化并存储模型.py
>>训练，仿真完模型，调用此文件即可，生成模型.h文件，可供单片机或其他嵌入式设备使用。详细使用，查看函数
