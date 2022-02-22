import d2lzh as d2l
from mxnet import gluon, init
from mxnet.gluon import loss as gloss, nn
import mxnet as mx
from mxnet.gluon import data as gdata, loss as gloss, model_zoo, nn
import os
from mxnet import autograd, gluon, init, nd
import time
from mxnet.gluon import HybridBlock
from mxnet.image import  Augmenter
import random
import cv2
import numpy as np
import sys
from PIL import Image




def Q_liang(max_data,min_data):
    int_bits=0
    max_liang=max(abs(max_data),max(min_data))
    for i in range(8):
        if(max_liang<=2**i):
            int_bits=i
            break
    frac_bits=7-int_bits
    return int_bits,frac_bits              

def liang(data):
    b=data.reshape(1,-1)[0]
    min_wt = b.min()[0].asnumpy()
    max_wt = b.max() [0].asnumpy()
    int_bits,frac_bits = Q_liang(max_wt,min_wt)
    print("该层参数为Q%s.%s"%(int_bits,frac_bits))
    data_test=nd.round(data*(2**frac_bits))
    return data_test
    
    
def INT8_liang(data):
    data_INT=liang(data)      #数据量化             
    data_INT=data_INT.astype("int8") #量化 INT8必须
    data_INT=data_INT.astype("float32") #为了python计算
    return data_INT


net = nn.Sequential()
net.add(nn.Conv2D(channels=1, kernel_size=3, activation='relu'),
        nn.MaxPool2D(pool_size=2, strides=2),
        # Dense会默认将(批量大小, 通道, 高, 宽)形状的输入转换成
        # (批量大小, 通道 * 高 * 宽)形状的输入
        nn.Conv2D(channels=4, kernel_size=3, activation='relu'),
        nn.MaxPool2D(pool_size=2, strides=2),
        nn.Dense(8))


net.load_parameters("D:/traint__minst_as")
#采用最大量化

def INT_8_net_4_test_s(net,X,OUT_RSHIFT):
    global ouput1
    ouput_shift=0
    bias_shift=0
    X=X.astype("int8")
    X=X.astype("float32") #为了python计算
    count=0
    for layer in net:
        str_temp=str(layer)
        cneg_name=str_temp.split("(")[0]
        if(cneg_name=="Conv2D")or(cneg_name=="Dense"):
            ouput_shift=OUT_RSHIFT[count]
            ouput_shift=2**ouput_shift
            X=layer(X)
            #print(X.max(),layer)
            X=X/ouput_shift                                   #输出偏移
            X=nd.round(X)
            #print(X.max())
            X=X.astype("int8")
            if(count==1):
                ouput1=X
            X=X.astype("float32")
            count=count+1
        else:
            X=layer(X)
            X=X.astype("int8")
            X=X.astype("float32")
    return X
# X=Image.open("C:\\Users\\胡程畅\\Desktop\\test_picture\\0.jpg")
# X_array=nd.array(X)
# X_array=X_array/255
# X_array=nd.round(X_array*127).reshape((1,1,28,28))

# result=INT_8_net_4(net_int8,X_array)
# result,result.argmax(axis=1)


data_dir  ='D:\mnist_2'
transform_train = gdata.vision.transforms.Compose([
    # 随机对图像裁剪出面积为原图像面积0.08~1倍、且高和宽之比在3/4~4/3的图像，再放缩为高和
    # 宽均为224像素的新图像
    gdata.vision.transforms.Resize(120),
    gdata.vision.transforms.CenterCrop(100),

    # 随机加噪声
    gdata.vision.transforms.ToTensor()
    # 对图像的每个通道做标准化
   ])
batch_size=100
train_ds = gdata.vision.ImageFolderDataset(
         os.path.join(data_dir, 'train2'), flag=0)

train_iter = gdata.DataLoader(train_ds.transform_first(transform_train),
                              batch_size, shuffle=True, last_batch='keep')


BIAS_LSHIFT=[6,7,6]
OUT_RSHIFT =[9,9,8]

net_int8=INT8_net_pranms_Init(net,BIAS_LSHIFT)
def net_Int8_evaluate_accuracy(data_iter, ctx):
    acc_sum, n = 0.00, 0
    for X, y in data_iter:
        y = y.astype('float32')
        y = y.as_in_context(ctx)
        X=nd.round(X*127)
        outputs = INT_8_net_4_test_s(net_int8,X.as_in_context(ctx),OUT_RSHIFT)
        acc_sum += (outputs.argmax(axis=1) == y).sum().copyto(mx.cpu())
        n += y.size
        acc_sum.wait_to_read()
    return acc_sum.asscalar() / n