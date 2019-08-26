#include "ros/ros.h"
#include <stdlib.h> 
#include <std_msgs/Float32.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Twist.h>
#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"
#include "std_msgs/Float32MultiArray.h"


int team_size; //use for get param from launch file
float v_linear_threshold;
float v_angular_threshold;
float robot_mass;
float robot_inertia;
float robot_radious;
float delta_time;
geometry_msgs::Twist Fvl[10];
geometry_msgs::Twist Fij[10];
geometry_msgs::Twist F_rot[10];

int main(int argc, char **argv)
{
ros::init(argc, argv, "real_robot_straight");
ros::NodeHandle nh;
ros::Rate loopRate(50);
nh.getParam("real_robot_straight/team_size", team_size);
nh.getParam("real_robot_straight/v_linear_threshold",v_linear_threshold);
nh.getParam("real_robot_straight/v_angular_threshold",v_angular_threshold);
nh.getParam("real_robot_straight/robot_mass", robot_mass);
nh.getParam("real_robot_straight/robot_inertia", robot_inertia);
nh.getParam("real_robot_straight/robot_radious", robot_radious);
nh.getParam("real_robot_straight/delta_time", delta_time);

/*
ros::Subscriber Fij_sub = nh.subscribe("msg2", 1000, Fij_CB);
*/
ros::Publisher amr_0_cmd_vel_pub = nh.advertise<geometry_msgs::Twist>("amr_0/cmd_vel", 1000);
ros::Publisher amr_1_cmd_vel_pub = nh.advertise<geometry_msgs::Twist>("amr_1/cmd_vel", 1000); 

geometry_msgs::Twist final_cmd_vel [team_size];
//geometry_msgs::Point first_linear_v [team_size];
//geometry_msgs::Point second_linear_v [team_size];
 int i;
float t; 
while (nh.ok()) 
{
     final_cmd_vel[0].linear.x=-0.15;
   final_cmd_vel[1].linear.x=-0.15;
  
  

ROS_INFO("--------------------------");
amr_0_cmd_vel_pub.publish(final_cmd_vel[0]);
amr_1_cmd_vel_pub.publish(final_cmd_vel[1]);
ros::spinOnce();
loopRate.sleep(); 
}


//return 0;
}