#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <boost/lexical_cast.hpp>
#include <std_msgs/Float32.h>
#include <geometry_msgs/Point32.h>
#include <geometry_msgs/Twist.h>
#include <stdlib.h> 

geometry_msgs::Point32 get_robo_pos;


void robot_pos_Callback(const geometry_msgs::Point32 &robot_pos)
{float x= 5;
  ROS_INFO("Robot pos  %.3f",x);

}

int main(int argc, char** argv) {
 ros::init(argc, argv, "vl_force");
 ros::NodeHandle nh;
 ros::Subscriber robot_pos_sub = nh.subscribe("robot_pos", 1000, robot_pos_Callback);




  ros::spin();

  return 0;


}
