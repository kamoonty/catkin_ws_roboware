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
  if (t>=2&&t<12) //10 secs
     {final_cmd_vel.linear.y=0.2;
   final_cmd_vel.linear.x=0;
    ROS_INFO("Sideways +Y");}      
  else if (t>=12&&t<42) // Straight
  {final_cmd_vel.linear.x=0.2;
    final_cmd_vel.linear.y=0;
    ROS_INFO("Go straight");}       
  else if (t>=42&&t<52) //Sideway
    {final_cmd_vel.linear.y=-0.2;
   final_cmd_vel.linear.x=0;
    ROS_INFO("Sideways -Y");} 
   
  else if(t>=52)
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