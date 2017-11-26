

# 一、机器学习理论
1. 什么是机器学习？
	A computer program is said to learn from experience E with respect to some class of tasks T and performance measure P, if performance at tasks in T, as measured by P, improves with experience E.(一种计算机程序，它在某类测试任务中的表现，随着经验E的丰富而提高)
2. 机器学习中的方法？
	机器学习中的方法或范式（paradigm）有很多种分类体系，例如从学习的方式分，有例子中学习、类比学习、分析学习等，但一般来说，现在研究得最多、被认为最有用的是从例子中学习。最常见的对“从例子中学习”的方法的分类是监督学习、非监督学习和强化学习，这是从训练样本的歧义性（ambiguity）来进行分类的。
3. 什么是有监督学习?（supervised learning）
	In supervised learning, we are given a data set and already know what our correct output should look like, having the idea that there is a relationship between the input and the output.(在有监督学习算法中，给定一个数据集，我们已经知道正确的输出应该是怎么样的，而且知道输入与输出之间一定有某种关系.)
4. 什么是无监督学习？(Unsupervised learning)
	Unsupervised learning allows us to approach problems with little or no idea what our results should look like. We can derive structure from data where we don't necessarily know the effect of the variables.(在无监督学习中，给定一个数据集，我们不知道或很少知道正确的输出应该是怎么样的，无监督学习可以从数据集中发现某些结构化知识，而我们不需要知道每个参数的确切作用。)
5. 什么是半监督学习？(semi-supervised learning)
	简而言之：用于训练的数据集中有样本只有小部分有标签，剩下的大部分都没有标签；
	半监督学习又可分为：
	- 纯(pure)半监督学习：未标注的样本不用于预测，推理用在以后的数据上。
	- 直推学习(transductive learning):未标注的样本恰好是算法要预测的。
6. 能否以有无标签区别有监督学习和无监督学习？
	不能，有监督学习和无监督学习之间有时是很模糊的，比如联合概率问题，它可以分成一系列独立的监督学习问题，同样对于条件概率问题，它又可以用无监督学习的方法来求解。

7. 有无监督算法
	classification、regression、structured output 一般认为是有监督学习
	density estimation 一般认为是无监督学习
	
8. 机器学习中的Task(T)(11类)：
	a. Classification:分类
	b. Classification with missing input:输入缺失(不完整的输入)情况下的分类
	c. Regression:回归
	d. Transcription:转录
	e. Translation:翻译
	f. Structured output:结构化输出
	g. Anomaly detection:异常检测
	h. Synthesis and sampling:合成与采样
	i. Imputation of missing values:缺失值插补
	j. Denoising:去噪
	k. Density estimation or probability mass function estimation:概率密度估计(连续)或概率质量估计(离散)
9. 回归(regression)
	a. 指研究一组随机变量$$(Y_1 ，Y_2 ，…，Y_i)$$和另一组$$(X_1，X_2，…，X_k)$$变量之间*关系*的统计分析方法，又称多重回归分析。通常$$Y_1 ，Y_2 ，…，Y_i$$是因变量，$$X_1，X_2，…，X_k$$是自变量。
	b. 回归主要的种类有：线性回归、曲线回归、二元logistic回归、多元logistic回归。
10. 分类(classification)
	a. 二元logistic回归；
	b. 多元logistic回归:思想：One VS One、one VS all和Many VS Many。
待完善11. 数据集划分
	a. 交叉验证(Cross Validation):一种数据集划分方法，同时也是一种模型挑选方法，适用于数据量较少的场合。
	b. 验证集(Validation Dataset):用于调整模型的超参数，为你和后的模型提供无偏估计。
	c. 测试集(Testing Dataset):为你和后的最终模型提供无偏估计。
	d. 存在$$J_valid < J_test$$的情况，因为最终模型有在验证集上进行了优化。
	e. 偏斜类(Skewed class):
		1). 准确率(Precision)/召回率(Recall);
		2). F-Score = P*R/(P+R);

待完善12. 欠拟合和过拟合(underfitting, overfitting)

待完善13. 学习曲线(Learning curve)


数据清洗
数据预处理
梯度下降方法(GD,SGD,adam,momenton...)
# 二、视觉相关

# 三、卷积神经网络相关
（常见层, CNN, 流行CNN Model, YOLOv2, Face Detection/Recognition）

# 四、传统模式识别相关
（KNN, GMM, EM, PCA, K-means, SMO）

# 五、工作经验

# 六、专业能力
(GPU, C/C++, Linux编程, CMake, OpenCV, DeepLearning.ai专项课程)

# 其、其他知识
1. 什么是强化学习？
强化学习来说，它通过对没有概念标记、但与一个延迟奖赏或效用（可视为延迟的概念标记）相关联的训练例进行学习，以获得某种从状态到行动的映射。这里本来没有概念标记的概念，但延迟奖赏可被视为一种延迟概念标记，因此其训练样本的歧义性介于监督学习和非监督学习之间。需要注意的是，监督学习和非监督学习从一开始就是相对的，而强化学习在提出时并没有从训练样本歧义性的角度考虑其与监督学习和非监督学习的区别，因此，一些早期的研究中把强化学习视为一种特殊的非监督学习。[来源](http://blog.sina.com.cn/s/blog_95c4c1170102whjk.html)