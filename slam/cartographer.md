# 一、 论文阅读(Real-Time Loop Closure in 2D LIDAR SLAM)

0. 精度5cm;
1. 分支定界搜索算法(branch-and-bound approach)做激光与子图的匹配(scan-to-submap matches);
2. 本文的主要贡献是降低了回环检测的计算量；
3. 最近的激光帧只会与最近的submap匹配，当一个submap完成时，该submap就不会再添加新激光，并且该submap自动加入回环检测中去。
4. 算法周期性的进行pose optimization.



# 二、流程图

```flow
st=>start: 开始
e=>end: 结束
op1=>operation: 新激光到来
st->op1
op2=>operation: local 匹配(scan matching)[hit-miss]
op1->op2
op3=>operation: 
```
# 三、 符号说明
* scan位姿表示：$\xi=(\xi_x,\xi_y,\xi_{\theta})$
* 扫描scan(点云)：$ H=\{h_k\}_{k=1,…,K},h_k \in \mathbb{R^2} $
* scan-to-submap变换矩阵:$T_\xi$
* scan-to-submap变换：$T_{\xi }h_k=\underbrace{\left(\begin{matrix}cos\xi_\theta&-sin\xi_\theta\\sin\xi_\theta&cos\xi_\theta\end{matrix} \right)}_{R_\xi}h_k+\underbrace{\left(\begin{matrix}\xi_x\\\xi_y\end{matrix}\right)}_{t_\xi}$
* 概率栅格地图概率值：$M:r\mathbb{Z}\times r\mathbb{Z} \to [p_{min},p_{max}]$
* submap世界坐标系下的位姿（m代表map）：$\Xi^m=\{\xi^m_i\}_{i=1,…,m}$
* scan世界坐标系下的位姿（s代表scan）：$\Xi^s=\{\xi^s_j\}_{j=1,…,n}$
* scan i在匹配到的submap j坐标系下的位姿：$\xi_{ij}$
* 与scan i和submap j相对应的协方差矩阵:$\sum_{ij}$



# 参考资料
1. 

[Cartographer学习一论文阅读](http://ttshun.com/2018/09/12/Cartographer%E5%AD%A6%E4%B9%A0%E4%B8%80%E8%AE%BA%E6%96%87%E9%98%85%E8%AF%BB/)

