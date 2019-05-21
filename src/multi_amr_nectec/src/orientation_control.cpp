#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <std_msgs/Float32.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose2D.h>
#include <stdlib.h> 
//#include "multi_amr_nectec/pos_msg.h"
//#include "math.h"
//#include "std_msgs/String.h"
geometry_msgs::Pose2D get_pose2d_agent [10]; //allocate for max 10 robots
geometry_msgs::Pose2D get_pose2d_vl;
geometry_msgs::Twist get_velocity_vl; 


int team_size; //use for get param from launch file
float K_ang;
// We need to round value after subscribe because if not it can cause problem
// when VL= 0.00000003 and Robot 1 Pos X = 0.00000004 it is not equal so useroundf (number*100)/100

void vl_velocityCB(const geometry_msgs::Twist & vl_velocity) //robot velocity contain x y yaw speed
{ get_velocity_vl.angular.z=roundf(vl_velocity.angular.z*10000)/10000; // round to 5 decimal place
  ROS_INFO("**** VL Yaw velocity [%f]*****", get_velocity_vl.angular.z);
}
void vl_pose2D_CB(const geometry_msgs::Pose2D & vl_pose2d) //robot pose 2d contain x y pos and theta (yaw position)
{ get_pose2d_vl.theta=roundf(vl_pose2d.theta*10000)/10000;
}

void agent0_pose2D_CB(const geometry_msgs::Pose2D & agent_pose2d)
{ get_pose2d_agent[0].theta=roundf(agent_pose2d.theta*10000)/10000;
}
void agent1_pose2D_CB(const geometry_msgs::Pose2D & agent_pose2d)
{ get_pose2d_agent[1].theta=roundf(agent_pose2d.theta*10000)/10000;
}
void agent2_pose2D_CB(const geometry_msgs::Pose2D & agent_pose2d)
{ get_pose2d_agent[2].theta=roundf(agent_pose2d.theta*10000)/10000;
}
void agent3_pose2D_CB(const geometry_msgs::Pose2D & agent_pose2d)
{ get_pose2d_agent[3].theta=roundf(agent_pose2d.theta*10000)/10000;
}
int main(int argc, char** argv) 
{
 ros::init(argc, argv, "vl_force");
 ros::NodeHandle nh;
 ros::Rate loopRate(20);
 //load param from launch file
 nh.getParam("orientation_force/team_size", team_size);
 nh.getParam("orientation_force/K_ang", K_ang);

 geometry_msgs::Twist send_fvl [team_size];
 geometry_msgs::Point Dist_vl [team_size];
 geometry_msgs::Point Force_vl [team_size];
 
 ros::Subscriber vl_velocity_sub = nh.subscribe("vl_robot/pub_velocity", 1000, vl_velocityCB); // subscribe speed of VL in x y theta (m/s)
 ros::Subscriber vl_pose2d_sub = nh.subscribe("vl_robot/pose2d", 1000, vl_pose2D_CB);
 ros::Subscriber agent0_pose2d_sub = nh.subscribe("amr_0/pose2d", 1000, agent0_pose2D_CB);
 ros::Subscriber agent1_pose2d_sub = nh.subscribe("amr_1/pose2d", 1000, agent1_pose2D_CB);
 ros::Subscriber agent2_pose2d_sub = nh.subscribe("amr_2/pose2d", 1000, agent2_pose2D_CB);
 ros::Subscriber agent3_pose2d_sub = nh.subscribe("amr_3/pose2d", 1000, agent3_pose2D_CB);

 ros::Publisher angular_force0_pub = nh.advertise<geometry_msgs::Twist>("amr_0/cmd_vel", 1000);
 ros::Publisher angular_force1_pub = nh.advertise<geometry_msgs::Twist>("amr_1/cmd_vel", 1000); 
 ros::Publisher angular_force2_pub = nh.advertise<geometry_msgs::Twist>("amr_2/cmd_vel", 1000);
 ros::Publisher angular_force3_pub = nh.advertise<geometry_msgs::Twist>("amr_3/cmd_vel", 1000);


while (nh.ok()) 
{ 
   for (int i = 0; i < team_size; i++)
      {        int state=0;
               Dist_vl[i].x=get_pos_vl.x-robot_pos[i].x;
               Dist_vl[i].y=get_pos_vl.y-robot_pos[i].y;
               if(Dist_vl[i].x<0)
               {unit_vec_x=-1;}
               else if (Dist_vl[i].x>0)
               {unit_vec_x=1;}
               
               if(Dist_vl[i].y<0)
               {unit_vec_y=-1;}
               else if (Dist_vl[i].y>0)
               {unit_vec_y=1;}
               float abs_dist = sqrt(pow((robot_pos[i].x-get_pos_vl.x),2)+pow((robot_pos[i].y-get_pos_vl.y),2)) ;         
               //ROS_INFO("Dist from VL of AMR %d=[%f,%f]",i,Dist_vl[i].x,Dist_vl[i].y);
               //ROS_INFO("Absolute distance of AMR %d from VL =%f",i,abs_dist);
               ROS_INFO("Ux= %d Uy= %d",unit_vec_x,unit_vec_y);
               ROS_INFO("Dist_vl [%f,%f]",Dist_vl[i].x,Dist_vl[i].y);
               //double abs_dist_vl_x=fabs(Dist_vl[i].x); 
               //double abs_dist_vl_y=fabs(Dist_vl[i].y);
              
               //ROS_INFO("ABS dist_VL =[%f,%f]",abs_dist_vl_x,abs_dist_vl_y);
                // Use fabs for float absolute
                Force_vl[i].x=Kvl*(fabs(Dist_vl[i].x)-fabs(initial_pos_x[i]));
                Force_vl[i].y=Kvl*(fabs(Dist_vl[i].y)-fabs(initial_pos_y[i]));            
                ROS_INFO("Virtual Force of robot %d[%.3f,%.3f]",i,Force_vl[i].x,Force_vl[i].y);           
                  send_fvl[i].linear.x =unit_vec_x*Force_vl[i].x;
                  send_fvl[i].linear.y =unit_vec_y*Force_vl[i].y; 
                  send_fvl[i].angular.z=get_angular_vl.angular.z; 
                ROS_INFO("Cmd_vel robot %d x=%f y=%f",i, send_fvl[i].linear.x,send_fvl[i].linear.y);  
                ROS_INFO("-----------------------");
                }              
                force0_pub.publish(send_fvl[0]);
                force1_pub.publish(send_fvl[1]);
                force2_pub.publish(send_fvl[2]);
                force3_pub.publish(send_fvl[3]);
                

      ros::spinOnce();
      loopRate.sleep();

}

  //return 0;

}
