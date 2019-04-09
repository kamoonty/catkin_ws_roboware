#include "ros/ros.h"
#include "beginner_tutorials/my_msg.h"

void clbk(const beginner_tutorials::my_msg::ConstPtr& msg) {
    //ROS_INFO("another filed %d", msg->another_field);
    for (int i = 0; i<11; i++)
    {
       ROS_INFO("Get point: x=%.2f, y=%.2f", msg->points[i].x, msg->points[i].y);
       ROS_INFO("----------------");
    }
    
}
   

int main(int argc, char **argv)
{
  // ROS objects
  ros::init(argc, argv, "my_subscriber");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("my_topic", 1, clbk);

  ros::spin();

}