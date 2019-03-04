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



