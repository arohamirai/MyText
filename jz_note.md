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
// 用R表示旋转矩阵，yaw pitch roll分别表示Z　Y　X轴的转角，q=[q0,q1,q2,q3]'表示单位四元数，排序方式(w,x,y,z)
// S为旋转顺序，取值：'ZYX','XYZ'...
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
##1. Eigen 中各种变换关系
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
Eigen::AngleAxisd(euler_angles, ::Eigen::Vector3d::UnitZ())		// 此处绕Z旋转
// 欧拉角 ————>  旋转向量 ————> 旋转矩阵
Eigen::AngleAxisd(euler_angles, ::Eigen::Vector3d::UnitZ())		// 此处绕Z旋转
rotation matrix =rotation_vector.matrix();
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
rotation_vector1.angle();
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
