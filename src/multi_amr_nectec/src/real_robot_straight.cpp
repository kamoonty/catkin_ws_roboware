#include "ros/ros.h"
#include <stdlib.h> 
#include <std_msgs/Float32.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Twist.h>
#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"
#include "std_msgs/Float32MultiArray.h"



float v_linear_threshold;
float v_angular_threshold;


int main(int argc, char **argv)
{
ros::init(argc, argv, "real_robot_straight");
ros::NodeHandle nh;
ros::Rate loopRate(100);

nh.getParam("real_robot_straight/v_linear_threshold",v_linear_threshold);
//nh.getParam("real_robot_straight/v_angular_threshold",v_angular_threshold);



ros::Publisher amr_0_cmd_vel_pub = nh.advertise<geometry_msgs::Twist>("amr_0/cmd_vel", 1000);
ros::Publisher amr_1_cmd_vel_pub = nh.advertise<geometry_msgs::Twist>("amr_1/cmd_vel", 1000); 

geometry_msgs::Twist final_cmd_vel [2];

int i;
float t; 
while (nh.ok()) 
{
     final_cmd_vel[0].linear.x=v_linear_threshold;
   final_cmd_vel[1].linear.x=v_linear_threshold;
  
  

ROS_INFO("--------------------------");
amr_0_cmd_vel_pub.publish(final_cmd_vel[0]);
amr_1_cmd_vel_pub.publish(final_cmd_vel[1]);
ros::spinOnce();
loopRate.sleep(); 
}


//return 0;
}