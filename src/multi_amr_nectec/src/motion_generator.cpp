#include "ros/ros.h"
#include <stdlib.h> 
#include <std_msgs/Float32.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Twist.h>
int team_size; //use for get param from launch file
geometry_msgs::Twist Fvl[10];
geometry_msgs::Twist Fij[10];
geometry_msgs::Twist F_rot[10];

void Fvl_CB(const geometry_msgs::Twist & Fvl)
{


}

void Fij_CB(const geometry_msgs::Twist & Fij)
{

}
void F_rot_CB(const geometry_msgs::Twist & F_rot)
{

}
int main(int argc, char **argv)
{

ros::init(argc, argv, "motion_generator");
ros::Rate loopRate(20);
ros::NodeHandle nh;
ros::Subscriber Fvl_sub = nh.subscribe("msg1", 1000, Fvl_CB);
ros::Subscriber Fij_sub = nh.subscribe("msg2", 1000, Fij_CB);
ros::Subscriber F_rot_sub = nh.subscribe("msg3", 1000, F_rot_CB);

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
}

ros::spinOnce();
loopRate.sleep(); 
}

//return 0;
}