from PIL import Image
import numpy as np
import sys


dirpath=sys.argv[1]
file_path=dirpath[0:-4]
file_path=file_path+".txt"
img_PIL = Image.open(dirpath)#读取数据
img_PIL_array=np.array(img_PIL)



img_PIL_array=img_PIL_array.reshape(1,784)[0]


img_PIL_array=np.array(img_PIL_array).reshape(1,784)[0]

img_PIL_array=img_PIL_array/255
img_PIL_array=img_PIL_array*128
img_PIL_array=np.round(img_PIL_array)

np.savetxt(file_path,img_PIL_array,fmt="%d" ,delimiter=" ")