#include <ros/ros.h>
#include <dynamic_reconfigure/server.h>
// MyParamsConfig = MyParams + Config, MyParams前缀与MyParams.cfg最后一行的第三个参数对应
#include <my_dyn_rec_demo/MyParamsConfig.h>


void callback(my_dyn_rec::MyParamsConfig& config, uint32_t level)
{
	ROS_INFO("New values: [%d] - [%s]", config.int_param, config.str_param.c_str());
}


int main(int argc, char** argv)
{
	ros::init(argc, argv, "my_node");

	// my_dyn_rec： 动态配置文件生成的 PACKAGE NAME
	// MyParamsConfig = MyParams + Config, MyParams前缀与MyParams.cfg最后一行的第三个参数对应
	dynamic_reconfigure::Server<my_dyn_rec::MyParamsConfig> server;
	dynamic_reconfigure::Server<my_dyn_rec::MyParamsConfig>::CallbackType f;
	
	f = boost::bind(&callback, _1, _2);
	server.setCallback(f);

	ros::spin();
	
	return 0;
}
