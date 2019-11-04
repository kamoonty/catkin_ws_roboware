#include "ros/ros.h"
#include <stdlib.h> 
#include <std_msgs/Float32.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Twist.h>





ros::Publisher amr_0_cmd_vel_pub;
ros::Publisher amr_1_cmd_vel_pub;

void cmd_vel_CB(const geometry_msgs::Twist & cmd_vel)
{	geometry_msgs::Twist new_vel = cmd_vel;
// same velocity for two robots
amr_0_cmd_vel_pub.publish(new_vel);
amr_1_cmd_vel_pub.publish(new_vel);
}





int main(int argc, char **argv)
{
ros::init(argc, argv, "control_2_robot");
ros::NodeHandle nh;
ros::Rate loopRate(100);


amr_0_cmd_vel_pub = nh.advertise<geometry_msgs::Twist>("amr_0/cmd_vel", 1000);
amr_1_cmd_vel_pub = nh.advertise<geometry_msgs::Twist>("amr_1/cmd_vel", 1000); 
ros::Subscriber sub_cmd = nh.subscribe("cmd_vel",1000, cmd_vel_CB);
ros::spin();

return 0;


}