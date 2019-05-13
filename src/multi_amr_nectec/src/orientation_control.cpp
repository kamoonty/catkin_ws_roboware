#include <ros/ros.h>
//#include <std_msgs/Float32.h>
//#include <geometry_msgs/Point32.h>

#include <stdlib.h>
#include "nav_msgs/Odometry.h"
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Quaternion.h>

geometry_msgs::Point robot_pos; //float 64 inside
geometry_msgs::Quaternion robot_quat;

void odomCallback(const nav_msgs::Odometry::ConstPtr& odom)
{ 
  robot_pos.x=odom->pose.pose.position.x;
  robot_pos.y=odom->pose.pose.position.y;
  robot_pos.z=0; // ground robot

  robot_quat.x=odom->pose.pose.orientation.x;
  robot_quat.y=odom->pose.pose.orientation.y;
  robot_quat.z=odom->pose.pose.orientation.z;
  robot_quat.w=odom->pose.pose.orientation.w;
  // it declare in quantanion not Row pitch yaw
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "Robot_odom");
    ros::NodeHandle nh;   
    ros::Subscriber sub = nh.subscribe("odom", 1000, odomCallback);
    ros::Publisher robot_quat_pub = nh.advertise<geometry_msgs::Quaternion>("pub_quat", 1000);    
    
    ros::Publisher force0_pub = nh.advertise<geometry_msgs::Twist>("amr_0/cmd_vel", 1000);
    ros::Publisher force1_pub = nh.advertise<geometry_msgs::Twist>("amr_1/cmd_vel", 1000); 
    ros::Publisher force2_pub = nh.advertise<geometry_msgs::Twist>("amr_2/cmd_vel", 1000);
    ros::Publisher force3_pub = nh.advertise<geometry_msgs::Twist>("amr_3/cmd_vel", 1000);



    ros::Rate loopRate(20);
	while (ros::ok()) 
{   
    robot_quat_pub.publish(robot_quat);
	ros::spinOnce();
    loopRate.sleep();
}
	//return 0;
}
