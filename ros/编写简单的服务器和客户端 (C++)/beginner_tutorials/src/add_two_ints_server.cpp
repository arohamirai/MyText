#include "ros/ros.h"
// beginner_tutorials/AddTwoInts.h是由编译系统自动根据我们先前创建的 srv 文件生成的对应该 srv 文件的头文件
#include "beginner_tutorials/AddTwoInts.h"

// 这个函数提供两个int值求和的服务，int值从request里面获取，而返回数据装入response内，这些数据类型都定义在srv文件内部，函数返回一个boolean值。
bool add(beginner_tutorials::AddTwoInts::Request  &req,
		beginner_tutorials::AddTwoInts::Response &res)
    {
      res.sum = req.a + req.b;
      ROS_INFO("request: x=%ld, y=%ld", (long int)req.a, (long int)req.b);
      ROS_INFO("sending back response: [%ld]", (long int)res.sum);
      return true;
    }

int main(int argc, char **argv)
    {
      ros::init(argc, argv, "add_two_ints_server");
      ros::NodeHandle n;

      ros::ServiceServer service = n.advertiseService("add_two_ints", add);
      ROS_INFO("Ready to add two ints.");
      ros::spin();

      return 0;
	}
