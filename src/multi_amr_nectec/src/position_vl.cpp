/*
 *
 *  Created on: Apr 18, 2019
 *      Author: Kanin Soloist
 */

#include <ros/ros.h>
#include <std_msgs/Float32.h>
#include <geometry_msgs/Point32.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Twist.h>
#include <stdlib.h>
#include "multi_amr_nectec/pos_msg.h"
#include "nav_msgs/Odometry.h"

//multi_amr_nectec::pos_msg get_msg;
//nav_msgs::Odometry::ConstPtr get_odom;
geometry_msgs::Point vl_pos; //float 64 inside

void odomCallback(const nav_msgs::Odometry::ConstPtr& odom)
{ 
  vl_pos.x=odom->pose.pose.position.x;
  vl_pos.y=odom->pose.pose.position.y; 
 
  //ROS_INFO("Seq: [%d]", odom->header.seq);
  //ROS_INFO("get odom seq: [%d]", get_odom->header.seq);
/* ROS_INFO("Position-> x: [%f], y: [%f], z: [%f]", odom->pose.pose.position.x,odom->pose.pose.position.y, odom->pose.pose.position.z);
  ROS_INFO("Orientation-> x: [%f], y: [%f], z: [%f], w: [%f]", odom->pose.pose.orientation.x, odom->pose.pose.orientation.y, odom->pose.pose.orientation.z, odom->pose.pose.orientation.w);
  ROS_INFO("Vel-> Linear: [%f], Angular: [%f]", odom->twist.twist.linear.x,odom->twist.twist.angular.z);
   */
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "Virtual_Leader_pos");
    ros::NodeHandle nh;   
    ros::Publisher vl_pos_pub = nh.advertise<geometry_msgs::Point>("vl_pos", 1000);
    ros::Subscriber sub = nh.subscribe("odom", 1000, odomCallback);
    ros::Rate loopRate(100);
	while (ros::ok()) 
{  
   

    vl_pos_pub.publish(vl_pos); // pub virtual leader position 
    //ROS_INFO("Published VL pos %f, %f ",vl_pos.x,vl_pos.y);
	ros::spinOnce();
    loopRate.sleep();
}
	//return 0;
}

