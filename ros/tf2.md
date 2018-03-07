1. target frame，source frame，parent frame，child frame
	* source、target frame是在进行坐标变换时的概念，source是坐标变换的源坐标系，target是目标坐标系，这个时候，这个变换代表的是坐标变换。
	* parent、child frame是在描述坐标系变换时的概念，parent是原坐标系，child是变换后的坐标系，这个时候这个变换描述的是坐标系变换，也是child坐标系在parent坐标系下的描述。如果把child固结于一个刚体，那么这个变换描述的就是刚体在parent坐标系下的姿态。这个用处就大多了，可以用它来描述刚体的运动了。
	
2. tf树维护的坐标系之间的关系
