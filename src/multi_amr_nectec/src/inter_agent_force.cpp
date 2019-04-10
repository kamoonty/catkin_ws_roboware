#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <boost/lexical_cast.hpp>
#include <std_msgs/Float32.h>
#include <geometry_msgs/Point32.h>
#include <geometry_msgs/Twist.h>
#include <stdlib.h> 
#include "multi_amr_nectec/pos_msg.h"

geometry_msgs::Point32 robot_pos [4];
geometry_msgs::Point32 Dist_vl [4];
geometry_msgs::Point32 Force_vl [4];
multi_amr_nectec::pos_msg get_msg;
int team_size; //use for get param
void robot_pos_Callback(const multi_amr_nectec::pos_msg::ConstPtr& msg) 
{ for (int i = 0; i<4; i++)
    { robot_pos[i].x=msg->point_robot[i].x;
      robot_pos[i].y=msg->point_robot[i].y;
       ROS_INFO("Get amr %d pos : x=%.2f, y=%.2f",i, msg->point_robot[i].x, msg->point_robot[i].y);
       ROS_INFO("----------------");
    }
}   

int main(int argc, char** argv) 
{
 ros::init(argc, argv, "vl_force");
 ros::NodeHandle nh;
 ros::Rate loopRate(1);

 ros::Subscriber robot_pos_sub = nh.subscribe("robot_pos", 1000, robot_pos_Callback);
 
 ros::Publisher force0_pub = nh.advertise<geometry_msgs::Twist>("amr_0/cmd_vel", 1000);
 ros::Publisher force1_pub = nh.advertise<geometry_msgs::Twist>("amr_1/cmd_vel", 1000); 
 ros::Publisher force2_pub = nh.advertise<geometry_msgs::Twist>("amr_2/cmd_vel", 1000);
 ros::Publisher force3_pub = nh.advertise<geometry_msgs::Twist>("amr_3/cmd_vel", 1000);
 
 nh.getParam("inter_agent_force/team_size", team_size);
 //int team_size = 4 ;
 float Kij=0.25;
 geometry_msgs::Point32 dist_agent;
    dist_agent.x=8;
    dist_agent.y=8;

while (ros::ok()) 
{ ros::spinOnce();
  geometry_msgs::Twist send_fvl [team_size];
/*
   for (int j = 0; j < team_size; j++)
                {Dist_vl[j].x=get_vl.x-robot_pos[j].x;
                 Dist_vl[j].y=get_vl.y-robot_pos[j].y;
                int check_x=1;
                int check_y=1;
               if(robot_pos[j].x>=get_vl.x)
                    {check_x=-1;}
               if(robot_pos[j].y>=get_vl.y)
                    {check_y=-1;}
                //ROS_INFO("Dist agent X=%.3f",dist_agent.x);
                //ROS_INFO("Dist_vl of robot %d[%.3f,%.3f]",j,Dist_vl[j].x,Dist_vl[j].y);
                Force_vl[j].x=Kvl*(Dist_vl[j].x-check_x*(dist_agent.x));
                Force_vl[j].y=Kvl*(Dist_vl[j].y-check_y*(dist_agent.y));
             
                //ROS_INFO("Virtual Force of robot %d[%.3f,%.3f]",j,Force_vl[j].x,Force_vl[j].y);
                 
                  send_fvl[j].linear.x =Force_vl[j].x;
                  send_fvl[j].linear.y =Force_vl[j].y;  
                 ROS_INFO("Cmd_vel of robot %d  [%.3f,%.3f]",j, send_fvl[j].linear.x,send_fvl[j].linear.y);  
                
                }
                force0_pub.publish(send_fvl[0]);
                force1_pub.publish(send_fvl[1]);
                force2_pub.publish(send_fvl[2]);
                force3_pub.publish(send_fvl[3]);

      ROS_INFO("-------SEND CMD VEL------");
   
      loopRate.sleep();
*/
}

  //return 0;

}
