#include <ros/ros.h>
//#include <std_msgs/Float32.h>
//#include <geometry_msgs/Point32.h>

//#include <geometry_msgs/Twist.h>
#include <stdlib.h>
#include "nav_msgs/Odometry.h"
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Quaternion.h>

geometry_msgs::Point robot_pos; //float 64 inside
geometry_msgs::Quaternion robot_quat;
geometry_msgs::Twist robot_velocity;

void odomCallback(const nav_msgs::Odometry::ConstPtr& odom)
{ 
  robot_pos.x=odom->pose.pose.position.x;
  robot_pos.y=odom->pose.pose.position.y;
  robot_pos.z=0; // ground robot

  robot_quat.x=odom->pose.pose.orientation.x;
  robot_quat.y=odom->pose.pose.orientation.y;
  robot_quat.z=odom->pose.pose.orientation.z;
  robot_quat.w=odom->pose.pose.orientation.w;
  
  robot_velocity.linear.x=odom->twist.twist.linear.x;
  robot_velocity.linear.y=odom->twist.twist.linear.y;
  robot_velocity.linear.z=odom->twist.twist.linear.z;
  // for omni rotation no need for x,y angular
  robot_velocity.angular.x=odom->twist.twist.angular.x;
  robot_velocity.angular.y=odom->twist.twist.angular.y;
  robot_velocity.angular.z=odom->twist.twist.angular.z;
  
  
  //ROS_INFO("Seq: [%d]", odom->header.seq);
  //ROS_INFO("get odom seq: [%d]", get_odom->header.seq);
/* ROS_INFO("Position-> x: [%f], y: [%f], z: [%f]", odom->pose.pose.position.x,odom->pose.pose.position.y, odom->pose.pose.position.z);
  ROS_INFO("Orientation-> x: [%f], y: [%f], z: [%f], w: [%f]", odom->pose.pose.orientation.x, odom->pose.pose.orientation.y, odom->pose.pose.orientation.z, odom->pose.pose.orientation.w);
  ROS_INFO("Vel-> Linear: [%f], Angular: [%f]", odom->twist.twist.linear.x,odom->twist.twist.angular.z);
   */
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "Robot_odom");
    ros::NodeHandle nh;   
    ros::Subscriber sub = nh.subscribe("odom", 1000, odomCallback);
    ros::Publisher robot_pos_pub = nh.advertise<geometry_msgs::Point>("pub_pos", 1000);    
    ros::Publisher robot_quat_pub = nh.advertise<geometry_msgs::Quaternion>("pub_quat", 1000);    
    ros::Publisher robot_velocity_pub = nh.advertise<geometry_msgs::Twist>("pub_velocity", 1000);    
   

    ros::Rate loopRate(20);
	while (ros::ok()) 
{  
    //ROS_INFO("Robot pos [%.3f,%.3f]",robot_pos.x,robot_pos.y);
    //ROS_INFO("Orientation x: [%.3f], y: [%.3f], z: [%.3f], w: [%.3f]",robot_quat.x,robot_quat.y,robot_quat.z,robot_quat.w);
    robot_pos_pub.publish(robot_pos);
    robot_quat_pub.publish(robot_quat);
    robot_velocity_pub.publish(robot_velocity);
   

	ros::spinOnce();
    loopRate.sleep();
}
	//return 0;
}
