#一、pickle
pickle这里代指pickle模块与cpickle模块，pickle模块将python对象按字节系列化存储到文件中，并可以从文件中还原python对象。


1. pickle模块与cpickle模块：
cPickle模块是pickle模块的C语言版，cPickle模块甚至可以比pickle模块快1000倍，但是cPickle模块不支持Pickler()和Unpickler类，因为它们在cPickle里面是函数而非类。大多数程序都不需要Pickler()和Unpickler类，因此推荐使用cPickle.

2. pickle与marshal异同：
    * pickle不会重复序列化同一对象，换言之，pickle可以跟踪已经序列化的对象，一旦后面再次引用到该对象，pickle不会再对其进行序列化，而marshal模块没有实现该功能。
    * marshal 不能序列化自定义类，而pickle可以，只要类定义和要存储的对象在同一模块中（同一文件）。
    * marshal 不保证对不同版本的python兼容，而pickle保证。
   
# pickle 模块支持的对象
    * `None`,`True`和`False`
    * 整型，长整型，浮点型，复数；
    * 标准字符串和unicode字符串；
    * 列表、元组、集合和字典（其中内容必须是可pickle的）；
    * 定义在模块顶级层的函数（全局函数）；
    * 定义在模块顶级层的内建函数（全局内建函数）；
    * 定义在模块顶级层的类；
    * 最后一个本人翻译的不好，直接给英文原文：instances of such classes whose `__dict__` or the result of calling `__getstate__()` is picklable.
    

    
    
    
    
## 四个主要函数
### 读写文件
    1. 写入文件：pickle.dump(obj, file[, protocol])
    2. 读取文件：obj = pickle.load(file)
    
### 读写内存
    1. 编码：pickle.dumps(obj[, protocol])
    2. 解码：obj = pickle.loads(string)
    
## 例子
```
from scipy import misc
import matplotlib.pyplot as plt
import pickle

img = misc.imread("/home/lile/gallery02.jpg")

# 读写文件
output = open('/home/lile/Desktop/pick.dat','wb')
pickle.dump(img,output,protocol = pickle.HIGHEST_PROTOCOL)
output.close()

input = open('/home/lile/Desktop/pick.dat','rb')
im = pickle.load(input)
plt.imshow(im)
print(type(im),im.shape)
input.close()

# 读写内存
s = pickle.dumps(img)
print(type(s))
ss = pickle.loads(s)
print(type(ss))
plt.imshow(ss)
plt.axis('off')


```
