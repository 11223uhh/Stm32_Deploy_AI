import os
import numpy as np
import d2lzh as d2l
from mxnet import gluon, init
from mxnet.gluon import loss as gloss, nn
import mxnet as mx
from mxnet.gluon import data as gdata, loss as gloss, model_zoo, nn
import os
from mxnet import autograd, gluon, init, nd
import time

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

#计算模型输入输出量并存储形状
shift_count=0

def get_net_cicun(X_shape,y_shape,i,count,f,BIAS_LSHIFT,OUT_RSHIFT):
    str_temp=str(i)
    global shift_count
    cneg_name=str_temp.split("(")[0]
    if(cneg_name=="Conv2D"):
        
        name=str(i.name_scope).split("<bound method Block.name_scope of")[1][1:]

        name=name.split("(")[0]+"_"+str(count)
        CONV_IM_DIM =X_shape[2]
        CONV_IM_CH =X_shape[1]
        
        CONV_OUT_DIM=y_shape[2]
        CONV_OUT_CH=y_shape[1]
        
        CONV_KER_DIM=str_temp.split("kernel_size=(")[1]
        CONV_KER_DIM=CONV_KER_DIM.split(",")[0]
        CONV_STRIDE=str_temp.split("stride=(")[1]
        CONV_STRIDE=CONV_STRIDE.split(",")[0]
        try:
            CONV_PADDING=str_temp.split("padding=(")[1]
            CONV_PADDING=CONV_PADDING.split(",")[0]
        except:
            CONV_PADDING=0
         
        temp=str("#define CONV_IM_DIM")+"_"+str(count)+" "+str(CONV_IM_DIM)+"\n"
        f.write(temp)
        temp=str("#define CONV_IM_CH")+"_"+str(count)+" "+str(CONV_IM_CH)+"\n"
        f.write(temp)
        temp=str("#define CONV_OUT_DIM")+"_"+str(count)+" "+str(CONV_OUT_DIM)+"\n"
        f.write(temp)
        temp=str("#define CONV_OUT_CH")+"_"+str(count)+" "+str(CONV_OUT_CH)+"\n"
        f.write(temp)
        temp=str("#define CONV_KER_DIM")+"_"+str(count)+" "+str(CONV_KER_DIM)+"\n"
        f.write(temp)
        temp=str("#define CONV_STRIDE")+"_"+str(count)+" "+str(CONV_STRIDE)+"\n"
        f.write(temp)
        temp=str("#define CONV_PADDING")+"_"+str(count)+" "+str(CONV_PADDING)+"\n"
        f.write(temp)
        
        str1=name+"_BIAS_LSHIFT"+str("_")+str(count)
        temp="#define %s"%str1+str(" ")+str(BIAS_LSHIFT[shift_count])+"\n"
        f.write(temp)
        str1=name+"_OUT_RSHIFT"+str("_")+str(count)
        temp="#define %s"%str1+str(" ")+str(OUT_RSHIFT[shift_count])+"\n"+"\n"
        f.write(temp)
        shift_count=shift_count+1
        
    if(cneg_name=="Dense"):
        name=str(i.name_scope).split("<bound method Block.name_scope of")[1][1:]

        name=name.split("(")[0]+"_"+str(count)
        try:
            IP1_DIM=X_shape[1]*X_shape[2]*X_shape[2]
        except:
            IP1_DIM=X_shape[1]
        temp=str("#define IP1_DIM")+"_"+str(count)+" "+str(IP1_DIM)+"\n"
        f.write(temp)
        
        IP1_OUT=y_shape[1]
        temp=str("#define IP1_OUT")+"_"+str(count)+" "+str(IP1_OUT)+"\n"
        f.write(temp)
        
        str1=name+"_BIAS_LSHIFT"+str("_")+str(count)
        temp="#define %s"%str1+str(" ")+str(BIAS_LSHIFT[shift_count])+"\n"
        f.write(temp)
        str1=name+"_OUT_RSHIFT"+str("_")+str(count)
        temp="#define %s"%str1+str(" ")+str(OUT_RSHIFT[shift_count])+"\n"+"\n"
        f.write(temp)
        shift_count=shift_count+1

    if(cneg_name=="MaxPool2D"):
        POOL1_KER_DIM=str_temp.split("size=(")[1]
        POOL1_KER_DIM= POOL1_KER_DIM.split(",")[0]
        POOL1_STRIDE=str_temp.split("stride=(")[1]
        POOL1_STRIDE=POOL1_STRIDE.split(",")[0]
        POOL1_PADDING=str_temp.split("padding=(")[1]
        POOL1_PADDING=POOL1_PADDING.split(",")[0]
        POOL1_OUT_DIM=y_shape[2]
        
        temp=str("#define POOL_OUT_DIM")+"_"+str(count)+" "+str(POOL1_OUT_DIM)+"\n"
        f.write(temp)
        temp=str("#define POOL_KER_DIM")+"_"+str(count)+" "+str(POOL1_KER_DIM)+"\n"
        f.write(temp)
        temp=str("#define POOL_STRIDE")+"_"+str(count)+" "+str(POOL1_STRIDE)+"\n"
        f.write(temp)
        temp=str("#define POOL_PADDING")+"_"+str(count)+" "+str(POOL1_PADDING)+"\n"
        f.write(temp)
        
        
#计算位移并存储位移
def get_net_shift(X,net,f,BIAS_LSHIFT,OUT_RSHIFT):
    count=0
    for layer in net:
        name=layer.name[0:4]
        output=layer(X)
        get_net_cicun(X.shape,output.shape,layer,count,f,BIAS_LSHIFT,OUT_RSHIFT)
        f.write("\n\n")

        X=output
        count=count+1



    
def liang_print(net,X,BIAS_LSHIFT,f):

    count=0
    name_count=0

    for layer in net:
        str_temp=str(layer)
        cneg_name=str_temp.split("(")[0]
        if(cneg_name=="Conv2D"):
            name=str(layer.name_scope).split("<bound method Block.name_scope of")[1][1:]

            name=name.split("(")[0]+"_"+str(name_count)
            weight=layer.weight.data()
            if(count>0):
                d1=weight.swapaxes(1,2)
                d2=d1.swapaxes(2,3)
                data=d2.reshape(1,-1)[0]
            else:
                data=weight.reshape(1,-1)[0]

            temp2 = ','.join(str(int(i.asnumpy())) for i in data)
            temp="#define %s"%(name+"_weight")+" {"+temp2+"}"+"\n\n"
            f.write(temp)

            bias=layer.bias.data().reshape(1,-1)[0]
            bias  =bias/(2**(BIAS_LSHIFT[count]))
            bias=nd.round(bias)
            temp2 = ','.join(str(int(i.asnumpy())) for i in bias)
            temp="#define %s"%(name+"_bias")+" {"+temp2+"}"+"\n\n"

            f.write(temp)
            name_count=name_count+1
            count=count+1
        if(cneg_name=="Dense"):
            name=str(layer.name_scope).split("<bound method Block.name_scope of")[1][1:]

            name=name.split("(")[0]+"_"+str(name_count)
            shape=[0,0,0,0]
            shape[0]=net[-1].bias.data().shape[0]
            shape[1:]=X.shape[1:]
            
            weight=layer.weight.data()
            weight=weight.reshape(shape)
            d1=weight.swapaxes(1,2)
            d2=d1.swapaxes(2,3)
            data=d2.reshape(1,-1)[0]
            temp2 = ','.join(str(int(i.asnumpy())) for i in data)
            temp="#define %s"%(name+"_weight")+" {"+temp2+"}"+"\n\n"
            f.write(temp)
            bias=layer.bias.data().reshape(1,-1)[0]
            bias  =bias/(2**(BIAS_LSHIFT[count]))
            bias=nd.round(bias)
            temp2 = ','.join(str(int(i.asnumpy())) for i in bias)
            temp="#define %s"%(name+"_bias")+" {"+temp2+"}"+"\n\n"
            f.write(temp)
            count=count+1
            name_count=name_count+1

        X = layer(X)



#采用最大量化
def INT8_net_pranms_Init(net,BIAS_LSHIFT):
    count=0
    for layer in net:
        try:
            w_data=layer.weight.data()
            b_data=layer.bias.data()
            
            w_data_INT8=INT8_liang(w_data)
            b_data_INT8=INT8_liang(b_data)
            b_data_INT8  =b_data_INT8*(2**(BIAS_LSHIFT[count]))
            #print(b_data_INT8)
            count=count+1
            layer.weight.set_data(w_data_INT8)
            layer.bias.  set_data(b_data_INT8)
        except:
            print("池化层无法量化")
    return net


def net_get_data(X,file,net,BIAS_LSHIFT,OUT_RSHIFT):
    
    f = open(file, 'a+')
    get_net_shift(X,net,f,BIAS_LSHIFT,OUT_RSHIFT)
    liang_print(net,X,BIAS_LSHIFT,f)
    name_count=0
    f.close()
def RAM_ROM_calculate(X,net):
    data_len=0
    count=0
    for layer in net:
        output=layer(X)
        try:
            w_data=layer.weight.data()
            w_data=w_data.reshape(1,-1)[0]
            b_data=layer.bias.data()
            
            b_data=b_data.reshape(1,-1)[0]
            #print(w_data.shape[0])
            data_len=data_len+w_data.shape[0]+b_data.shape[0]
            if(count==0):
                data_len2=(X.reshape(1,-1)[0]).shape[0]+(output.reshape(1,-1)[0]).shape[0]
            count=count+1

        except:
            c=3
           
                
        X=output
    ROM=data_len/1024
    ROM_str1="ROM所需 "+str(ROM)[0:5]+" KB"
    
    RAM=data_len2/1024+ROM
    RAM_str1="RAM所需 "+str(RAM)[0:5]+" KB"

    print(ROM_str1,RAM_str1)
###########################################################################用户自定义代码
net = nn.Sequential()
net.add(nn.Conv2D(channels=1, kernel_size=3, activation='relu'),
        nn.MaxPool2D(pool_size=2, strides=2),
        # Dense会默认将(批量大小, 通道, 高, 宽)形状的输入转换成
        # (批量大小, 通道 * 高 * 宽)形状的输入
        nn.Conv2D(channels=4, kernel_size=3, activation='relu'),
        nn.MaxPool2D(pool_size=2, strides=2),
        nn.Dense(8))
net.load_parameters("D:/traint__minst_as")
X=nd.zeros((1,1,100,100))
BIAS_LSHIFT=[6,5,5]
OUT_RSHIFT =[9,9,8]
net_int8=INT8_net_pranms_Init(net,BIAS_LSHIFT)
RAM_ROM_calculate(X,net)
net_get_data(X,"D://mnist_adin_5.txt",net_int8,BIAS_LSHIFT,OUT_RSHIFT)