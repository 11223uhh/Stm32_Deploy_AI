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
import gluoncv

def Q_liang(num):
    set_probability=1
    
    temp=num.copy()
    temp=temp.asnumpy()
    temp=np.absolute(temp)
    for i in range(8):
        probability=np.sum(temp<=2**i)/(temp.reshape(1,-1).shape[1])
        if(probability>=set_probability):
            break
    int_bits=i
    frac_bits=7-i
    return int_bits,frac_bits
def Q_liang_2(num,set_probability):
    
    temp=num.copy()
    temp=temp.asnumpy()
    temp=np.absolute(temp)
    for i in range(8):
        probability=np.sum(temp<=2**i)/(temp.reshape(1,-1).shape[1])
        if(probability>=set_probability):
            break
    int_bits=i
    frac_bits=7-i
    return int_bits,frac_bits


def liang(data):
    b=data.reshape(1,-1)[0]
    int_bits,frac_bits = Q_liang(b)
    print("该层参数为Q%s.%s"%(int_bits,frac_bits))
    data_test=nd.round(data*(2**frac_bits))
    return data_test
    
    
def INT8_liang(data):
    data_INT=liang(data)      #数据量化             
    data_INT=data_INT.astype("int8") #量化 INT8必须
    data_INT=data_INT.astype("float32") #为了python计算
    return data_INT



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
            print("")
    return net
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




def Get_net_shift(X,net,ctx,debug,set_probability):
    """
    该函数用于生成量化参数，BIAS_LSHIFT,OUT_RSHIFT，极其重要。

    param X   
        data type  :ndarray
        meaning    :测试数据,采用真实样本，数组shape也要与模型训练一致，只能使用一个样本。
    param net : 
        data type  :Sequential 
        meaning    :未量化的模型
    param ctx: 
        data type  :Context 
        meaning    :运行平台，GPU还是CPU eg mx.cpu(),mx.gpu()
    param debug: 
        data type  :num 
        meaning    :是否打印，相关调试信息。
    param set_probability:  
        data type  :num 
        meaning    :在生成BIAS_LSHIFT，OUT_RSHIFT考虑样本范围，set_probability越大量化考虑的样本越多，但也可能由于异常数据影响，量化参数，极其重要。
       
    """    
    count=0
    BIAS_LSHIFT=[]
    OUT_RSHIFT=[]
    X = X.as_in_context(ctx)
    X=X.astype('float32')

    for layer in net:
        name=layer.name[0:4]
        output=layer(X)
        if(name=="conv")or(name=="dens"):
            output_int_bits,output_frac_bits=Q_liang_2(output,set_probability)

            X_temp=X.reshape(1,-1)
            X_int_bits,X_frac_bits=Q_liang_2(X_temp,set_probability)

            W=layer.weight.data()
            W_int_bits,W_frac_bits=Q_liang_2(W,set_probability)

            b=layer.bias.data()    
            b_int_bits,b_frac_bits=Q_liang_2(b,set_probability)
            
            bias_shift=  X_frac_bits+W_frac_bits-b_frac_bits
            output_shift=X_frac_bits+W_frac_bits-output_frac_bits
            if(debug):
                print("该层网络量化参数  XQ%d.%d WQ%d.%d BQ%d.%d output Q%d.%d"%(X_int_bits,X_frac_bits,W_int_bits,W_frac_bits,b_int_bits,b_frac_bits,output_int_bits,output_frac_bits))
                print("偏移值bias_shift= %d,output_shift=%d\n"%(bias_shift,output_shift))
            BIAS_LSHIFT.append(bias_shift)
            OUT_RSHIFT.append(output_shift)
        X=output
        count=count+1
    return BIAS_LSHIFT,OUT_RSHIFT

def net_Int8_evaluate_accuracy(data_iter,net,ctx,BIAS_LSHIFT,OUT_RSHIFT):
    net_int8=INT8_net_pranms_Init(net,BIAS_LSHIFT)
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



def find_max_label(list_test,label):
    # list_test Bias_shi和output_shift 出现的次数序列。里面每一个元素代表不同偏差序列的次数
    # label  返回次数排名第几
    # label=1 函数返回出现最多的次数的索引
    # label=2 函数返回出现第二多的次数的索引
    oringht_list=list()
    oringht_list=list_test.copy()
    if(label==1):
        max_ele_ment=max(list_test)
        return list_test.index(max_ele_ment)
    for i in range(label-1):
        max_ele_ment=max(list_test)
        list_test.remove(max_ele_ment)
    max_ele_ment=max(list_test)
    return (oringht_list.index(max_ele_ment))

def find_good(list_input,sequence):
    # list_input 测试数据集形成的偏差序列
    # sequence  排名
    #根据从每一个图片生成的偏差所组成的偏差序列，返回出现次数第sequence多的元素，元素是bias_shift和output_shift
    # 
    len_gth=len(list_input)
    count_dict =list()
    count_save_data_list =list()

    for i in range(len_gth):
        if (list_input[i]) in count_save_data_list:
            label=count_save_data_list.index(list_input[i])
            #print(list_input[i],count_dict)
            count_dict[label] += 1
        else:
            count_dict.insert(i,1) 
            count_save_data_list.insert(i,list_input[i]) 
    
    #print(count_dict)
    #print(count_save_data_list)
    array=nd.array(count_dict)
    
    label=find_max_label(count_dict,sequence)
    result=count_save_data_list[int(label)]
    result_list=list(result)
    half_len=int(len(result_list)/2)
    BIAS_LSHIFT=result_list[0:half_len]
    OUT_RSHIFT=result_list[half_len:]
    return BIAS_LSHIFT,OUT_RSHIFT

###  count 采用出现次数前几的偏差 count=1 则只会拿出现最多的偏差作为模型量化，count=2 会拿出现次数前2的所有偏差进行测试
###  test_iter 测试数据集     
###  valid_ds  测试数据集 
##  net_quan_load  BN_dep  函数
## file     模型保存路径
## range_    采用数据集多少张图片进行测试
##debug     是否打印log
## set_probability 设置一个可能性
def find_good_acc(count,test_iter,valid_ds,net_quan_load,file,ctx,range_,debug,set_probability):
    ###################################################################################################
    max_BIAS_LSHIFT=list()
    max_OUT_RSHIFT=list()
    acc=0
    max_acc=0
    for i in range(count):
        net=net_quan_load(file)
        BIAS_LSHIFT,OUT_RSHIFT=find_lshift(valid_ds,range_,net,ctx,debug,set_probability,sequence=i+1)
        acc=net_Int8_evaluate_accuracy(test_iter,net,ctx,BIAS_LSHIFT,OUT_RSHIFT)
        if(acc>max_acc):
            max_acc=acc
            max_BIAS_LSHIFT=BIAS_LSHIFT
            max_OUT_RSHIFT=OUT_RSHIFT
        print(acc,BIAS_LSHIFT,OUT_RSHIFT)
    print(max_acc,max_BIAS_LSHIFT,max_OUT_RSHIFT)

def find_lshift(valid_ds,num,net,ctx,debug,set_probability,sequence):

    Shift_list=list()

    for i in range(num):
        input_data=(valid_ds[i][0].reshape(1,1,28,28))
        input_data= input_data.astype('float32')
        input_data=input_data/255
        BIAS_LSHIFT,OUT_RSHIFT=Get_net_shift(input_data,net,ctx,debug,set_probability)
        #print(BIAS_LSHIFT,OUT_RSHIFT)
        Shift_list.append((BIAS_LSHIFT+OUT_RSHIFT))

    BIAS_LSHIFT,OUT_RSHIFT=find_good(Shift_list,sequence)
    return BIAS_LSHIFT,OUT_RSHIFT

#计算模型输入输出量并存储形状
shift_count=0

def net_save_structure(X_shape,y_shape,i,count,f,BIAS_LSHIFT,OUT_RSHIFT):
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
        print(BIAS_LSHIFT,shift_count)
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
def net_save_model_structure(X,net,f,BIAS_LSHIFT,OUT_RSHIFT):
    global shift_count
    count=0
    for layer in net:
        name=layer.name[0:4]
        output=layer(X)
        net_save_structure(X.shape,output.shape,layer,count,f,BIAS_LSHIFT,OUT_RSHIFT)
        f.write("\n\n")

        X=output
        count=count+1
    shift_count=0

###   根据发现，BN层与1*1的可分离卷积层作用一致。
###   该函数可以把原本的带BN层的神经网络的参数加载到带有1*1的可分离卷积层神经网络
###   net 带有BN层的神经网络   未量化
###   net_quan 带有1*1的可分离卷积   未量化
def net_data_BN_to_Depconv(net,net_quan,debug):
    count=0
    for layer in net_quan:
        str_temp=str(layer)
        if(str_temp.find('Conv2D')!=-1)or(str_temp.find('Dense')!=-1):
            if(str_temp.find('groups')!=-1):
                str_net=str(net[count])
                if(str_net.find('BatchNorm')!=-1):
                    if(debug==1):
                        print("%d层为Bn层"%count)
                    mean=net[count].running_mean.data()
                    var= net[count].running_var.data()
                    gamma =net[count].gamma.data()
                    beta= net[count].beta.data()
                    
                    shape1=layer.weight.data().shape
                    shape2=layer.bias.data().shape
                    
                    w=gamma/(nd.sqrt(var + 1e-5))
                    b=beta-(gamma*mean)/(nd.sqrt(var + 1e-5))

                    w=w.reshape(shape=shape1)
                    b=b.reshape(shape=shape2)
                    
                    layer.weight.set_data(w)
                    layer.bias.  set_data(b)          
                    
                else:
                    layer.weight.set_data(net[count].weight.data())
                    layer.bias.  set_data(net[count].bias.data())
                    if(debug==1):
                        print("%d层为可分离卷积层"%count)
            else:
                if(debug==1):
                    print("%d普通卷积或者全连接"%count)
                layer.weight.set_data(net[count].weight.data())
                layer.bias.  set_data(net[count].bias.data())
        else:
            if(debug==1):
                print("%d池化层"%count)
        count=count+1
    return net_quan
    
def net_save_model_data(net,X,BIAS_LSHIFT,f):

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





def net_save_quant_model(X,file,net,BIAS_LSHIFT,OUT_RSHIFT):
    """
    该函数用于保存量化后的模型，并生成.h文件。

    param X   
        data type  :ndarray
        meaning    :测试数据,只需要确定数组shape正确即可，对数据无要求  
    param file : 
        data type  :Str 
        meaning    :模型存储位置 eg: D://test_model.h        
    param net : 
        data type  :Sequential 
        meaning    :量化后的模型
    param BIAS_LSHIFT: 
        data type  :list 
        meaning    :模型每一层的Bias_lshift偏移
    param OUT_RSHIFT: 
        data type  :list 
        meaning    :模型每一层的OUT_lshift偏移
    """
    f = open(file, 'a+')
    net_save_model_structure(X,net,f,BIAS_LSHIFT,OUT_RSHIFT)
    net_save_model_data(net,X,BIAS_LSHIFT,f)
    name_count=0
    f.close()
    
    
def RAM_ROM_calculate(X,net):
    """
    该函数用于计算，并打印出模型所需ROM和RAM大小
    param X: 
        data type  :ndarray     
        meaning    :测试数据,只需要确定数组shape正确即可，对数据无要求
    param net : 
        data type  :Sequential 
        meaning    :模型(不分量化前后)

    """
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
    
    