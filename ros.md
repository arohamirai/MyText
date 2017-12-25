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

	