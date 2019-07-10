#include "ros/ros.h"
#include "geometry_msgs/Point.h"
#include <geometry_msgs/Twist.h>


int main(int argc, char **argv)
{
  // ROS objects
  ros::init(argc, argv, "vl_trajectory_linear");
ros::NodeHandle nh;
ros::Publisher vl_cmd_vel_pub = nh.advertise<geometry_msgs::Twist>("vl_robot/cmd_vel", 1000);
ros::Rate loop_rate(100);
geometry_msgs::Twist final_cmd_vel; 
int i;
float t;
while (ros::ok())
  { t=i*0.01;
  if (t>=2&&t<=10) //deleay for 1 secs
  {final_cmd_vel.linear.x=0.5;
    ROS_INFO("Running with i=%d t=%f",i,t);
  }
  if (t>10) //specify time here
  {final_cmd_vel.linear.x=0;
        ROS_INFO("End of 10 secs");}     
     i=i+1;
        
    vl_cmd_vel_pub.publish(final_cmd_vel) ;

    ros::spinOnce();

    loop_rate.sleep();

  }


  //return 0;
}