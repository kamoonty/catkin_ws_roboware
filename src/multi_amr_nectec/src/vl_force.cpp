#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <boost/lexical_cast.hpp>
#include <std_msgs/Float32.h>
#include <geometry_msgs/Point32.h>
#include <geometry_msgs/Twist.h>
#include <stdlib.h> 
#include "multi_amr_nectec/pos_msg.h"


geometry_msgs::Point32 get_vl;
geometry_msgs::Point32 robot_pos [4];
geometry_msgs::Point32 Dist_vl [4];
geometry_msgs::Point32 Force_vl [4];
multi_amr_nectec::pos_msg get_msg;
int team_size; //use for get param
float Kvl;
float dist_from_vl_x;
float dist_from_vl_y;
void VL_Callback(const geometry_msgs::Point32 & vl_pos)
{  get_vl= vl_pos;
  ROS_INFO("VL Position [%.3f,%.3f]",get_vl.x,get_vl.y);
}

void robot_pos_Callback(const multi_amr_nectec::pos_msg::ConstPtr& msg) 
{ for (int i = 0; i<4; i++)
    { robot_pos[i].x=msg->point_robot[i].x;
      robot_pos[i].y=msg->point_robot[i].y;
       //ROS_INFO("Get amr %d pos : x=%.2f, y=%.2f",i, msg->point_robot[i].x, msg->point_robot[i].y);
       //ROS_INFO("----------------");
    }
}   

int main(int argc, char** argv) 
{
 ros::init(argc, argv, "vl_force");
 ros::NodeHandle nh;
 ros::Rate loopRate(1);
 ros::Subscriber vl_sub = nh.subscribe("vl_pos", 1000, VL_Callback);
 ros::Subscriber robot_pos_sub = nh.subscribe("robot_pos", 1000, robot_pos_Callback);
 
 ros::Publisher force0_pub = nh.advertise<geometry_msgs::Twist>("amr_0/cmd_vel", 1000);
 ros::Publisher force1_pub = nh.advertise<geometry_msgs::Twist>("amr_1/cmd_vel", 1000); 
 ros::Publisher force2_pub = nh.advertise<geometry_msgs::Twist>("amr_2/cmd_vel", 1000);
 ros::Publisher force3_pub = nh.advertise<geometry_msgs::Twist>("amr_3/cmd_vel", 1000);
 
 nh.getParam("vl_force/team_size", team_size);
 nh.getParam("vl_force/Kvl", Kvl);
 nh.getParam("vl_force/dist_from_vl_x", dist_from_vl_x);
 nh.getParam("vl_force/dist_from_vl_y", dist_from_vl_y); 

float hold_x=dist_from_vl_x;
float hold_y=dist_from_vl_y;

while (ros::ok()) 
{ ros::spinOnce();
  geometry_msgs::Twist send_fvl [team_size];
   for (int j = 0; j < team_size; j++)
                {Dist_vl[j].x=get_vl.x-robot_pos[j].x;
                 Dist_vl[j].y=get_vl.y-robot_pos[j].y;
                int check_x=1;
                int check_y=1;
               if(robot_pos[j].x>=get_vl.x)
                    {check_x=-1;}
               if(robot_pos[j].y>=get_vl.y)
                    {check_y=-1;}
                // for triangular formation
               /*if (j==2)
               {dist_from_vl_x=0;
                dist_from_vl_y=4.618;}     
               else
               {dist_from_vl_x=hold_x;
               dist_from_vl_y=hold_y;}
               */

                //ROS_INFO("Dist default X=%.3f",dist_from_vl_x);
                //ROS_INFO("Dist_vl of robot %d[%.3f,%.3f]",j,Dist_vl[j].x,Dist_vl[j].y);
                Force_vl[j].x=Kvl*(Dist_vl[j].x-check_x*(dist_from_vl_x));
                Force_vl[j].y=Kvl*(Dist_vl[j].y-check_y*(dist_from_vl_y));
             
                //ROS_INFO("Virtual Force of robot %d[%.3f,%.3f]",j,Force_vl[j].x,Force_vl[j].y);
                 
                  send_fvl[j].linear.x =Force_vl[j].x;
                  send_fvl[j].linear.y =Force_vl[j].y;  
                 ROS_INFO("Cmd_vel robot%d=[%.3f,%.3f]",j, send_fvl[j].linear.x,send_fvl[j].linear.y);  
                
                }
                force0_pub.publish(send_fvl[0]);
                force1_pub.publish(send_fvl[1]);
                force2_pub.publish(send_fvl[2]);
                force3_pub.publish(send_fvl[3]);
              
      ROS_INFO("-------SEND CMD VEL------");
   
      loopRate.sleep();

}

  //return 0;

}
