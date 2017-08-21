 文件读取数据

#零、pipeline
1. 文件名列表
2. 可配置的 文件名乱序(shuffling)
3. 可配置的 最大训练迭代数(epoch limit)
4. 文件名队列
5. 针对输入文件格式的阅读器
6. 纪录解析器
7. 可配置的预处理器
8. 样本队列


# 一、文件名列表
## 1. 直接手打名字：["file0", "file1", ...];
## 2. 列表解析：[("file%d" % i) for i in range(2)]
## 3. tf函数：tf.train.match_filenames_once

