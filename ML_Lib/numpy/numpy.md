# 零、 python思维
* In the Python world, the number of dimensions is referred to as rank.

# 一、numpy
1. numpy.ndarray与python中array.arrray的区别：
    *array.arrray只能处理一维数据；

2. numpy.ndarray数据内存分布：
    plane分布
    
# array 创建
1. 基本方法：
    * 使用标准python的list和tuple创建（拷贝创建）：
    ```
    x = [2,3,4]
    a = np.array(x，dtype = np.int64)
    ```
    array transforms sequences of sequences into two-dimensional arrays, sequences of sequences of sequences into three-dimensional arrays, and so on.
    
    * 标准初始化array:
    * - 使用list或tuple指定维度(shape)，和数据类型:np.zeros(),np.ones(),np.empty();
    * - 使用数字初始化：np.eye(m,n,dtype)
    * 生成等差数列：np.arange(start,stop,step)函数（只建议生成整数序列，由于浮点型精度原因，生成浮点型数列时无法确定获取的数列元素个数，这是推荐np.linspace()指定元素个数）
    * np.linspace函数：linspace(start, stop, num=50, endpoint=True, retstep=False, dtype=None)，其中retstep指定是否返回创建时的step。
    
2. 高级方法：
    创建与下标相关的矩阵：np.fromfunction(function, shape, **kwargs)
```
def f(x,y):
    return 10*x+y
    
b = np.fromfunction(f,(5,4),dtype=int)
b
```
    
# array 打印
1. 打印规则：
    * 最后一维为从左到右排列；
    * 倒数第二维从上到下排列；
    * 其他维也时从上倒下排列。
    
一维数组打印为行形式，二维数组打印成矩阵形式，三维数组打印成矩阵列表形式。

# array 基本操作
1. + / - 操作

2. * 操作（逐元素）
```
    A = np.array([[1,1],[0,1])
    B = np.array([[2,0],[3,4]])
    C = A*B
```

3. 矩阵乘法：dot()
```
    C = A.dot(B)
```
或者
```
    C = np.dot(A,B)
```

4. *=、/= 、+= 、 -= 原地操作

5. 幂：**（逐元素）

6. 比较操作： <、>、>=、<= （逐元素）

# array高级操作
1. 一元操作：ndarray类已内置实现
    比如 max,min sum等
2. 逐元素累加操作：ndarray.cumsum()
```
b = np.arange(12).reshape(3,4)
b.cumsum(axis=1)
```

# 通用函数
exp()、sqrt()、add()等均为逐元素操作

# 索引、切片和迭代
##  一维、二维操作
跟其他数组操作相同，略。

## 多维操作
### `:`和`...`
假定A是一个5维的array.
1. b = A[i],当[]中维度小于A的维度时，默认补全：,即b = A[i] = A[i,:,:,:,:];
2. `...`号：跟1中功能类似，只是`...`出现在前面或中间等。例：A[i] = A[i,...], A[...,i] = A[:,:,:,:,I], A[i,...,j] = A[i,:,:,:,j], A[i,...,j,:] = A[i,:,:,j,:];
### 迭代
1. 从外层向内层逐层迭代。
2. 逐元素操作：`A.flat`,返回迭代器类型，从内层向外层逐层迭代(C-style)。

# 维度变换管理
##1. 平铺
`ndarray.ravel(order = 'C')` 或者 `np.ravel(ndarray,order = 'C')`,
order有四个参数：
    *`C`——C-style;
    *`F`——Fortan-style;
    *`A`——如果内存连续，按Fortan-style读，否则按C-style读;
    *`K`——按数据的实际内存排列读;
    
与ndarray.flat的区别：ndarray.flat返回的是numpy.flatiter的数据类型，而不是numpy.ndarray数据类型，而ravel()返回的是原数据的拷贝，不是引用。

##2. reshape:
    相当于两步：ravel(order = 'C') 和reshape(shape = newshape)，返回数据拷贝。
    
##3. resize:
    与reshape功能相同，但是不返回数据拷贝，而是原地操作数组。
    
##4. 组合数组
###1. a.shape = b.shape,且rank > 1时
   1. 垂直组合：`np.vstack((a,b)) = np.row_stack((a,b))`
   2. 水平组合：`np.hstack((a,b)) = np.column_stack((a,b))`

###2. a的rank = 1时
   1. 一维变二维：`a[:,newaxis] = np.vstack((a)) = np.row_stack((a))`；
   2. 二维变三维：np.stack(arrays, axis=0),（不做笔记，具体使用时先实验）
   3. 高维数组（rank > 2）的`hstack`和`vstack`：`hstack`沿第二轴，`vstack`沿第一轴，`concatenate`允许选定特定的轴。

##5. 分割数组
    1. 垂直分割：np.vsplit()
    2. 水平分割：np.hsplit()
    3. 高维分割：split，hsplit,vsplit与组合函数类似
    
# broadcasting:广播
[网络资料](http://blog.csdn.net/lanchunhui/article/details/50158975)
当操作两个array时，numpy会逐个比较它们的shape（构成的元组tuple），只有在下述情况下，两arrays才算兼容：
    * 相等
    * 其中一个为1，（进而可进行拷贝拓展已至，shape匹配）

一定要注意，执行 broadcast 的前提在于，两个 ndarray 执行的是 element-wise（按位加，按位减） 的运算，而不是矩阵乘法的运算，矩阵乘法运算时需要维度之间严格匹配。（且矩阵乘法，np.dot(A, B) 如果维度不匹配，提示的错误不会是 broadcast，而是 aligned）



# 线性代数
```
import numpy as np
a = np.array([[1.0, 2.0], [3.0, 4.0]])
b = np.array([[-2.0, 1.0], [1.5, -0.5]])
# 转置
x = a.transpose()
x = a.T

# 矩阵的逆
x = np.linalg.inv(a)

# eye
u = np.eye(2)

# 矩阵乘法
x = np.dot(a,b)

```
# trace
x = np.trace(u)

#求解线性方程
y = np.array([[5.], [7.]])
np.linalg.solve(a, y)

