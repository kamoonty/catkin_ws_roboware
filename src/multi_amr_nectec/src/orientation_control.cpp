#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <std_msgs/Float32.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Twist.h>
#include <stdlib.h> 
//#include "multi_amr_nectec/pos_msg.h"
//#include "math.h"
//#include "std_msgs/String.h"
geometry_msgs::Quaternion get_robot_quat[10] ; //allocate for max 10 robots
geometry_msgs::Twist get_angular_vl;
//multi_amr_nectec::pos_msg get_msg;
int team_size; //use for get param from launch file
float K_ang;
// We need to round value after subscribe because if not it can cause problem
// when VL= 0.00000003 and Robot 1 Pos X = 0.00000004 it is not equal so useroundf (number*100)/100

void vl_angCB(const geometry_msgs::Twist & robot_velocity)
{ get_angular_vl.angular.z=roundf(robot_velocity.angular.z*10000)/10000; // round to 5 decimal place
  ROS_INFO("**** VL Yaw velocity [%f]*****",get_angular_vl.angular.z);
}

void robot0_quatCB(const geometry_msgs::Quaternion & robot_quat)
{ 
  get_robot_quat[0].x=roundf(robot_quat.x*10000)/10000; 
  get_robot_quat[0].y=roundf(robot_quat.y*10000)/10000; 
  get_robot_quat[0].z=roundf(robot_quat.z*10000)/10000; 
  get_robot_quat[0].w=roundf(robot_quat.w*10000)/10000; 
  //ROS_INFO("AMR 0 pos [%f,%f]",robot_pos[0].x,robot_pos[0].y);
}
void robot1_quatCB(const geometry_msgs::Quaternion & robot_quat)
{ get_robot_quat[1].x=roundf(robot_quat.x*10000)/10000; 
  get_robot_quat[1].y=roundf(robot_quat.y*10000)/10000; 
  get_robot_quat[1].z=roundf(robot_quat.z*10000)/10000; 
  get_robot_quat[1].w=roundf(robot_quat.w*10000)/10000;
}
void robot2_quatCB(const geometry_msgs::Quaternion & robot_quat)
{ get_robot_quat[2].x=roundf(robot_quat.x*10000)/10000; 
  get_robot_quat[2].y=roundf(robot_quat.y*10000)/10000; 
  get_robot_quat[2].z=roundf(robot_quat.z*10000)/10000; 
  get_robot_quat[2].w=roundf(robot_quat.w*10000)/10000;
}
void robot3_quatCB(const geometry_msgs::Quaternion & robot_quat)
{ get_robot_quat[3].x=roundf(robot_quat.x*10000)/10000; 
  get_robot_quat[3].y=roundf(robot_quat.y*10000)/10000; 
  get_robot_quat[3].z=roundf(robot_quat.z*10000)/10000; 
  get_robot_quat[3].w=roundf(robot_quat.w*10000)/10000;
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

 ros::Subscriber vl_angular_sub = nh.subscribe("vl_robot/pub_velocity", 1000, vl_angCB);

 ros::Subscriber robot0_quat_sub = nh.subscribe("amr_0/pub_quat", 1000, robot0_quatCB);
 ros::Subscriber robot1_quat_sub = nh.subscribe("amr_1/pub_quat", 1000, robot1_quatCB);
 ros::Subscriber robot2_quat_sub = nh.subscribe("amr_2/pub_quat", 1000, robot2_quatCB);
 ros::Subscriber robot3_quat_sub = nh.subscribe("amr_3/pub_quat", 1000, robot3_quatCB);
 //ros::Subscriber vl_quat_sub = nh.subscribe("vl_robot/pub_quat", 1000, Callback);
 //ros::Subscriber robot_pos_sub = nh.subscribe<multi_amr_nectec::pos_msg>("robot_pos", 1000, boost::bind(robot_pos_Callback,_1,team_size));
 ros::Publisher force0_pub = nh.advertise<geometry_msgs::Twist>("amr_0/cmd_vel", 1000);
 ros::Publisher force1_pub = nh.advertise<geometry_msgs::Twist>("amr_1/cmd_vel", 1000); 
 ros::Publisher force2_pub = nh.advertise<geometry_msgs::Twist>("amr_2/cmd_vel", 1000);
 ros::Publisher force3_pub = nh.advertise<geometry_msgs::Twist>("amr_3/cmd_vel", 1000);

/*
while (nh.ok()) 
{ 
   for (int i = 0; i < team_size; i++)
      {        //Calculate diffent angle here
                //transform ang          
             
              //ROS_INFO("robot pos=[%f,%f] ",robot_pos[i].x,robot_pos[i].y);               
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
*/
  //return 0;

}
