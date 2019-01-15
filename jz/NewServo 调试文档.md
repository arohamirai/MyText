## 一，理想模拟
相机Z轴向前，x轴为横向方向，参数如下
### 1. 无横向偏移，无角度偏移
```
    // INIT wMc, wMcd
    wMc.setIdentity();
    //wMc.prerotate(Eigen::AngleAxisd(M_PI / 4, Eigen::Vector3d ( 0,1,0 )));
    wMc.pretranslate(Eigen::Vector3d(0.2, 0.1, 2));

    wMcd.setIdentity();
    //wMcd.prerotate(Eigen::AngleAxisd(M_PI / 2, Eigen::Vector3d ( 0,0,1 )));
    //wMcd.prerotate(Eigen::AngleAxisd(-M_PI / 4, Eigen::Vector3d ( 0,1,0 )));
    wMcd.pretranslate(Eigen::Vector3d(0.2, 0.1, 4));

```
![image](https://ws4.sinaimg.cn/large/006H1aMCgy1fz1nbldc97j30ru0n1mxi.jpg)
### 2. 没有横向偏移，但有角度偏移
```
 wp[0] = Eigen::Vector3d( 0., 0.2, 4.1);
    wp[1] = Eigen::Vector3d( 0.5, 0.1, 8.2);
    wp[2] = Eigen::Vector3d( 0.9, 0.5, 8.3);

    // INIT wMc, wMcd
    wMc.setIdentity();
    //wMc.prerotate(Eigen::AngleAxisd(M_PI / 4, Eigen::Vector3d ( 0,1,0 )));
    wMc.pretranslate(Eigen::Vector3d(0.2, 0.1, 2));

    wMcd.setIdentity();
    //wMcd.prerotate(Eigen::AngleAxisd(M_PI / 2, Eigen::Vector3d ( 0,0,1 )));
    wMcd.prerotate(Eigen::AngleAxisd(-M_PI / 4, Eigen::Vector3d ( 0,1,0 )));
    wMcd.pretranslate(Eigen::Vector3d(0.2, 0.1, 4));
```
![image](https://wx2.sinaimg.cn/large/006H1aMCgy1fz1mn2ahn7j30rq0mz74j.jpg)

### 3. 有横向偏移，有角度偏移
```
    // INIT wMc, wMcd
    wMc.setIdentity();
    //wMc.prerotate(Eigen::AngleAxisd(M_PI / 4, Eigen::Vector3d ( 0,1,0 )));
    wMc.pretranslate(Eigen::Vector3d(0.2, 0.1, 2));

    wMcd.setIdentity();
    //wMcd.prerotate(Eigen::AngleAxisd(M_PI / 2, Eigen::Vector3d ( 0,0,1 )));
    wMcd.prerotate(Eigen::AngleAxisd(-M_PI / 4, Eigen::Vector3d ( 0,1,0 )));
    wMcd.pretranslate(Eigen::Vector3d(0.5, 0.1, 4));

```
![image](https://ws1.sinaimg.cn/large/006H1aMCgy1fz1n81m6zvj30rs0n3mxi.jpg)

如果加入横向偏置，结果如下：
```
    // INIT wMc, wMcd
    wMc.setIdentity();
    //wMc.prerotate(Eigen::AngleAxisd(M_PI / 4, Eigen::Vector3d ( 0,1,0 )));
    wMc.pretranslate(Eigen::Vector3d(0.2, 0.1, 2));

    wMcd.setIdentity();
    //wMcd.prerotate(Eigen::AngleAxisd(M_PI / 2, Eigen::Vector3d ( 0,0,1 )));
    wMcd.prerotate(Eigen::AngleAxisd(-M_PI / 4, Eigen::Vector3d ( 0,1,0 )));
    wMcd.pretranslate(Eigen::Vector3d(0.5, 0.1, 4));
```
![image](https://ws3.sinaimg.cn/large/006H1aMCgy1fz1mpurm6mj30rq0mu3yq.jpg)
## 二、加噪声
给cp 加上噪声，模拟相机检测时的点位置检测误差, 结果显示，e2跳动很大，但最后e2和误差还是可以收敛
### 1. 无横向偏移，无角度偏移
参数：
```
    // INIT wMc, wMcd
    wMc.setIdentity();
    //wMc.prerotate(Eigen::AngleAxisd(M_PI / 4, Eigen::Vector3d ( 0,1,0 )));
    wMc.pretranslate(Eigen::Vector3d(0.2, 0.1, 2));

    wMcd.setIdentity();
    //wMcd.prerotate(Eigen::AngleAxisd(M_PI / 2, Eigen::Vector3d ( 0,0,1 )));
    //wMcd.prerotate(Eigen::AngleAxisd(-M_PI / 4, Eigen::Vector3d ( 0,1,0 )));
    wMcd.pretranslate(Eigen::Vector3d(0.2, 0.1, 4));
```
```
Eigen::Vector3d chaos = Eigen::Vector3d(rng.uniform(0., 0.01), rng.uniform(0., 0.01), rng.uniform(0., 0.01));
cp[i] = wMc.inverse() * (wp[i] + chaos);
```
![image](https://wx2.sinaimg.cn/large/006H1aMCgy1fz1mxywyb3j30rs0n2t92.jpg)
### 2. 没有横向偏移，但有角度偏移
参数：
```
    // INIT wMc, wMcd
    wMc.setIdentity();
    //wMc.prerotate(Eigen::AngleAxisd(M_PI / 4, Eigen::Vector3d ( 0,1,0 )));
    wMc.pretranslate(Eigen::Vector3d(0.2, 0.1, 2));

    wMcd.setIdentity();
    //wMcd.prerotate(Eigen::AngleAxisd(M_PI / 2, Eigen::Vector3d ( 0,0,1 )));
    wMcd.prerotate(Eigen::AngleAxisd(-M_PI / 4, Eigen::Vector3d ( 0,1,0 )));
    wMcd.pretranslate(Eigen::Vector3d(0.2, 0.1, 4));
```
加噪声
```
Eigen::Vector3d chaos = Eigen::Vector3d(rng.uniform(0., 0.01), rng.uniform(0., 0.01), rng.uniform(0., 0.01));
cp[i] = wMc.inverse() * (wp[i] + chaos);
```
结果如下
![image](https://wx1.sinaimg.cn/large/006H1aMCgy1fz1m80afb7j30rq0mxjrp.jpg)

### 3. 有横向偏移，有角度偏移
结果显示 e2不能收敛， 误差也无法收敛到0.001
参数：
```
    // INIT wMc, wMcd
    wMc.setIdentity();
    //wMc.prerotate(Eigen::AngleAxisd(M_PI / 4, Eigen::Vector3d ( 0,1,0 )));
    wMc.pretranslate(Eigen::Vector3d(0.5, 0.1, 2));

    wMcd.setIdentity();
    //wMcd.prerotate(Eigen::AngleAxisd(M_PI / 2, Eigen::Vector3d ( 0,0,1 )));
    wMcd.prerotate(Eigen::AngleAxisd(-M_PI / 4, Eigen::Vector3d ( 0,1,0 )));
    wMcd.pretranslate(Eigen::Vector3d(0.2, 0.1, 4));
```
加噪声
```
Eigen::Vector3d chaos = Eigen::Vector3d(rng.uniform(0., 0.01), rng.uniform(0., 0.01), rng.uniform(0., 0.01));
cp[i] = wMc.inverse() * (wp[i] + chaos);
```
![image](https://wx4.sinaimg.cn/large/006H1aMCgy1fz1mt27xy6j30rq0n5mxi.jpg)