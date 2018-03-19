#1. Affine Transform
*表示 2D 仿射变换，它执行从 2D 坐标到其他 2D 坐标的线性映射，保留了线的“直线性”和“平行性”。可以使用一系列平移 (translation)、缩放 (scale)、翻转 (flip)、旋转 (rotation) 和错切 (shear) 来构造仿射变换。
*6个自由度
*可以用3x2矩阵表示，也可以用3x3矩阵表示，此时最后一行为[0 0 1]
#2. projective transformation
* 也叫单应性变换（homography）
* 它有一项不变性，那就是在原图中保持共线的3个点，变换后仍旧共线
* 具有8个自由度
* (Dim+1)^2矩阵表示

#3. isometric transform
* 等距变换，保持欧式距离不变，实质：对图像的旋转+平移
* 3个自由度(1旋转角θ+两个平移tx,ty)

#4. similarity transform
* 相似变换，等距变换+均匀缩放
* 4 个自由度
