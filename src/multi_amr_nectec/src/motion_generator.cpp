#include "ros/ros.h"
#include <stdlib.h> 
#include <std_msgs/Float32.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Twist.h>
#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"
#include "std_msgs/Float32MultiArray.h"

int team_size; //use for get param from launch file
float v_linear_threshold;
float v_angular_threshold;
geometry_msgs::Twist Fvl[10];
geometry_msgs::Twist Fij[10];
geometry_msgs::Twist F_rot[10];

void Fvl_x_CB(const std_msgs::Float32MultiArray::ConstPtr& robot_cmd_vel_linear_x)
{	int i = 0;
	// print all the remaining numbers
	for(std::vector<float>::const_iterator it = robot_cmd_vel_linear_x->data.begin(); it != robot_cmd_vel_linear_x->data.end(); ++it)
	{  Fvl[i].linear.x=*it;
		i++;
        //printf("robot %d FVL_x=%f, \n",i, Fvl[i].linear.x);
	}

	return;
}
void Fvl_y_CB(const std_msgs::Float32MultiArray::ConstPtr& robot_cmd_vel_linear_y)
{	int i = 0;
	// print all the remaining numbers
	for(std::vector<float>::const_iterator it = robot_cmd_vel_linear_y->data.begin(); it != robot_cmd_vel_linear_y->data.end(); ++it)
	{  Fvl[i].linear.y=*it;
		i++;
        //printf("robot %d FVL_y=%f, \n",i, Fvl[i].linear.y);
	}

	return;
}
/*
void Fij_CB(const geometry_msgs::Twist & Fij)
{

}
void F_rot_CB(const geometry_msgs::Twist & F_rot)
{

}
*/
int main(int argc, char **argv)
{

ros::init(argc, argv, "motion_generator");
ros::NodeHandle nh;
ros::Rate loopRate(20);
nh.getParam("motion_generator/team_size", team_size);
nh.getParam("motion_generator/v_linear_threshold",v_linear_threshold);
nh.getParam("motion_generator/v_angular_threshold",v_angular_threshold);

ros::Subscriber Fvl_x_sub = nh.subscribe("vl_force_cmd_vel_x", 1000, Fvl_x_CB);
ros::Subscriber Fvl_y_sub = nh.subscribe("vl_force_cmd_vel_y", 1000, Fvl_y_CB);
/*
ros::Subscriber Fij_sub = nh.subscribe("msg2", 1000, Fij_CB);
ros::Subscriber F_rot_sub = nh.subscribe("msg3", 1000, F_rot_CB);
*/
ros::Publisher amr_0_cmd_vel_pub = nh.advertise<geometry_msgs::Twist>("amr_0/cmd_vel", 1000);
ros::Publisher amr_1_cmd_vel_pub = nh.advertise<geometry_msgs::Twist>("amr_1/cmd_vel", 1000); 
ros::Publisher amr_2_cmd_vel_pub = nh.advertise<geometry_msgs::Twist>("amr_2/cmd_vel", 1000);
ros::Publisher amr_3_cmd_vel_pub = nh.advertise<geometry_msgs::Twist>("amr_3/cmd_vel", 1000);
geometry_msgs::Twist final_cmd_vel [team_size];

while (nh.ok()) 
{

float m = 50; //robot mass = 50 kg
float lamda=2;
for(int n=0;n<team_size;n++)
{
final_cmd_vel[n].linear.x=(Fvl[n].linear.x+Fij[n].linear.x)/m;
final_cmd_vel[n].linear.y =(Fvl[n].linear.y+Fij[n].linear.y)/m;
final_cmd_vel[n].angular.z= lamda*F_rot[n].angular.z;
//Linear Velocity Threshold 
if(final_cmd_vel[n].linear.x>=v_linear_threshold)
              {final_cmd_vel[n].linear.x=v_linear_threshold;
              ROS_INFO("Threshold Vx max");}
else if (final_cmd_vel[n].linear.x<=-v_linear_threshold)
              {final_cmd_vel[n].linear.x=-v_linear_threshold;
                ROS_INFO("Threshold Vx min");}
if(final_cmd_vel[n].linear.y>=v_linear_threshold)
              {final_cmd_vel[n].linear.y=v_linear_threshold;
              ROS_INFO("Threshold Vy max");}
else if (final_cmd_vel[n].linear.y<=-v_linear_threshold)
              {final_cmd_vel[n].linear.y=-v_linear_threshold;
                ROS_INFO("Threshold Vy min");}
//Angular Velocity Threshold 
if(final_cmd_vel[n].angular.z>=v_angular_threshold)
   {final_cmd_vel[n].angular.z=v_angular_threshold;
              ROS_INFO("Threshold Theta max");}
else if(final_cmd_vel[n].angular.z<=-v_angular_threshold)
   {final_cmd_vel[n].angular.z=-v_angular_threshold;
              ROS_INFO("Threshold Theta min");}

ROS_INFO("Final CMD vel of robot %d (x,y,theta)=(%f,%f,%f)",n,final_cmd_vel[n].linear.x,final_cmd_vel[n].linear.y,final_cmd_vel[n].angular.z );
}
amr_0_cmd_vel_pub.publish(final_cmd_vel[0]);
amr_1_cmd_vel_pub.publish(final_cmd_vel[1]);
amr_2_cmd_vel_pub.publish(final_cmd_vel[2]);
amr_3_cmd_vel_pub.publish(final_cmd_vel[3]);


ros::spinOnce();
loopRate.sleep(); 
}

//return 0;
}