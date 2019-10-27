#include "ros/ros.h"
#include "geometry_msgs/Point.h"
#include <geometry_msgs/Twist.h>


int main(int argc, char **argv)
{
  // ROS objects
  ros::init(argc, argv, "vl_trajectory_c_shape");
ros::NodeHandle nh;
ros::Publisher vl_cmd_vel_pub = nh.advertise<geometry_msgs::Twist>("vl_robot/cmd_vel", 1000);
ros::Rate loop_rate(100);
geometry_msgs::Twist final_cmd_vel; 
int i=0;
float t=0;
while (ros::ok())
  { t=i*0.01;
  ROS_INFO("Time = %f ",t);
  if (t>=2&&t<7) 
     {final_cmd_vel.linear.y=-0.1;
   final_cmd_vel.linear.x=0;
    ROS_INFO("SIDEWAYS -Y");}      
  else if (t>=7&&t<17) 
  {final_cmd_vel.linear.x=0.1;
    final_cmd_vel.linear.y=0;
    ROS_INFO("Go straight");}       
  else if (t>=17&&t<24) 
    {final_cmd_vel.linear.y=0.1;
   final_cmd_vel.linear.x=0;
    ROS_INFO("Sideways +Y");} 
    else if (t>=24&&t<34) 
    {final_cmd_vel.linear.y=0;
   final_cmd_vel.linear.x=0.1;
    ROS_INFO("Go straightY");} 
  else if(t>=34)
  {final_cmd_vel.linear.x=0;
  final_cmd_vel.linear.y=0;
        ROS_INFO("End");}     
    
     i=i+1;    
    vl_cmd_vel_pub.publish(final_cmd_vel) ;
    ros::spinOnce();
    loop_rate.sleep();

  }


  //return 0;
}