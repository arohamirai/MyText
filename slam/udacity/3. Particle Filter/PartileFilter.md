# Particle Filter

##1. Resampling wheel
```
##  功能： 实现按样本权重值大小有放回的重抽样
# p 表示样本集合
# w 表示样本集合中对应样本的权重
p_temp = []
index = int(random.random()*N)
beta = 0.0
mw = max(w)
for i in range(N):
	bata += random.random()*2 * mw
	while beta > w[index]
		beta -= w[index]
		index = (index + 1) % N
	p_temp.append(p[index])

p = p_temp
```