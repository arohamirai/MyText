# 机器学习

标签（空格分隔）： 监督学习，supervisor learning
#第一周 
 1. 机器学习定义：
 &emsp;&emsp;A computer program is said to learn from experience E with respect to some class of tasks T and performance measure P, if its performance at tasks in T, as measured by P, improves with experience E.
 2. 机器学习算法：
&emsp;&emsp;1. 监督学习（supervised learning）
&emsp;&emsp;&emsp;&emsp;1. 回归（regression）
&emsp;&emsp;&emsp;&emsp;2. 分类（classification）
&emsp;&emsp;2. 无监督学习（unsupervised learning）

 3. 监督学习：
&emsp;&emsp;In supervised learning, we are given a data set and already know what our correct output should look like, having the idea that there is a relationship between the input and the output.

 4. 无监督学习
&emsp;&emsp;Unsupervised learning allows us to approach problems with little or no idea what our results should look like. We can derive structure from data where we don't necessarily know the effect of the variables.

# 第二周
##一、回归（regression）

0. 符号定义：
m：训练集的样本数。
n: 样本的特征点个数.
x：输入变量/特征。
y：输入变量/目标变量。
$x^i$：训练集中的第i个样本。
$y^i$：训练集中第i个样本的对应输出。
$x^i_j$：训练集中第i个样本的第j个特征的值。
1. 代价函数（cost function）
<center> $J(\theta_0, \theta_1) = \dfrac {1}{2m} \displaystyle \sum _{i=1}^m \left ( \hat{y}^{i}- y^{i} \right)^2 = \dfrac {1}{2m} \displaystyle \sum _{i=1}^m \left (h_\theta (x^{i}) - y^{i} \right)^2$</center>
&emsp;&emsp;取$\dfrac{1}{2}$是为了后面后面梯度下降法计算方便.

| Hypothesis | $h_\theta(x) = \theta_0+\theta_1x$ |
| --------|-----:|
| Parameters | $\theta_0,\theta_1$ |
|CostFunction|$J(\theta_0, \theta_1) = \dfrac {1}{2m} \displaystyle \sum _{i=1}^m \left ( \hat{y}^{i}- y^{i} \right)^2 = \dfrac {1}{2m} \displaystyle \sum _{i=1}^m \left (h_\theta (x^{i}) - y^{i} \right)^2$|

3. 梯度下降法：
repeat until convergence:
$$\theta_j := \theta_j - \alpha \frac{\partial}{\partial \theta_j} J(\theta_0, \theta_1)$$

每次迭代，应该同时更新$\theta_j$，更新公式如下：
\begin{align*} \text{repeat until convergence: } \lbrace & \newline \theta_0 := & \theta_0 - \alpha \frac{1}{m} \sum\limits_{i=1}^{m}(h_\theta(x^{i}) - y^{i}) \newline \theta_1 := & \theta_1 - \alpha \frac{1}{m} \sum\limits_{i=1}^{m}\left((h_\theta(x^{i}) - y^{i}) x^{i}_{1}\right)\newline... \newline \theta_n:= & \theta_n - \alpha \frac{1}{m} \sum\limits_{i=1}^{m}\left((h_\theta(x^{i}) - y^{i}) x^{i}_{n}\right) \newline \rbrace& \end{align*}
梯度下降法的一个良好特性：随着迭代离收敛点越近，每次的迭代步长会自动缩小。
4. 批量梯度下降法（“Batch” Gradient Descent）：
&emsp;&emsp;梯度下降法每次迭代时都使用所有的训练集数据。
## 特征缩放(feature scaling)
1. 缩放原则:使特征取值缩放到在[$-\frac{1}{3}$ $\frac{1}{3}$]和[-3 3]之间.即特征值缩放时,往0缩放不能使特征的最大值小于$\frac{1}{3}$,往$\infty$缩放最大值不能超过3.
2. 缩放方法:
&emsp;&emsp;1. 均值归一化(Mean normlization)
$$x_i := \dfrac{x_i - \mu_i}{s_i}$$
其中:
$\mu_i$: $x^i_j$特征的平均值.
$s_i$: $x^i_j$特质值的max-min,或者是标准方差.
&emsp;&emsp;

## 学习率$\alpha$(learning rate)
1.总则:
&emsp;&emsp;1. $\alpha$太小,收敛较慢.
&emsp;&emsp;2. $\alpha$太大,$J(\theta)$可能不会每次迭代都收敛,甚至最后不收敛.
## 正规方程(Normal Equation)
2.方程:
$$\theta = (X^T X)^{-1}X^T y$$
$X$:一行表示一个训练样本.
OCTAVE命令:
```
pinv(x'*x)*x'*y
```
3.$X^T X$wei 非可逆矩阵的原因及解决方法:
&emsp;&emsp;1.Redundant features(linear dependent):删除存在线性相关的特征,只保留一个.
&emsp;&emsp;2.Too many features (e.g. m ≤ n):删除一些特征,或者使用regularization.

<center>梯度下降法与正规方程的比较</center>
|梯度下降法 | 正规方程|
| --------|-----:|
|Need to choose alpha |No need to choose alpha |
|Needs many iterations|No need to iterate|
|O($kn^2$)|O($n^3$)need to calculate inverse of $X^TX$|
|Works well when n is large|Slow if n is very large|
4.使用原则:
当$n<=10000$时,使用正规方程,当$n>10000$时,使用梯度下降法.

## 编程指南
X:特质值为行排列形式.

1.假设函数:
```
Hx = X*theta;
```
2.预测方程:
```
predict = theta'*x;
```
3.代价函数:
```
J = (hx - y)'*(hx - y)/(2*m);
```
4.梯度下降法:
```
theta = theta - alpha*(1/m)*((hx - y)'*X)'; 
```

5.特征缩放:
```
// X 不包含常量1项
[m,n] = size(X);
  
mu = mean(X,1);

sigma = std(X,1,1);

X_norm = (X-repmat(mu,m,1))./repmat(sigma,m,1);
```

6.正规方程:
```
theta = pinv(X'*X)*X'*y;
```
#第三周
# 二、分类(Classification)
## 假设模型:
假设模型为Sigmoid方程:
$$\begin{align*}& h_\theta (x) = g ( \theta^T x ) \newline \newline& z = \theta^T x \newline& g(z) = \dfrac{1}{1 + e^{-z}}\end{align*}$$

表示为1的概率,即:
$$ h_\theta(x) = P(y=1 | x ; \theta) = 1 - P(y=0 | x ; \theta)$$
sigmoid方程的图形如下:
<center> ![sigmoid](http://wx2.sinaimg.cn/mw690/006H1aMCgy1feoivrwjkvj30my03k0su.jpg) </center>

## 决策边界(decision Boundary)
在分类问题中:
$$\begin{align*}& h_\theta(x) \geq 0.5 \rightarrow y = 1 \newline& h_\theta(x) < 0.5 \rightarrow y = 0 \newline\end{align*}$$
等价于:
$$\begin{align*}& \theta^T x \geq 0 \Rightarrow y = 1 \newline& \theta^T x < 0 \Rightarrow y = 0 \newline\end{align*}$$
下面这个公式可以减去求sigmoid方程的过程.

## 代价函数(Cost Function)
分类问题的代价函数:
$$\begin{align*}& J(\theta) = \dfrac{1}{m} \sum_{i=1}^m \mathrm{Cost}(h_\theta(x^{(i)}),y^{(i)}) \newline & \mathrm{Cost}(h_\theta(x),y) = -\log(h_\theta(x)) \; & \text{if y = 1} \newline & \mathrm{Cost}(h_\theta(x),y) = -\log(1-h_\theta(x)) \; & \text{if y = 0}\end{align*}$$

简化形式:
$$\begin{align*}&J(\theta) = - \frac{1}{m} \displaystyle \sum_{i=1}^m [y^{(i)}\log (h_\theta (x^{(i)})) + (1 - y^{(i)})\log (1 - h_\theta(x^{(i)}))];\newline& \mathrm{Cost}(h_\theta(x),y) = - y \; \log(h_\theta(x)) - (1 - y) \log(1 - h_\theta(x))\end{align*}$$
向量形式:
$$\begin{align*} & h = g(X\theta)\newline & J(\theta) = \frac{1}{m} \cdot \left(-y^{T}\log(h)-(1-y)^{T}\log(1-h)\right) \end{align*}$$

## 梯度下降法:
$$\begin{align*} & Repeat \; \lbrace \newline & \; \theta_j := \theta_j - \frac{\alpha}{m} \sum_{i=1}^m (h_\theta(x^{(i)}) - y^{(i)}) x_j^{(i)} \newline & \rbrace \end{align*}$$

向量形式:
$$\theta := \theta - \frac{\alpha}{m} X^{T} (g(X \theta ) - \vec{y})$$

证明过程[^logicgradprove].

## 借用规划库
0.一些优化算法
|英文|中文|特点|
|--------|-----:|
|Grandient Descent|梯度下降法|理解简单,但需要手动选择$\alpha$|
|Conjugate Gradient|共轭梯度法|不需要手动选择$\alpha$,并且通常速度更快|
|BFGS|拟牛顿法|不需要手动选择$\alpha$,并且通常速度更快|
|L-BFGS|LIMIT-MEMORY BFGS|不需要手动选择$\alpha$,并且通常速度更快|
1.目的:得到$\theta$.
2.需要提供:
提供计算代价函数和梯度的函数,即计算:
$$\begin{align*} & J(\theta) \newline & \dfrac{\partial}{\partial \theta_j}J(\theta)\end{align*}$$
3.代码实现:
3.1自己实现costFunction:
```
function [jVal, gradient] = costFunction(theta)
  jVal = [...code to compute J(theta)...];
  gradient = [...code to compute derivative of J(theta)...];
end
```
3.2调用高级库优化:
```
options = optimset('GradObj', 'on', 'MaxIter', 100);
initialTheta = zeros(2,1);
   [optTheta, functionVal, exitFlag] = fminunc(@costFunction, initialTheta, options);
```

## 多类别分类(Multiclass Classification)
1.思想:One VS all
对每个类,都训练一个二类分类器(该类,不是该类),得到k个分类器(k等于类别数),当有新数据进入时,带入k个分类器,取其中概率最大的值为预测的类别.
$$\begin{align*}& y \in \lbrace0, 1 ... n\rbrace \newline& h_\theta^{(0)}(x) = P(y = 0 | x ; \theta) \newline& h_\theta^{(1)}(x) = P(y = 1 | x ; \theta) \newline& \cdots \newline& h_\theta^{(n)}(x) = P(y = n | x ; \theta) \newline& \mathrm{prediction} = \max_i( h_\theta ^{(i)}(x) )\newline\end{align*}$$

## Overfitting:
1.不恰当的拟合后果:
|不恰当的拟合|后果|
|---|----:|:---:|
|Overfitting|High bias|
|underfitting|High variance|
2.防止过拟合方法:
&emsp;&emsp;2.1减少特征数量
&emsp;&emsp;&emsp;&emsp;2.1.1手动选择保留特征;
&emsp;&emsp;&emsp;&emsp;2.1.2自动选择(参看后文).
&emsp;&emsp;2.2正则化(Regularization):保留所有特征,但是减小他们的权重.

## 正则化(Regularization)
通过在代价函数内 添加正则化项$\lambda\ \sum_{j=1}^n \theta_j^2$,($x_{0}^{i} = 0$ 项不用正则化),使得拟合的线稍微平滑,以抑制过拟合,$\lambda$称为**正则化参数(regularization parameter)**.
### 1.线性回归(linear regression)的正则化
1.正则化的代价函数为:
$$J(\theta) =  \dfrac{1}{2m}\  \sum_{i=1}^m (h_\theta(x^{(i)}) - y^{(i)})^2 + \lambda\ \sum_{j=1}^n \theta_j^2$$

2.正则化方程的梯度下降法:
$$\begin{align*}& Repeat \; \lbrace \newline & \; \theta_0 : = \theta_0 - \alpha\frac{1}{m}\sum_{i=1}^m(h_\theta(x^{(i)}) - y^{(i)})x_j^{(i)} \newline& \theta_j := \theta_j(1 - \alpha\frac{\lambda}{m}) - \alpha\frac{1}{m}\sum_{i=1}^m(h_\theta(x^{(i)}) - y^{(i)})x_j^{(i)}\newline&\newline &\rbrace \end{align*}$$


精髓就在于,$(1 - \alpha\frac{\lambda}{m})$项通常是一个接近于1,但比1小的值,因此比起未正则化,左边$\theta_j$通常较右边$\theta_j$小.

3.正则化方程的正规方程法:
$$\begin{align*}& \theta = \left( X^TX + \lambda \cdot L \right)^{-1} X^Ty \newline& \text{where}\ \ L = \begin{bmatrix} 0 & & & & \newline & 1 & & & \newline & & 1 & & \newline & & & \ddots & \newline & & & & 1 \newline\end{bmatrix}\newline& L \in R^{(n+1)x(n+1)}\end{align*}$$

### 2.分类(classification,logic regression)的正则化
1.正则化的代价函数:
$$J(\theta) = - \frac{1}{m} \sum_{i=1}^m \large[ y^{(i)}\ \log (h_\theta (x^{(i)})) + (1 - y^{(i)})\ \log (1 - h_\theta(x^{(i)}))\large] + \frac{\lambda}{2m}\sum_{j=1}^n \theta_j^2$$
2.正则化的梯度下降法:
与linear regression相似:
$$\begin{align*}& Repeat \; \lbrace \newline & \; \theta_0 : = \theta_0 - \alpha\frac{1}{m}\sum_{i=1}^m(h_\theta(x^{(i)}) - y^{(i)})x_j^{(i)} \newline& \theta_j := \theta_j(1 - \alpha\frac{\lambda}{m}) - \alpha\frac{1}{m}\sum_{i=1}^m(h_\theta(x^{(i)}) - y^{(i)})x_j^{(i)}\newline&\newline &\rbrace \end{align*}$$





## 编程指南
1.logic regression模型:
```
h = g(X*theta);
```
2.未正则化代价函数:
```
J = 1/m * (-y'*log(h)-(1-y)'*log(1-h));
```
3.未正则梯度下降:
```
theta = theta - alpha/m *X'(g(X*theta)-y);
```
2.正则化代价函数:
```
J = 1/m * (-y'*log(h)-(1-y)'*log(1-h))+lambda/(2*m)*(theta'*theta-theta[1]*theta[1]);
```
3.正则梯度下降:
```
theta = theta*(1-alpha*lambda/m) - alpha/m *X'(g(X*theta)-y);
theta[0] =  theta* - alpha/m *X'(g(X*theta)-y);
```




# 第五周

1.符号定义:
$L$:网络的总层数(total layers);
$s_l$:l层不包括偏差项的总单元数(total unit in layer l ,not counting bias unit);
$K$:输出层的单元数,即类别总数(total unit of output layer);

## 1.代价函数
$$\begin{gather*} J(\Theta) = - \frac{1}{m} \sum_{i=1}^m \sum_{k=1}^K \left[y^{(i)}_k \log ((h_\Theta (x^{(i)}))_k) + (1 - y^{(i)}_k)\log (1 - (h_\Theta(x^{(i)}))_k)\right] + \frac{\lambda}{2m}\sum_{l=1}^{L-1} \sum_{i=1}^{s_l} \sum_{j=1}^{s_{l+1}} ( \Theta_{j,i}^{(l)})^2\end{gather*}$$
其中:
$h_{\theta}(x) \in R^K$;
$(h_{\theta}(x))_{i} = i^{th}\text{output}$;

NOTE:
1.上面公式中2次累加项是计算输出层的每个单元的logiistic regression.
2.上面公司中3次累加项是把整个网络的$\theta_{s}$的每个单元.
3.上面公司中3次累加项中的$i$不是指训练集的数目.

##2.梯度下降法




[^logicgradprove]:https://www.baidu.com/s?wd=%E8%AF%81%E6%98%8E+%E7%BF%BB%E8%AF%91