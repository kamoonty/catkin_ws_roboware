#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <std_msgs/Float32.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose2D.h>
#include <stdlib.h> 
//#include "multi_amr_nectec/pos_msg.h"
#include "math.h"
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
  //ROS_INFO("**** VL Yaw velocity [%f]*****", get_velocity_vl.angular.z);
}
void vl_pose2D_CB(const geometry_msgs::Pose2D & vl_pose2d) //robot pose 2d contain x y pos and theta (yaw position)
{ get_pose2d_vl.theta=roundf(vl_pose2d.theta*10000)/10000;
//ROS_INFO("**** VL angle(theta)= [%f]*****", get_pose2d_vl.theta);
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
float convert_to_degree(float theta)
{            
  if(theta<0)
    {//ROS_INFO("Theta<0");  
    theta =(2*M_PI)+theta;
    theta=(theta/M_PI)*180;}
else theta=(theta/M_PI)*180;
return theta;
}

int main(int argc, char** argv) 
{
 ros::init(argc, argv, "orientation_control");
 ros::NodeHandle nh;
 ros::Rate loopRate(20);
 //load param from launch file
 nh.getParam("orientation_control/team_size", team_size);
 nh.getParam("orientation_control/K_ang", K_ang);
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
 float diff_angle [team_size];
 
 geometry_msgs::Twist send_velocity [team_size];

while (nh.ok()) 
{ 
   for (int i = 0; i < team_size; i++)
      {       //ROS_INFO("-start loop-");
              int rotate_direction=0; // use for clockwise and anti clockwise direction
              float degree_vl = convert_to_degree(get_pose2d_vl.theta);
              float degree_agent[team_size];
              degree_agent[i]=convert_to_degree(get_pose2d_agent[i].theta);
              ROS_INFO("VL angle =%f degree",degree_vl );
              ROS_INFO("agent[%d] angle =%f degree",i,degree_agent[i] );
              diff_angle[i]= (degree_vl-degree_agent[i]);
              ROS_INFO("Diff angle agent %d = %f degree",i,degree_agent[i] );
              /*
              if(diff_angle[i]>0) //case1 vl_angle>robot_angle
              {rotate_direction=1;}   //turn anti clockwise
              else if (diff_angle[i]<0) //case2 vl_angle<robot_angle
              {rotate_direction=-1;}
              else if (diff_angle==0) // VL and robot are in same degree
              {rotate_direction=0;}
              */
    if(diff_angle[i]>0) 
    {
    if(fabs(diff_angle[i])<180)
       rotate_direction=1;
    else rotate_direction=-1;
    }

    else if (diff_angle[i]<0)
     {
    if(fabs(diff_angle[i])<180)
       rotate_direction=-1;
    else rotate_direction=1;
    }

              // Use fabs for float absolute
              send_velocity[i].angular.z=K_ang*fabs(diff_angle[i])*rotate_direction;
              send_velocity[i].angular.z=(send_velocity[i].angular.z)*M_PI/180; //convert back to radian
              //set angular velocity thereshold 
              if(send_velocity[i].angular.z>=1)
              {send_velocity[i].angular.z=1;
              ROS_INFO("Threshold angular velocity max");}
              else if (send_velocity[i].angular.z<=-1)
              {send_velocity[i].angular.z=-1;
                ROS_INFO("Threshold angular velocity min");}

              ROS_INFO("Angular velocity of robot %d =%f",i,send_velocity[i].angular.z );  
              ROS_INFO("-----------------------");
      }              
      angular_force0_pub.publish(send_velocity[0]);
      angular_force1_pub.publish(send_velocity[1]);
      angular_force2_pub.publish(send_velocity[2]);
      angular_force3_pub.publish(send_velocity[3]);
      ros::spinOnce();
      loopRate.sleep();

}

}
