#一. 协方差公式
若向量$x$的协方差为$\Sigma$，则Ax的协方差为$A\Sigma A^T$
\begin{equation} 
\begin{split} 
Cov(x) &= \Sigma\\ 
Cov(\color{firebrick}{\mathbf{A}}x) &= \color{firebrick}{\mathbf{A}} \Sigma \color{firebrick}{\mathbf{A}}^T 
\end{split} \label{covident} 
\end{equation}

# 二. 预测（predict）
##1. 运动描述
最简单的情况，机器人以一定速度匀速运动，预测方程为：
\begin{split} 
\color{deeppink}{p_k} &= \color{royalblue}{p_{k-1}} + \Delta t &\color{royalblue}{v_{k-1}} \\ 
\color{deeppink}{v_k} &= &\color{royalblue}{v_{k-1}} 
\end{split}
写成矩阵形式
\begin{align} 
\color{deeppink}{\mathbf{\hat{x}}_k} &= \begin{bmatrix} 
1 & \Delta t \\ 
0 & 1 
\end{bmatrix} \color{royalblue}{\mathbf{\hat{x}}_{k-1}} \\ 
&= \mathbf{F}_k \color{royalblue}{\mathbf{\hat{x}}_{k-1}} \label{statevars} 
\end{align}
$F_k$：状态转移矩阵，也叫预测矩阵(prediction matrix)
$u_k$：控制向量，表示外部影响（External influence）（该因素可知）,比如机器人即时发送的命令，突然加减速，转弯等不可预测的因素
##2. 外部控制
$B_k$：控制矩阵，用于将控制向量转移到下一状态的影响
例如，在机器人运动时，给机器人发送一个加速命令，加速度为$a$，则新的转移方程为：
\begin{equation} 
\begin{split} 
\color{deeppink}{\mathbf{\hat{x}}_k} &= \mathbf{F}_k \color{royalblue}{\mathbf{\hat{x}}_{k-1}} + \begin{bmatrix} 
\frac{\Delta t^2}{2} \\ 
\Delta t 
\end{bmatrix} \color{darkorange}{a} \\ 
&= \mathbf{F}_k \color{royalblue}{\mathbf{\hat{x}}_{k-1}} + \mathbf{B}_k \color{darkorange}{\vec{\mathbf{u}_k}} 
\end{split} 
\end{equation}
##3. 未知因素影响
$Q_k$：未知因素对系统的影响，比如车轮打滑，飞行器被风吹动，该变量添加到协方差矩阵中，表示预测不确定性增加。
\begin{equation} 
\begin{split} 
\color{deeppink}{\mathbf{\hat{x}}_k} &= \mathbf{F}_k \color{royalblue}{\mathbf{\hat{x}}_{k-1}} + \mathbf{B}_k \color{darkorange}{\vec{\mathbf{u}_k}} \\ 
\color{deeppink}{\mathbf{P}_k} &= \mathbf{F_k} \color{royalblue}{\mathbf{P}_{k-1}} \mathbf{F}_k^T + \color{mediumaquamarine}{\mathbf{Q}_k} 
\end{split} 
\label{kalpredictfull} 
\end{equation}
In other words, the **new best estimate** is a **prediction** made from **previous best estimate**, plus a **correction** for **known external influences**.

And the **new uncertainty** is **predicted** from the **old uncertainty**, with some **additional uncertainty from the environment**.
#三、更新(update)


$H_k$：测量矩阵，传感器测量值与观测值可能单位不同、比例不同，通过该矩阵将传感器测量值转换到观测值系统下。
观测值到传感器测量值的变换：
\begin{equation} 
\begin{aligned} 
\vec{\mu}_{\text{expected}} &= \mathbf{H}_k \color{deeppink}{\mathbf{\hat{x}}_k} \\ 
\mathbf{\Sigma}_{\text{expected}} &= \mathbf{H}_k \color{deeppink}{\mathbf{P}_k} \mathbf{H}_k^T 
\end{aligned} 
\end{equation}
$Z_k$：传感器测量值
$R_k$：传感器之间的协方差矩阵
$K$：卡尔曼增益（kalman gain）

融合传感器数据（measurement）与预测数据（predict）后的新分布:
\begin{equation} \label{matrixgain} 
\color{purple}{\mathbf{K}} = \Sigma_0 (\Sigma_0 + \Sigma_1)^{-1} 
\end{equation}
\begin{equation} 
\begin{split} 
\color{royalblue}{\vec{\mu}’} &= \vec{\mu_0} + &\color{purple}{\mathbf{K}} (\vec{\mu_1} – \vec{\mu_0})\\ 
\color{mediumblue}{\Sigma’} &= \Sigma_0 – &\color{purple}{\mathbf{K}} \Sigma_0 
\end{split} \label{matrixupdate} 
\end{equation}
（$\mu_0$, $\Sigma_0$）和（$\mu_1$, $\Sigma_1$）为measurement和predict的高斯分布，两者是平等关系，没有非要（$\mu_0$, $\Sigma_0$）就是measurement，（$\mu_1$, $\Sigma_1$)就是predict，具体可看理论补充1）
#四、 整合
##1. 两个分布：
预测：$(\color{fuchsia}{\mu_0}, \color{deeppink}{\Sigma_0}) = (\color{fuchsia}{\mathbf{H}_k \mathbf{\hat{x}}_k}, \color{deeppink}{\mathbf{H}_k \mathbf{P}_k \mathbf{H}_k^T})$
测量：$(\color{yellowgreen}{\mu_1}, \color{mediumaquamarine}{\Sigma_1}) = (\color{yellowgreen}{\vec{\mathbf{z}_k}}, \color{mediumaquamarine}{\mathbf{R}_k})$
##2. 融合测量
两者相乘，更新预测：
\begin{equation} 
\begin{split} 
\color{royalblue}{\mathbf{\hat{x}}_k’} &= \color{fuchsia}{\mathbf{\hat{x}}_k} & + & \color{purple}{\mathbf{K}’} ( \color{yellowgreen}{\vec{\mathbf{z}_k}} – \color{fuchsia}{\mathbf{H}_k \mathbf{\hat{x}}_k} ) \\ 
\color{royalblue}{\mathbf{P}_k’} &= \color{deeppink}{\mathbf{P}_k} & – & \color{purple}{\mathbf{K}’} \color{deeppink}{\mathbf{H}_k \mathbf{P}_k} 
\end{split} 
\label{kalupdatefull} 
\end{equation}
\begin{equation} 
\color{purple}{\mathbf{K}’} = \color{deeppink}{\mathbf{P}_k \mathbf{H}_k^T} ( \color{deeppink}{\mathbf{H}_k \mathbf{P}_k \mathbf{H}_k^T} + \color{mediumaquamarine}{\mathbf{R}_k})^{-1} 
\label{kalgainfull} 
\end{equation}
##3. 流程图
<center>![Kalman Filter循环过程](http://ws2.sinaimg.cn/large/006H1aMCly1fpy75woq4oj30bt0fagng.jpg)</center>


#五、应用
需要输入的参数(N维)：
$x$：初始state，2n*1大小（向量）
$P$：初始协方差，2n*2n大小

$u_k$：控制输入向量，大小未知
$B_k$：控制矩阵，大小未知($B_k*u_k$)
$F_k$：转移矩阵，2n*2n大小。

$H_k$：测量矩阵，n*2n大小（$H_k*x$）
$R_k$：测量协方差，n*n大小


#六、示例代码
##1. 一维kalman滤波
```py
def kalman_filter(x, P):
    for n in range(len(measurements)):
        
        # measurement update
        Z = matrix([[measurements[n]]])
        y = Z- (H*x)
        S = H*P*H.transpose() + R
        K = P*H.transpose()*S.inverse()
        x = x +(K*y)
        P = (I - (K*H))*P
        # prediction
        x = (F*x) +u
        P = F*P*F.transpose()
        #print [x, P]
        
    return x,P

############################################
### use the code below to test your filter!
############################################

measurements = [1, 2, 3]

x = matrix([[0.], [0.]]) # initial state (location and velocity)
P = matrix([[1000., 0.], [0., 1000.]]) # initial uncertainty
u = matrix([[0.], [0.]]) # external motion
F = matrix([[1., 1.], [0, 1.]]) # next state function
H = matrix([[1., 0.]]) # measurement function
R = matrix([[1.]]) # measurement uncertainty
I = matrix([[1., 0.], [0., 1.]]) # identity matrix

print(kalman_filter(x, P))
# output should be:
# x: [[3.9996664447958645], [0.9999998335552873]]
# P: [[2.3318904241194827, 0.9991676099921091], [0.9991676099921067, 0.49950058263974184]]

```
##2. 二维kalman滤波
```
def filter(x, P):
    for n in range(len(measurements)):
        
        # prediction
        x = (F * x) + u
        P = F * P * F.transpose()
        
        # measurement update
        Z = matrix([measurements[n]])
        y = Z.transpose() - (H * x)
        S = H * P * H.transpose() + R
        K = P * H.transpose() * S.inverse()
        x = x + (K * y)
        P = (I - (K * H)) * P
    
    print 'x= '
    x.show()
    print 'P= '
    P.show()

########################################

print "### 4-dimensional example ###"

measurements = [[5., 10.], [6., 8.], [7., 6.], [8., 4.], [9., 2.], [10., 0.]]
initial_xy = [4., 12.]

# measurements = [[1., 4.], [6., 0.], [11., -4.], [16., -8.]]
# initial_xy = [-4., 8.]

# measurements = [[1., 17.], [1., 15.], [1., 13.], [1., 11.]]
# initial_xy = [1., 19.]

dt = 0.1

x = matrix([[initial_xy[0]], [initial_xy[1]], [0.], [0.]]) # initial state (location and velocity)
u = matrix([[0.], [0.], [0.], [0.]]) # external motion

#### DO NOT MODIFY ANYTHING ABOVE HERE ####
#### fill this in, remember to use the matrix() function!: ####

P =  matrix([[0, 0, 0, 0],[0 , 0 ,0 ,0],[0, 0, 1000, 0],[0, 0, 0, 1000]])# initial uncertainty: 0 for positions x and y, 1000 for the two velocities
F =  matrix([[1,0,dt,0],[0,1,0,dt],[0,0,1,0],[0,0,0,1]])# next state function: generalize the 2d version to 4d
H =  matrix([[1,0,0,0],[0,1,0,0]])# measurement function: reflect the fact that we observe x and y but not the two velocities
R =  matrix([[0.1,0],[0,0.1]])# measurement uncertainty: use 2x2 matrix with 0.1 as main diagonal
I =  matrix([[1,0,0,0],[0,1,0,0],[0,0,1,0],[0,0,0,1]])# 4d identity matrix

###### DO NOT MODIFY ANYTHING HERE #######

filter(x, P)

```

#五、理论补充
##1. 高斯相乘
两个高斯分布相乘，其结果是一个新的高斯分布。
考虑1d情况，有两个已知高斯分布，其参数分布为($\mu_1$, $sigma_1$)和($\mu_2$, $sigma_2$)，相乘结果如下：
<center>![image](https://ws1.sinaimg.cn/large/006H1aMCly1fpy4jhlu1hj30gd0aldfx.jpg)</center>

\begin{equation} \label{fusionformula} 
\begin{aligned} 
\color{royalblue}{\mu’} &= \mu_0 + \frac{\sigma_0^2 (\mu_1 – \mu_0)} {\sigma_0^2 + \sigma_1^2}\\ 
\color{mediumblue}{\sigma’}^2 &= \sigma_0^2 – \frac{\sigma_0^4} {\sigma_0^2 + \sigma_1^2} 
\end{aligned} 
\end{equation}
（补充：更原始的形式如下：
\begin{equation} \label{originfusionformula} 
\begin{aligned} 
\color{royalblue}{\mu’} &= \frac{\mu_0*\sigma_1^2 + \mu_1 * \sigma_0^2}{\sigma_0^2 + \sigma_1^2}\\ 
\color{mediumblue}{\sigma’}^2 &= \frac{1}{\frac{1}{\sigma_0^2} + \frac{1}{\sigma_1^2}}
\end{aligned} 
\end{equation}
）
提取出一个因子$k$，上式可以简写成
\begin{equation} \label{gainformula} 
\color{purple}{\mathbf{k}} = \frac{\sigma_0^2}{\sigma_0^2 + \sigma_1^2} 
\end{equation}
\begin{equation} 
\begin{split} 
\color{royalblue}{\mu’} &= \mu_0 + &\color{purple}{\mathbf{k}} (\mu_1 – \mu_0)\\ 
\color{mediumblue}{\sigma’}^2 &= \sigma_0^2 – &\color{purple}{\mathbf{k}} \sigma_0^2 
\end{split} \label{update} 
\end{equation}
写成矩阵形式（一维及高维）
\begin{equation} \label{matrixgain} 
\color{purple}{\mathbf{K}} = \Sigma_0 (\Sigma_0 + \Sigma_1)^{-1} 
\end{equation}
\begin{equation} 
\begin{split} 
\color{royalblue}{\vec{\mu}’} &= \vec{\mu_0} + &\color{purple}{\mathbf{K}} (\vec{\mu_1} – \vec{\mu_0})\\ 
\color{mediumblue}{\Sigma’} &= \Sigma_0 – &\color{purple}{\mathbf{K}} \Sigma_0 
\end{split} \label{matrixupdate} 
\end{equation}

#参考资料：
[1]. [How a Kalman filter works, in pictures](http://www.bzarg.com/p/how-a-kalman-filter-works-in-pictures/)
[2]. [Understanding the Basis of the Kalman Filter Via a Simple and Intuitive Derivation](http://ieeexplore.ieee.org/document/6279585/?reload=true)