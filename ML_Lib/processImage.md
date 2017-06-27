[使用Numpy和Scipy处理图像](http://www.open-open.com/lib/view/open1417942286667.html)
[matplotlib和PIL读取图像](http://www.cnblogs.com/yinxiangnan-charles/p/5928689.html)
在 python 中除了用 opencv，也可以用 matplotlib 和 PIL 这两个库操作图片。本人偏爱 matpoltlib，因为它的语法更像 matlab。

# 一、读写图像
## 1. matplotlib库方法
```
import matplotlib.pyplot as plt # plt 用于显示图片
import matplotlib.image as mpimg # mpimg 用于读取图片

# type(lena) 为numpy.ndarray
lena = mpimg.imread('lena.png') # 读取和代码处于同一目录下的 lena.png

plt.imshow(lena) # 显示图片
plt.savefig('lena_new_sz.png') # 保存图片
plt.axis('off') # 不显示坐标轴
plt.show()
```

## 2. scipy库方法
 ```
from scipy import misc

# type(lena) 为numpy.ndarray
img = misc.imread('lena.jpg')
misc.imsave('lena.jpg',img)

 ```
 
## 3. PIL库方法
 ```
 from PIL import Image
 
# type(im) 不是 numpy.ndarray，而是 PIL.JpegImagePlugin.JpegImageFile
im = Image.open('lena.png')

# 显示图像
im.show()

 ```
 
# 二、批量读取图片
```
from glob import glob

# 得到的三图片名字的list
filelist = glob('random*.png')

```
 
 
# 二、显示图像

numpy.ndarray 类型图像显示方法有两个库：pylab 和 matplotlib.pyplot， 但是其实两个库都属于matplotlib，执行的也是相同的代码，pylab更侧重于交互（即ipython）中使用，一般编程用pyplot就可以
## 1. pylab方法
```
import pylab as pl

pl.imshow(img)
```

## 2. matplotlib.pyplot 方法
```
import matplotlib.pyplot as plt

plt.imshow(img)

```

# 将 PIL Image 图片转换为 numpy 数组
```
im_array = np.array(im)
# 也可以用 np.asarray(im) 区别是 np.array() 是深拷贝，np.asarray() 是浅拷贝
```



