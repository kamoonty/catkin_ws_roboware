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
float robot_mass;
float robot_inertia;
float robot_radious;
geometry_msgs::Twist Fvl[10];
geometry_msgs::Twist Fij[10];
geometry_msgs::Twist F_rot[10];
// Virtual leader force
void Fvl_x_CB(const std_msgs::Float32MultiArray::ConstPtr& F_vl_x)
{	int i = 0;
	for(std::vector<float>::const_iterator it = F_vl_x->data.begin(); it != F_vl_x->data.end(); ++it)
	{  Fvl[i].linear.x=*it;
        //printf("robot %d FVL_x=%f, \n",i, Fvl[i].linear.x);
		i++;
	}

	return;
}
void Fvl_y_CB(const std_msgs::Float32MultiArray::ConstPtr& F_vl_y)
{	int i = 0;
	for(std::vector<float>::const_iterator it = F_vl_y->data.begin(); it != F_vl_y->data.end(); ++it)
	{  Fvl[i].linear.y=*it;
        //printf("robot %d FVL_y=%f, \n",i, Fvl[i].linear.y);
		i++;
	}

	return;
}
//Inter agent force
void Fij_x_CB(const std_msgs::Float32MultiArray::ConstPtr& F_ij_x)
{	int i = 0;
	for(std::vector<float>::const_iterator it = F_ij_x->data.begin(); it != F_ij_x->data.end(); ++it)
	{  Fij[i].linear.x=*it;
        //printf("robot %d FVL_x=%f, \n",i, Fvl[i].linear.x);
		i++;
	}

	return;
}
void Fij_y_CB(const std_msgs::Float32MultiArray::ConstPtr& F_ij_y)
{	int i = 0;
	for(std::vector<float>::const_iterator it = F_ij_y->data.begin(); it != F_ij_y->data.end(); ++it)
	{  Fij[i].linear.y=*it;
        //printf("robot %d FVL_y=%f, \n",i, Fvl[i].linear.y);
		i++;
	}

	return;
}
//Rotational force
void F_rot_CB(const std_msgs::Float32MultiArray::ConstPtr& robot_cmd_vel_angular_z)
{int i = 0;
	// print all the remaining numbers
	for(std::vector<float>::const_iterator it = robot_cmd_vel_angular_z->data.begin(); it != robot_cmd_vel_angular_z->data.end(); ++it)
	{  F_rot[i].angular.z=*it;	
        //printf("robot %d F_Rot=%f, \n",i,F_rot[i].angular.z);
		i++;
	}

	return;

}
int main(int argc, char **argv)
{
ros::init(argc, argv, "motion_generator");
ros::NodeHandle nh;
ros::Rate loopRate(5);
nh.getParam("motion_generator/team_size", team_size);
nh.getParam("motion_generator/v_linear_threshold",v_linear_threshold);
nh.getParam("motion_generator/v_angular_threshold",v_angular_threshold);
nh.getParam("motion_generator/robot_mass", robot_mass);
nh.getParam("motion_generator/robot_inertia", robot_inertia);
nh.getParam("motion_generator/robot_radious", robot_radious);
ros::Subscriber Fvl_x_sub = nh.subscribe("F_vl_x", 1000, Fvl_x_CB);
ros::Subscriber Fvl_y_sub = nh.subscribe("F_vl_y", 1000, Fvl_y_CB);
ros::Subscriber Fij_x_sub = nh.subscribe("F_ij_x", 1000, Fij_x_CB);
ros::Subscriber Fij_y_sub = nh.subscribe("F_ij_y", 1000, Fij_y_CB);
ros::Subscriber F_rot_sub = nh.subscribe("F_rot", 1000, F_rot_CB);
/*
ros::Subscriber Fij_sub = nh.subscribe("msg2", 1000, Fij_CB);
*/
ros::Publisher amr_0_cmd_vel_pub = nh.advertise<geometry_msgs::Twist>("amr_0/cmd_vel", 1000);
ros::Publisher amr_1_cmd_vel_pub = nh.advertise<geometry_msgs::Twist>("amr_1/cmd_vel", 1000); 
ros::Publisher amr_2_cmd_vel_pub = nh.advertise<geometry_msgs::Twist>("amr_2/cmd_vel", 1000);
ros::Publisher amr_3_cmd_vel_pub = nh.advertise<geometry_msgs::Twist>("amr_3/cmd_vel", 1000);
geometry_msgs::Twist final_cmd_vel [team_size];
float delta_t=1;
while (nh.ok()) 
{
float lamda=2;
for(int n=0;n<team_size;n++)
{
final_cmd_vel[n].linear.x=(Fvl[n].linear.x+Fij[n].linear.x)*delta_t/robot_mass;
final_cmd_vel[n].linear.y =(Fvl[n].linear.y+Fij[n].linear.y)*delta_t/robot_mass;
final_cmd_vel[n].angular.z= (F_rot[n].angular.z)*robot_radious*delta_t/robot_inertia;

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
ROS_INFO("--------------------------");
amr_0_cmd_vel_pub.publish(final_cmd_vel[0]);
amr_1_cmd_vel_pub.publish(final_cmd_vel[1]);
amr_2_cmd_vel_pub.publish(final_cmd_vel[2]);
amr_3_cmd_vel_pub.publish(final_cmd_vel[3]);


ros::spinOnce();
loopRate.sleep(); 
}

//return 0;
}