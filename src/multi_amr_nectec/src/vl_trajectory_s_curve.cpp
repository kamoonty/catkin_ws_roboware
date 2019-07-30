#include "ros/ros.h"
#include "geometry_msgs/Point.h"
#include <geometry_msgs/Twist.h>


int main(int argc, char **argv)
{
  // ROS objects
  ros::init(argc, argv, "vl_trajectory_s_curve");
ros::NodeHandle nh;
ros::Publisher vl_cmd_vel_pub = nh.advertise<geometry_msgs::Twist>("vl_robot/cmd_vel", 1000);
ros::Rate loop_rate(100);
geometry_msgs::Twist final_cmd_vel; 
int i;
float t;
while (ros::ok())
  { t=i*0.01;
  if (t>=2&&t<17) //delay for 15 secs
    {final_cmd_vel.linear.x=0.5;
   final_cmd_vel.angular.z=-0.2;
    ROS_INFO("First half circle");
    }   
  else if (t>=17&&t<32) //specify time here
   {final_cmd_vel.linear.x=0.5;
  final_cmd_vel.angular.z=0.2;
        ROS_INFO("Second First half circle");}       

  if(t>=32)
  {final_cmd_vel.linear.x=0;
  final_cmd_vel.angular.z=0;
        ROS_INFO("End");}     
    
     i=i+1;    
    vl_cmd_vel_pub.publish(final_cmd_vel) ;
    ros::spinOnce();
    loop_rate.sleep();

  }


  //return 0;
}