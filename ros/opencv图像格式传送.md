#1. 发送端：
···
	ros::Publisher image_pub_;
	
	// 读入OpenCV格式图像
	Mat map = imread("path-to-image",1);
	sensor_msgs::ImagePtr p_image_msg;	
	p_image_msg =
          cv_bridge::CvImage(std_msgs::Header(), "mono16", map).toImageMsg();
	sensor_msgs::Image image;
	image_pub_.publish(image);
···

#2. 接收端
···
	// 接收端回掉函数
	void handleImageCallback(const sensor_msgs::ImagePtr& image_msg)
	{
		cv_bridge::CvImagePtr p_image;
		p_image = cv_bridge::toCvCopy(*image_msg,
                                "mono16");
		Mat& image = p_image->image;
		cv::imshow("image",image);
		cv::waitKey(2);
	}
	
	ros::Subcriber image_sub_;
	

···