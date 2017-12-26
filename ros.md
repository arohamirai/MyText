# ROS
# 二. ROS环境
	ROS_MASTER_URI:ROS结点管理器路径
	ROS_ROOT：ROS core packages路径
	ROS_PACKAGE_PATH:package和stack的路径
	PYTHONPATH：python解释器path
	
# 三. 文件系统
	1. Packages: 软件包，是ROS应用程序代码的组织单元，每个软件包都可以包含程序库、**可执行文件**、脚本或者其它手动创建的东西。
	2. Manifest (package.xml): 清单，是对软件包相关信息的描述,用于定义软件包相关元信息之间的依赖关系，这些信息包括版本、维护者和许可协议等。
	3. rospack允许你获取软件包的有关信息。(rospack find [包名称])
	4. roscd是rosbash命令集中的一部分，它允许你直接切换(cd)工作目录到某个软件包或者软件包子目录当中。(roscd [包名称])
	5. rosls是rosbash命令集中的一部分，它允许你直接按软件包的名称而不是绝对路径执行ls命令（罗列目录）。
	
# 四. 创建ROS程序包
	1. 一个程序包要想称为catkin程序包必须符合以下要求：
		* 该程序包必须包含catkin compliant package.xml文件;
		* 这个package.xml文件提供有关程序包的元信息;
		* 程序包必须包含一个catkin 版本的CMakeLists.txt文件，而Catkin metapackages中必须包含一个对CMakeList.txt文件的引用;
		* 每个目录下只能有一个程序包;
		* 这意味着在同一个目录下不能有嵌套的或者多个程序包存在。
	最简单的程序包也许看起来就像这样：
	![image](http://ws2.sinaimg.cn/large/006H1aMCgy1fmtb2rgupxj30h202pdfn.jpg)
	
	2. catkin_create_pkg命令创建新的package，如果有需要你还可以在后面添加一些需要依赖的其它程序包.(catkin_create_pkg <package_name> [depend1] [depend2] [depend3])
	3. catkin_make 是一个命令行工具，它简化了 catkin 的标准工作流程。你可以认为 catkin_make 是在 CMake 标准工作流程中依次调用了cmake 和 make；
		源代码在默认src目录中：catkin_make [make_targets] [-DCMAKE_VARIABLES=...]
		源代码在其他目录中：catkin_make --source [my_src]
	4. build 目录是build space的默认所在位置，同时cmake 和 make也是在这里被调用来配置并编译你的程序包。devel 目录是devel space的默认所在位置, 同时也是在你安装程序包之前存放可执行文件和库文件的地方。
# 五. 理解ROS节点
	1. 图的概念
		Nodes:节点,一个节点即为一个可执行文件，它可以通过ROS与其它节点进行通信。
		Messages:消息，消息是一种**ROS数据类型**，用于订阅或发布到一个话题。
		Topics:话题,节点可以发布消息到话题，也可以订阅话题以接收消息。
		Master:节点管理器，ROS名称服务 (比如帮助节点找到彼此)。
		rosout: ROS中相当于stdout/stderr。
		roscore: 主机+ rosout + 参数服务器 (参数服务器会在后面介绍)。
	2. 客户端库
		ROS节点可以使用ROS客户库与其他节点通信，ROS客户端库允许使用不同编程语言编写的节点之间互相通信:
		rospy = python 客户端库
		roscpp = c++ 客户端库
	3. rosnode
		rosnode list：列出活跃的节点
		rosnode info：命令返回的是关于一个特定节点的信息（rosnode info /rosout）
	4. rosrun
		rosrun 允许你使用包名直接运行一个**包内的节点**(而不需要知道这个包的路径)。(rosrun [package_name] [node_name] __name:=my_nodeName, 最后一个参数在想重命名节点名称时使用的)
# 六. 理解ROS话题
	1. 节点之间通过话题建立通信联系；
	2. rostopic:rostopic命令工具能让你获取有关ROS话题的信息.
		rostopic -h:使用选项帮助查看rostopic的子命令.
		rostopic echo [topic_name]:实时显示某个话题上发布的数据（节点图上将多加了一个新的订阅）
		rostopic list: 列出所有当前订阅和发布的话题。
		rostopic list -v: 显示出有关所发布和订阅的话题及其类型的详细信息。
		rostopic 的其他命令可以通过帮助查看(-h 参数)

	