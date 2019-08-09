#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <std_msgs/Float32.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose2D.h>
#include <stdlib.h> 
#include "math.h"
#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"
#include "std_msgs/Float32MultiArray.h"
//#include "std_msgs/String.h"
geometry_msgs::Pose2D get_pose2d_agent [10]; //allocate for max 10 robots
geometry_msgs::Pose2D get_pose2d_vl;
geometry_msgs::Twist get_velocity_vl; 
float delta_time;

int team_size; //use for get param from launch file
float K_ang;
float D_ang;
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
void agent4_pose2D_CB(const geometry_msgs::Pose2D & agent_pose2d)
{ get_pose2d_agent[4].theta=roundf(agent_pose2d.theta*10000)/10000;
}
void agent5_pose2D_CB(const geometry_msgs::Pose2D & agent_pose2d)
{ get_pose2d_agent[5].theta=roundf(agent_pose2d.theta*10000)/10000;
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
 ros::Rate loopRate(100);
 //load param from launch file
 nh.getParam("orientation_control/team_size", team_size);
 nh.getParam("orientation_control/K_ang", K_ang);
 nh.getParam("orientation_control/D_ang", D_ang);
 nh.getParam("orientation_control/delta_time", delta_time);
 ros::Subscriber vl_velocity_sub = nh.subscribe("vl_robot/pub_velocity", 1000, vl_velocityCB); // subscribe speed of VL in x y theta (m/s)
 ros::Subscriber vl_pose2d_sub = nh.subscribe("vl_robot/pose2d", 1000, vl_pose2D_CB);
 ros::Subscriber agent0_pose2d_sub = nh.subscribe("amr_0/pose2d", 1000, agent0_pose2D_CB);
 ros::Subscriber agent1_pose2d_sub = nh.subscribe("amr_1/pose2d", 1000, agent1_pose2D_CB);
 ros::Subscriber agent2_pose2d_sub = nh.subscribe("amr_2/pose2d", 1000, agent2_pose2D_CB);
 ros::Subscriber agent3_pose2d_sub = nh.subscribe("amr_3/pose2d", 1000, agent3_pose2D_CB);

 ros::Subscriber agent4_pose2d_sub = nh.subscribe("amr_4/pose2d", 1000, agent4_pose2D_CB);
 ros::Subscriber agent5_pose2d_sub = nh.subscribe("amr_5/pose2d", 1000, agent5_pose2D_CB);
 ros::Publisher pub_rotational_force = nh.advertise<std_msgs::Float32MultiArray>("F_rot", 1000);
 
 float diff_angle [team_size];
 float new_diff_angle [team_size];
 float first_data [team_size];
 float second_data [team_size];
 float diff_value [team_size];
 float previous_velocity [team_size];
 geometry_msgs::Twist calculate_rotational_force [team_size];

while (nh.ok()) 
{ std_msgs::Float32MultiArray robot_rotational_force;
  robot_rotational_force.data.clear();
   for (int i = 0; i < team_size; i++)
      {       //ROS_INFO("-start loop-");
              int rotate_direction=0; // use for clockwise and anti clockwise direction
              float degree_vl = convert_to_degree(get_pose2d_vl.theta);
              float degree_agent[team_size];
              degree_agent[i]=convert_to_degree(get_pose2d_agent[i].theta);
              ROS_INFO("Robot %d",i );
              ROS_INFO("VL angle =%f degree",degree_vl );
              ROS_INFO("Agent[%d] angle =%f degree",i,degree_agent[i] );
              diff_angle[i]= (degree_vl-degree_agent[i]);
              ROS_INFO("Angle between VL and agent %d = %f degree",i,diff_angle[i] );
         // to avoid unnecessary rotation  
    if(diff_angle[i]>=0) 
    {
    if(fabs(diff_angle[i])<180)
       rotate_direction=1;  // clockwise 
    else rotate_direction=-1; //anti clock wise
    }

    else if (diff_angle[i]<0)
     {
    if(fabs(diff_angle[i])<180)
       rotate_direction=-1;
    else rotate_direction=1;
    }
    // to avoid jerk movement of VL and agent between 0 or 360
     if(fabs(diff_angle[i])>=180&&fabs(diff_angle[i])<=360)
    { //ROS_INFO("diff_angle=%f",diff_angle[i]); 
      new_diff_angle[i]=360-fabs(diff_angle[i]);
      diff_angle[i]=new_diff_angle[i];
       ROS_INFO("New Angle between VL and agent %d = %f degree",i,diff_angle[i] );
       }    

    // equation to calculate damper equation  
    // still has problem when angle between 0 and 360 so we set
    // D_ang=0 first
      first_data[i]= fabs(diff_angle[i]);
      if(second_data[i]!=0)
       { ROS_INFO("First Data = %f",first_data[i]);
        ROS_INFO("Second Data = %f",second_data[i]);
         diff_value[i]= (fabs(first_data[i])-fabs(second_data[i]))/delta_time;
       second_data[i]=first_data[i];
       ROS_INFO("Differentiate data angle of robot %d = %f",i,diff_value[i]);
       }
       else
       {second_data[i]=first_data[i];
       ROS_INFO("!!!!Enter First loop!!!");
       }     

      // Use fabs for float absolute
      calculate_rotational_force[i].angular.z=rotate_direction*(K_ang*fabs(diff_angle[i])+D_ang*diff_value[i]);
      calculate_rotational_force[i].angular.z=(calculate_rotational_force[i].angular.z)*M_PI/180; //convert back to radian

  /*   // to avoid jerk movement  but it work not properly
    if(fabs(diff_angle[i])>=180&&fabs(diff_angle[i])<=360)
    {calculate_rotational_force[i].angular.z=previous_velocity[i]; //reduce speed to the same as previous loop 
       ROS_INFO("-Fix speed same as previous velocity to avoid jerk rotation-"); }    
    previous_velocity[i]=calculate_rotational_force[i].angular.z;

*/ 
      // Publish data        
      ROS_INFO("Rotational Force -> robot %d =%f",i,calculate_rotational_force[i].angular.z );  
      ROS_INFO("-----------------------");
      robot_rotational_force.data.push_back(calculate_rotational_force[i].angular.z);
      
      }            

     pub_rotational_force.publish(robot_rotational_force);

      ros::spinOnce();
      loopRate.sleep();

}

}
