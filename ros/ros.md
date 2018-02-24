# ROS
# 问答：
	1. 什么时候要source ~/catkin_ws/devel/setup.zsh?
		答： 每次打开新终端时。其作用是读取当前catkin工作空间的环境变量。因此最方便的方法是将其写入到~/.bashrc文件中

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
# 七. 理解ROS服务和参数
	1. ROS Services:服务（services）是节点之间通讯的另一种方式。服务允许节点发送请求（request） 并获得一个响应（response）。
		使用方法：
		rosservice list         输出可用服务的信息
		rosservice call         调用带参数的服务
		rosservice type         输出服务类型
		rosservice find         依据类型寻找服务find services by service type
		rosservice uri          输出服务的ROSRPC uri
	2. rosparam：rosparam使得我们能够存储并操作ROS 参数服务器（Parameter Server）上的数据。参数服务器能够存储整型、浮点、布尔、字符串、字典和列表等数据类型。rosparam使用YAML标记语言的语法。
		使用方法：
		rosparam set            设置参数
		rosparam get            获取参数
		rosparam get /			获取所有参数
		rosparam load           从文件读取参数
		rosparam dump           向文件中写入参数
		rosparam delete         删除参数
		rosparam list           列出参数名
	3. rosparam dump and rosparam load：参数保存与加载
		rosparam dump [file_name]
		rosparam load [file_name] [namespace]
# 八. 使用rqt_console和roslaunch
	1. rqt_console:属于ROS日志框架(logging framework)的一部分，用来显示节点的输出信息。
	2. rqt_logger_level:允许我们修改节点运行时输出信息的日志等级（logger levels）（包括 DEBUG、WARN、INFO和ERROR）。
	3. roslaunch:roslaunch可以用来启动定义在launch文件中的多个节点。
# 九. 1 消息(msg)和服务(srv)介绍

消息(msg): msg文件就是一个描述ROS中所使用消息类型的简单文本。它们会被用来生成不同语言的源代码。
服务(srv): 一个srv文件描述一项服务。它包含两个部分：请求和响应。 msg文件存放在package的msg目录下，srv文件则存放在srv目录下。 msg文件实际上就是每行声明一个数据类型和变量名。
# 十. 编写简单的消息发布器和订阅器 (C++)
  1. catkin_make --force-cmake:强制重新编译
# 十一. 编写简单的服务器和客户端 (C++)
	1. 服务跟节点是不一样的，服务类似于远程函数调用，节点相当于两个程序通信。
	2. 节点之间通过话题[topic]通信,服务端与客户端之间不需要话题。
# 十二. 录制与回放数据
 1. 录制数据（通过创建一个bag文件）：记录ROS系统运行时的话题数据（publisher的才能被记录），记录的话题数据将会累积保存到bag文件中。
	1.1 rosbag record -a:将当前发布的所有话题数据都录制保存到一个bag文件中,文件名以录制时间命名。
	1.2 rosbag record -O <subset_bagfile_name> <publisher name>:录制指定话题数据，-O参数告诉rosbag record将数据记录保存到名为subset_bagfile_name.bag的文件中，同时后面的话题参数告诉rosbag record只能录制指定的话题
	1.3 rosbag info <your bagfile>：录制的bagfile 文件包含信息。
	1.4 rosbag play <your bagfile>: 回放录制信息(-d, -r 参数控制等待时间、消息发布速率)
	1.5 rosbag record/play 命令的局限性:在前述部分中你可能已经注意到了turtle的路径可能并没有完全地映射到原先通过键盘控制时产生的路径上——整体形状应该是差不多的，但没有完全一样。造成该问题的原因是turtlesim的移动路径对系统定时精度的变化非常敏感。rosbag受制于其本身的性能无法完全复制录制时的系统运行行为，rosplay也一样。对于像turtlesim这样的节点，当处理消息的过程中系统定时发生极小变化时也会使其行为发生微妙变化，用户不应该期望能够完美的模仿系统行为。

# 十三. rviz
rviz ： The ROS Visualization Tool ，即机器人操作系统3D可视化工具。它的作用就是：一个虚拟世界，用来模拟机器人在现实世界的运行效果。简单的说它就是ROS的一个模拟器软件。
## rviz是用来干什么的，为什么要使用rviz：
你不需要用一个实际的机器人开始ROS学习。ROS包含了许多在虚拟环境中运行的机器人包，所以你可以在拥有真实世界的机器人前，在虚拟环境中测试您的程序。
在ROS中有3个可以模拟机器人的模拟器软件：
Gazebo
Stage
ArbotiX(就是RVIz)
你可以任选一个：
Gazebo：可以模拟出完整的现实世界，但是软件使用起来比较复杂。 
Stage：简单的2D模拟器，可以管理多个机器人和各种传感器，比如激光传感器。 
ArbotiX：它就是Rviz，它跟Gazebo软件比较，它不能模拟物理现象和没有传感器反馈。

