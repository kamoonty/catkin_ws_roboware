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
geometry_msgs::Twist get_velocity_vl;  // un used
float delta_time;
int team_size; //use for get param from launch file
float K_ang;
float D_ang;
// We need to round value after subscribe because if not it can cause problem
// when VL= 0.00000003 and Robot 1 Pos X = 0.00000004 it is not equal so useroundf (number*100)/100



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
 ros::init(argc, argv, "orientation_control_exper");
 ros::NodeHandle nh;
 ros::Rate loopRate(100);
 //load param from launch file
 nh.getParam("orientation_control_exper/team_size", team_size);
 nh.getParam("orientation_control_exper/K_ang", K_ang);
 nh.getParam("orientation_control_exper/D_ang", D_ang);
 nh.getParam("orientation_control_exper/delta_time", delta_time);

 ros::Publisher pub_rotational_force = nh.advertise<std_msgs::Float32MultiArray>("F_rot", 1000);
 
 float diff_angle [team_size];
 float new_diff_angle [team_size];
 float first_data [team_size];
 float second_data [team_size];
 float diff_value [team_size];
 float previous_velocity [team_size];
 //float robot_theta [team_size];
 geometry_msgs::Twist calculate_rotational_force [team_size];
tf::TransformListener listener;
while (nh.ok()) 
{ std_msgs::Float32MultiArray robot_rotational_force;
  robot_rotational_force.data.clear();
   for (int i = 0; i < team_size; i++)
    {  
    tf::StampedTransform transform;
    try{std::string follower_robot ("/amr_");
    std::string leader_robot ("vl_robot/base_link");
    follower_robot =follower_robot+ boost::lexical_cast<std::string>(i);
    follower_robot =follower_robot+"/base_link";
 
    listener.waitForTransform(follower_robot,leader_robot, ros::Time(0), ros::Duration(100.0) );
    listener.lookupTransform(follower_robot,leader_robot,ros::Time(0), transform);
    //base_link is refer to virtual leader robot
    // we should replace to vl_robot/base_link later
    }
    catch (tf::TransformException &ex) {
      ROS_ERROR("%s",ex.what());
      ros::Duration(1.0).sleep();
      continue;
    }
//double x = transform.getOrigin().getX();
//double y = transform.getOrigin().getY();
double th = tf::getYaw(transform.getRotation());    
diff_angle[i]=th;          

int rotate_direction=0; // use for clockwise and anti clockwise direction
 ROS_INFO("Robot %d",i );
ROS_INFO("Radian angle between VL and agent %d = %f rad",i,diff_angle[i] );
ROS_INFO("Degree angle between VL and agent %d = %f deg",i,convert_to_degree(diff_angle[i]) );


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
       { //ROS_INFO("First Data = %f",first_data[i]);
        //ROS_INFO("Second Data = %f",second_data[i]);
         diff_value[i]= (fabs(first_data[i])-fabs(second_data[i]))/delta_time;
       second_data[i]=first_data[i];
       //ROS_INFO("Differentiate data angle of robot %d = %f",i,diff_value[i]);
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
      ROS_INFO("------------------------------------------");
      robot_rotational_force.data.push_back(calculate_rotational_force[i].angular.z);
      
      }            

     pub_rotational_force.publish(robot_rotational_force);

      ros::spinOnce();
      loopRate.sleep();

}

}
