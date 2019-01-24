#2018.06.06
##1. tf2:doTransform()
功能：ros中PointCloud2坐标系间变换
例程：
```
  geometry_msgs::TransformStamped sensor2base_stamped;
  while (1)
  {
    try
    {
      sensor2base_stamped =
          tfBuffer_.lookupTransform("base_footprint", "laser_link", ros::Time::now());
    }
    catch (tf2::TransformException& ex)
    {
      ROS_WARN_THROTTLE(1, "sensor2base_stamped: %s", ex.what());
      continue;
    }
    break;
  }
  sensor_msgs::PointCloud2 couldInBase;
  // couldInSensor 为传入的sensor_msgs::PointCloud2 类型点云
  tf2::doTransform(couldInSensor,couldInBase,sensor2base_stamped );
```
##2. ros查询tf后变换关系相乘
1. ros 查询到的tf是`geometry_msgs::TransformStamped`类型，不能直接进行乘法运算，必须先转换成`Eigen::Affine3d`类型才能进行直接乘法，转换代码如下：
```
	#include"tf2_eigen/tf2_eigen.h"
	
	geometry_msgs::TransformStamped base2odom_stamped;
	try
      {
        base2odom_stamped =
            tfBuffer_.lookupTransform("odom", "base_footprint", ros::Time::now());
      }
      catch (tf2::TransformException& ex)
      {
        ROS_WARN_THROTTLE(1, "base2odom_stamped: %s", ex.what());
        lookup_tf_success = false;
        //return;
      }
	// 转换
	Eigen::Affine3d base2odom = tf2::transformToEigen(base2odom_stamped);
```
2. `geometry_msgs::Pose`类型用于变换相乘，同样要先转换为`Eigen::Affine3d`类型，转换如下：
```
geometry_msgs::Pose initial_pose_;
Eigen::Affine3d base2world;
// 转换
tf2::fromMsg(initial_pose_, base2world);
```
##3. ros中时间
1. `ros::Time(0)` 表示最新时间，但如果这是传给`lookupTransform`函数的话，得到的结果时间戳为0，所以最好避免用`ros::Time(0)`，一律用`ros::Time::now()`.
2. ros时间变换成以秒为单位：`ros::Time::now().toSec()`，求以秒为单位的时间间隔类似，只要把`ros::Time`类型的时间相减，再做`.toSec()`操作。
##4. 迭代点云，修改点云
```
/*
* 激光数据回调函数
* void CartographerFrontEndServer::handleLaserScan(sensor_msgs::LaserScan scan)
* 部分代码
*/

  sensor_msgs::PointCloud2 couldInSensor;
  couldInSensor.header = scan.header;
  couldInSensor.width = 3;
  couldInSensor.height = 1;

  double angle_increment = scan.angle_increment;
  double angle_min = scan.angle_min;
  int range_size = scan.ranges.size();

  sensor_msgs::PointCloud2Modifier modifier(couldInSensor);
  modifier.setPointCloud2Fields(3, "x", 1, sensor_msgs::PointField::FLOAT32,
                                "y", 1, sensor_msgs::PointField::FLOAT32,
                                "z", 1, sensor_msgs::PointField::FLOAT32);
  modifier.resize(range_size);

  sensor_msgs::PointCloud2Iterator<float> iter_x(couldInSensor, "x");
  sensor_msgs::PointCloud2Iterator<float> iter_y(couldInSensor, "y");
  sensor_msgs::PointCloud2Iterator<float> iter_z(couldInSensor, "z");

  for (int i = 0; i < range_size; i++)
  {
    double range = scan.ranges[i];
    float radian = i * angle_increment + angle_min;

    *iter_x = range* cos(radian);
    *iter_y = range* sin(radian);
    *iter_z = 0;

    ++iter_x;
    ++iter_y;
    ++iter_z;
  }
```
##4. Matlab中四元数、欧拉角、旋转矩阵的变换函数
```
// 用R表示旋转矩阵，yaw pitch roll分别表示Z　Y　X轴的转角(需要注意的是，两者并不一定是这种对应关系)，q=[q0,q1,q2,q3]'表示单位四元数，排序方式(w,x,y,z)
// S为旋转顺序，取值：'ZYX','XYZ'...
// 但凡涉及到S的地方，参数排序跟S相同，例如：angle2quat(r1,r2,r3，S);如果S='ZYX'，则r1 = yaw, r2 = pitch, r3 = roll
// r 表示欧拉角
// 角度均为弧度制

// 欧拉角到旋转矩阵
R=angle2dcm(r1,r2,r3,S); 
// 欧拉角到四元数
[q0 q1 q2 q2]=angle2quat(r1,r2,r3，S);

// 旋转矩阵到欧拉角
[r2,r2,r3]=dcm2angle(R, S);
// 旋转矩阵到四元数
[q0 q1 q2 q2]=dcm2quat(R);

// 四元数到旋转矩阵
R=quat2dcm([q0 q1 q2 q3]);
// 四元数到欧拉角
[r1,r2,r3]=quat2angle([q0 q1 q2 q2]，S);
```
#2018.06.07
## 1. Eigen 中各种变换关系
```
// Eigen 几何模块
#include <Eigen/Geometry>

/********** 类型定义 **********/
Eigen::Vector3d euler_angles;			// 欧拉角
Eigen::AngleAxisd rotation_vector;		// 旋转向量
Eigen::Matrix3d rotation_matrix;		// 旋转矩阵
Eigen::Quaterniond q;					// 四元数，排序方式(w,x,y,z)

/********** 欧拉角 **********/
// 欧拉角 ————> 旋转向量
rotation_vector = Eigen::AngleAxisd(euler_angles, ::Eigen::Vector3d::UnitZ())		// 此处绕Z旋转
// 欧拉角 ————>  旋转向量 ————> 旋转矩阵
rotation_vector = Eigen::AngleAxisd(euler_angles, ::Eigen::Vector3d::UnitZ())		// 此处绕Z旋转
rotation_matrix =rotation_vector.matrix();
// 欧拉角组 ————> 旋转向量组 ————> 旋转矩阵
euler_angles(yaw,pitch,roll);				// 此处yaw,pitch,roll旋转轴分别为Z,Y,X
rotation_matrix = Eigen::AngleAxisd(euler_angles[0], ::Eigen::Vector3d::UnitZ())
    * Eigen::AngleAxisd(euler_angles[1], ::Eigen::Vector3d::UnitY())
    * Eigen::AngleAxisd(euler_angles[2], ::Eigen::Vector3d::UnitX());
// 欧拉角组 ————> 旋转向量组 ————> 旋转矩阵 ————> 四元数
euler_angles(yaw,pitch,roll);				// 此处yaw,pitch,roll旋转轴分别为Z,Y,X
rotation_matrix = Eigen::AngleAxisd(euler_angles[0], ::Eigen::Vector3d::UnitZ())
    * Eigen::AngleAxisd(euler_angles[1], ::Eigen::Vector3d::UnitY())
    * Eigen::AngleAxisd(euler_angles[2], ::Eigen::Vector3d::UnitX());
q = Eigen::Quaterniond ( rotation_matrix );


/********** 旋转向量 **********/
// 旋转向量 ————> 欧拉角
rotation_vector.angle();
// 旋转向量 ————> 旋转矩阵
rotation matrix =rotation_vector.matrix();
// 旋转向量 ————>四元数
q = Eigen::Quaterniond ( rotation_vector );
// 旋转向量组 ————> 旋转矩阵
euler_angles(yaw,pitch,roll);				// 此处yaw,pitch,roll旋转轴分别为Z,Y,X
rotation_matrix = Eigen::AngleAxisd(euler_angles[0], ::Eigen::Vector3d::UnitZ())
    * Eigen::AngleAxisd(euler_angles[1], ::Eigen::Vector3d::UnitY())
    * Eigen::AngleAxisd(euler_angles[2], ::Eigen::Vector3d::UnitX());
// 旋转向量组 ————> 旋转矩阵 ————> 四元数
rotation_matrix = Eigen::AngleAxisd(euler_angles[0], ::Eigen::Vector3d::UnitZ())
    * Eigen::AngleAxisd(euler_angles[1], ::Eigen::Vector3d::UnitY())
    * Eigen::AngleAxisd(euler_angles[2], ::Eigen::Vector3d::UnitX());
q = Eigen::Quaterniond ( rotation_matrix );


/********** 旋转矩阵 **********/
// 旋转矩阵 ————>欧拉角组
Eigen::Vector3d euler_angles = rotation_matrix.eulerAngles ( 2,1,0 ); // ZYX顺序，即roll pitch yaw顺序
// 旋转矩阵 ————>旋转向量
rotation_vector.fromRotationMatrix(rotation_matrix);		// AngleAxisd类实现的方法，rotation_vector包含旋转向量轴的信息
// 旋转矩阵 ————>四元数
q = Eigen::Quaterniond ( rotation_matrix );


/********** 四元数 **********/
// 四元数 ————> 旋转矩阵 ————>旋转向量 ———> 欧拉角
rotation_matrix = q.toRotationMatrix();
rotation_vector.fromRotationMatrix(rotation_matrix);		// AngleAxisd类实现的方法，rotation_vector包含旋转向量轴的信息
rotation_vector1.angle();
// 四元数 ————> 旋转矩阵 ————> 旋转向量
rotation_matrix = q.toRotationMatrix();
rotation_vector.fromRotationMatrix(rotation_matrix);		// AngleAxisd类实现的方法，rotation_vector包含旋转向量轴的信息
// 四元数 ————> 旋转矩阵
rotation_matrix = q.toRotationMatrix();
```
# 2018.06.11
## 1. size_t 类型格式化输出符
[%zu 或 %lu](https://www.sigmainfy.com/blog/size_t_printf.html)

#2018.06.12
## 1. opencv图像类型和ros图像类型转换
```
// ros to opencv
cv::Mat image_cv;
sensor_msgs::CompressedImage image_ros_Compress;

cv_bridge::CvImagePtr p_image;
p_image = cv_bridge::toCvCopy(image_ros_Compress,
                                "mono8");
image_cv = p_image->image;
// or
sensor_msgs::Image image_ros;
cv_bridge::CvImagePtr p_image = cv_bridge::toCvCopy(image_ros,
                                                      "mono16");
image_cv = p_image->image;

// opencv to ros
sensor_msgs::CompressedImagePtr p_comressed_image_msg;
p_comressed_image_msg =
    cv_bridge::CvImage(std_msgs::Header(), "mono8", image_cv)
	.toCompressedImageMsg();
// or
 sensor_msgs::ImagePtr p_image_msg;
  p_image_msg =
      cv_bridge::CvImage(std_msgs::Header(), "mono16", image_cv).toImageMsg();


```
# 2018.06.14
1. circusctl start/stop [node_name] 可以代替网页5000端口开启/关闭节点

# 2018.07.03
1. 多播/组播(multicast)
多播的地址是特定的，D类地址用于多播。D类IP地址就是多播IP地址，即224.0.0.0至239.255.255.255之间的IP地址，并被划分为局部连接多播地址、预留多播地址和管理权限多播地址3类： 
局部多播地址：在224.0.0.0～224.0.0.255之间，这是为路由协议和其他用途保留的地址，路由器并不转发属于此范围的IP包。 
预留多播地址：在224.0.1.0～238.255.255.255之间，可用于全球范围（如Internet）或网络协议。 
管理权限多播地址：在239.0.0.0～239.255.255.255之间，可供组织内部使用，类似于私有IP地址，不能用于Internet，可限制多播范围。

#2018.07.05
1. ibvs_constrained 中相机projWidth, projHeight, objWidth, objHeight的参数选择过程：
	* 选择objWidth或objHeight, 另一个根据相机图像长宽比例换算
	* objWidth, objHeight 乘上一个比例2.778, 得到projWidth, projHeight, 2.778可以认为是视野与算法速度的最佳分辨率
	* 算出的projWidth, projHeight取整到4的倍数，最好是8的倍数，为了字节对齐，再除于2.778， 反算objWidth, objHeight
	* 重复上述过程，直到视野满足要求

#2018.07.06
ros subscribe的实现函数必须是const参数，如下：
```
void FollowLineRecord::handleResult(const visual_servo_msgs::IbvsConstrainedResultConstPtr &result)
```

# 2018.07.19
	1. 已知平移向量和四元数，求Eigen::Affine3d 类型初始化：
	```
	Eigen::Quaterniond q;//已知
	Eigen::Vector3d t;//已知
	Eigen::Affine3d translate;// 待求
	
	translate.setIdentity();
    translate.prerotate(q1);
    translate.pretranslate(t1);
	```
	2. Eigen的数据使用时最好都先初始化下，或setIdentity()下；
	
	3. 当不知道旋转轴时，又想知道旋转角度，可以用SVD方式分解，自动求解旋转轴
	```
	Eigen::Affine3d translate;// 已知
	double angle； // 待求
	Eigen::AngleAxisd angle_1 = Eigen::AngleAxisd(base2base.rotation());
	angle = angle_1.angle();
	```
	
	4. 强制杀死僵尸程序:使用 kill -9 <pid> 系统命令
	
	```
	/*
	系统命令：ps aux | grep apriltag_detector | grep -v grep | awk '{print $2}'
	ps aux：显示所有进程，详细信息
	grep apriltag_detector： 过滤， 只留下apriltag_detector 进程信息
	grep -v grep： 忽略掉grep进程
	awk： 数据流处理
	print $2：打印 每行中的第二个字段
	*/
	
	
	
			FILE* fp2;
            int pid;
            char pid_buf[PIPE_BUF];
            if ((fp2 = popen("ps aux | grep apriltag_detector | grep -v grep | awk '{print $2}'", "r")) == NULL)
            {
              ROS_ERROR("popen failed!");
              // err_quit("popen");
            }
            while ((fgets(pid_buf, PIPE_BUF, fp2)) != NULL)
            {
              pid = atoi(pid_buf);
              std::string command = "kill -9 " + std::to_string(pid);
              status = system(command.c_str());
              assert(status != -1);
            }
            pclose(fp2);
	```
# 2018.7.23
	1. `Eigen::Isometry2d `二维旋转初始化
	```
		Eigen::Isometry2d laser2template_;
		laser2template_.setIdentity();
		laser2template_.prerotate(Eigen::Rotation2Dd(output_.x[2]));
		laser2template_.pretranslate(
        Eigen::Vector2d(output_.x[0], output_.x[1]));
	```
	
	2. `Eigen::Isometry3d` 转`Eigen::Isometry2d`
	```
		Eigen::Affine2d laser2base_;
		Eigen::Affine3d laser2base = tf2::transformToEigen(laser2base_stamped);
		double yaw = GetYaw(Eigen::Quaterniond(laser2base.rotation()));

		laser2base_.setIdentity();
		laser2base_.prerotate(Eigen::Rotation2Dd(yaw));
		laser2base_.pretranslate(
        Eigen::Vector2d(laser2base(0, 3), laser2base(1, 3)));
	```
	3. [ROS参数服务器有两个版本，分别为:](https://www.ncnynl.com/archives/201702/1295.html)
	（1）NodeHandle版本，ros::NodeHandle::getParam()，参数相对于NodeHandle的命名空间进行解析;
	（2）bare版本：ros::param::get()， 参数相对于节点的命名空间进行解析;
	```
	//
	ros::NodeHandle::getParam();
	```
	
# 2018.7.26
	1. ros动态参数文件找不到.h文件:
	首先看是不是数据类型没有拼对，如果对，则在CMakeLists.txt 中，add_executable(node_name ${PROJECT_SOURCE_DIR}/src/node_name.cpp) 后面添加add_dependencies(node_name ${PROJECT_NAME}_gencfg)，表示需要依赖动态参数配置文件，例如
	```
	add_executable(scan_filter ${PROJECT_SOURCE_DIR}/src/scan_filter.cpp)
	target_link_libraries(scan_filter ${catkin_LIBRARIES} ${Boost_LIBRARIES} ${OpenCV_LIBRARIES})
	# make sure configure headers are built before any node using them
	add_dependencies(scan_filter ${PROJECT_NAME}_gencfg)
	```
	2. ros找不到msg的头文件：
	首先看是不是数据类型没有拼对，如果对，则在CMakeLists.txt 中，add_executable(node_name ${PROJECT_SOURCE_DIR}/src/node_name.cpp) 或add_library(...) 后面添加add_dependencies(node_name ${PROJECT_NAME}_gencpp)，表示需要本项目的msg文件，例如
	```
	add_library(CNatNetClient ${PROJECT_SOURCE_DIR}/src/CNatNetClient.cpp)
add_dependencies(CNatNetClient ${PROJECT_NAME}_gencpp)

add_executable(sensors_check_server src/SensorsCheckServer.cpp)
target_link_libraries(sensors_check_server
${catkin_LIBRARIES}
CNatNetClient
)
add_dependencies(sensors_check_server ${PROJECT_NAME}_gencpp)
	```
	3. ros找不到action的头文件：
	首先看是不是数据类型没有拼对，如果对，则在CMakeLists.txt 中，add_executable(node_name ${PROJECT_SOURCE_DIR}/src/node_name.cpp) 或add_library(...) 后面添加add_dependencies(node_name ${${PROJECT_NAME}_EXPORTED_TARGETS})，表示需要本项目的action文件，例如
	```
	add_dependencies(sensors_check_server
    ${PROJECT_NAME}_gencpp
    ${${PROJECT_NAME}_EXPORTED_TARGETS}
    ${catkin_EXPORTED_TARGETS})
	```

	4. boost:bind()当绑定类成员函数时，第二个参数一定是类对象的指针，即this指针，只有这样，boost::bind()才能找到成员函数的地址。静态成员函数除外。
	
# 2018.8.6
	1. 相机第一帧参数接近单位矩阵

# 2018.08.14
## 1. 三维旋转矩阵的全公式形式：
```
syms yaw pitch roll
rot_x = [1 0 0 0; 0 cos(roll) -sin(roll) 0; 0 sin(roll) cos(roll) 0; 0 0 0 1];
rot_y = [cos(pitch) 0 sin(pitch) 0; 0 1 0 0; -sin(pitch) 0 cos(pitch) 0; 0 0 0 1];
rot_z = [cos(yaw) -sin(yaw) 0 0; sin(yaw) cos(yaw) 0 0; 0 0 1 0; 0 0 0 1];

rot_zyx = rot_z * rot_y * rot_x
```
![image](http://ws4.sinaimg.cn/large/006H1aMCly1fu9e133xgdj30s50d9wez.jpg)

# footprint
EMMA200的footprint:
[[-0.42,-0.29],[-0.42,0.29],[0.42,0.29],[0.42,-0.29]]

# 2018.10.10
## 1. ros中坐标变换相关定义
parent/frame_id：表示父坐标
child/child_frame_id:表示子坐标

在tf树上，箭头由parent指向child，但在发布变换关系时，值应该是child2parent的值，也就是说，两者的箭头应该是相反的。例如
```
// 值因该是servo_target2base_footprint
vpTranslationVector t;
vpQuaternionVector q;
eMo.extract(t);
eMo.extract(q);
geometry_msgs::TransformStamped stamped_transform;
stamped_transform.header.stamp = ros::Time::now();
stamped_transform.header.frame_id = "base_footprint";
stamped_transform.child_frame_id = "servo_target";
stamped_transform.transform.translation.x = t[0]*0.001;
stamped_transform.transform.translation.y = t[1]*0.001;
stamped_transform.transform.translation.z = t[2]*0.001;
stamped_transform.transform.rotation.x = q.x();
stamped_transform.transform.rotation.y = q.y();
stamped_transform.transform.rotation.z = q.z();
stamped_transform.transform.rotation.w = q.w();
```

## 2. rviz 显示轨迹
rviz中订阅nav_msgs::Odometry消息，可以记录轨迹，而且frame_id和child_frame_id间不需要tf,但这时可能需要在rviz中手填fix_frame为frame_id。

示例
```
// fix_frame:test_world
void pubTestOdom(const vpHomogeneousMatrix& wMe, const geometry_msgs::Twist& vel)
{
  geometry_msgs::Pose base2world_pose;
  nav_msgs::Odometry base2world_odom;
  vpTranslationVector t;
  vpQuaternionVector q;

  wMe.extract(t);
  wMe.extract(q);
  base2world_pose.position.x = t[0] * 0.001;
  base2world_pose.position.y = t[1] * 0.001;
  base2world_pose.position.z = t[2] * 0.001;
  base2world_pose.orientation.x = q.x();
  base2world_pose.orientation.y = q.y();
  base2world_pose.orientation.z = q.z();
  base2world_pose.orientation.w = q.w();

  base2world_odom.header.stamp = ros::Time::now();
  base2world_odom.header.frame_id = "test_world";
  base2world_odom.child_frame_id = "test_base";
  base2world_odom.pose.pose = base2world_pose;
  base2world_odom.twist.twist = vel;

  debug_base_odom_pub_.publish(base2world_odom);
}
```

## 3. OpenGL变换框架
![image](http://wx1.sinaimg.cn/large/006H1aMCgy1fwq11rkddzj30rs0hf3yq.jpg)
	
# 2019.01.15
   数据变换
   ```
#include <tf_conversions/tf_eigen.h>
#include <eigen_conversions/eigen_msg.h>
   ```
   
# 2019.01.24
## 1. ros离线跑bag
1. launch文件中添加 `/use_sim_time` 字段，设为`true`
```
<launch>
    <param name="/use_sim_time" value="true" />
	...
	
</launch>
```
2. 发布时钟
```
rosbag play xxx --clock
```