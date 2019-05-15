#include "ros/ros.h"
//#include "beginner_tutorials/my_msg.h"
#include <geometry_msgs/Point.h>
#include <geometry_msgs/PoseStamped.h>
#include <std_msgs/Float32.h>
#include <nav_msgs/Path.h>

geometry_msgs::Point get_path[1000];
geometry_msgs::PoseStamped get_PoseStamped;
nav_msgs::Path gPlan;

void record_pathCB(const nav_msgs::Path::ConstPtr& path)
{   int i=0;
    for(i=0;i<500;i++)
    {
    get_path[i].x=path->poses[i].pose.position.x;
    get_path[i].y=path->poses[i].pose.position.y;
    }
}

int main(int argc, char **argv)
{ int i=0;
  // ROS objects
  ros::init(argc, argv, "subscribe_path");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("vl_robot/move_base/NavfnROS/plan", 1000, record_pathCB); 
  ros::Publisher path_pub = n.advertise<geometry_msgs::Point>("G_path", 1000);

 ros::Rate loop_rate(1);
while (ros::ok())
  {
    
    for(i=0;i<500;i++)
    {
    ROS_INFO("path x,y =[%f,%f]",get_path[i].x,get_path[i].y);
    }

    //path_pub.publish(get_path);
    ros::spinOnce();

    loop_rate.sleep();
    
  }

}