ros 多回调队列的一种应用场景

```
#include <ros/spinner.h>
#include <ros/callback_queue.h>

#include <std_msgs/Header.h>
#include <std_msgs/String.h>

// callbacks to be added to internal ROS queue
void headerCallback(const std_msgs::Header::ConstPtr& msg)
{
  ROS_INFO("stamp.sec: %d", msg->stamp.sec);
}

// callbacks to be added to user queue
void stringCallback(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("string: %s", msg->data.c_str());
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "my_queues");

  ros::NodeHandle n;
  // nothing special for internal ROS queue
  ros::Subscriber sub1 = n.subscribe("/header_topic", 10, headerCallback);

  // define user callback queue
  ros::CallbackQueue string_queue;
  // create options for subscriber and pass pointer to our custom queue
  ros::SubscribeOptions ops =
    ros::SubscribeOptions::create<std_msgs::String>(
      "/string_topic", // topic name
      10, // queue length
      stringCallback, // callback
      ros::VoidPtr(), // tracked object, we don't need one thus NULL
      &string_queue // pointer to callback queue object
    );
  // subscribe
  ros::Subscriber sub2 = n.subscribe(ops);

  // spawn async spinner with 1 thread, running on our custom queue
  ros::AsyncSpinner async_spinner(1, &string_queue);
  // start the spinner
  async_spinner.start();

  while (ros::ok())
  {
    // process one message from ROS internal queue
    ros::spinOnce();
    ROS_INFO("Press Enter to process available messages from ROS internal queue");
    // wait for user input
    getchar();
  }

  return 0;
}
```