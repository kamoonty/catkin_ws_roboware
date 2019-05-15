#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <std_msgs/Float32.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Twist.h>
#include <stdlib.h> 
//#include "multi_amr_nectec/pos_msg.h"
//#include "math.h"
//#include "std_msgs/String.h"
geometry_msgs::Point get_pos_vl;
geometry_msgs::Point robot_pos[10] ; //allocate for max 10 robots
//geometry_msgs::Twist get_angular_vl;
//multi_amr_nectec::pos_msg get_msg;
int team_size; //use for get param from launch file
float Kvl;
// We need to round value after subscribe because if not it can cause problem
// when VL= 0.00000003 and Robot 1 Pos X = 0.00000004 it is not equal so useroundf (number*100)/100
void vl_posCB(const geometry_msgs::Point & vl_pos)
{  get_pos_vl.x=roundf(vl_pos.x*10000)/10000; // round to 5 decimal place
   get_pos_vl.y=roundf(vl_pos.y*10000)/10000;
  ROS_INFO("****Get VL Position [%f,%f]*****",get_pos_vl.x,get_pos_vl.y);
}
/*
void vl_angCB(const geometry_msgs::Twist & robot_velocity)
{ get_angular_vl.angular.z=roundf(robot_velocity.angular.z*10000)/10000; // round to 5 decimal place
  ROS_INFO("**** VL Yaw velocity [%f]*****",get_angular_vl.angular.z);
}
*/
void robot0_posCB(const geometry_msgs::Point & pos)
{  robot_pos[0].x=roundf(pos.x*10000)/10000; // round to 5 decimal place
   robot_pos[0].y=roundf(pos.y*10000)/10000;
  //ROS_INFO("AMR 0 pos [%f,%f]",robot_pos[0].x,robot_pos[0].y);
}
void robot1_posCB(const geometry_msgs::Point & pos)
{  robot_pos[1].x=roundf(pos.x*10000)/10000; // round to 5 decimal place
   robot_pos[1].y=roundf(pos.y*10000)/10000;
}
void robot2_posCB(const geometry_msgs::Point & pos)
{  robot_pos[2].x=roundf(pos.x*10000)/10000; // round to 5 decimal place
   robot_pos[2].y=roundf(pos.y*10000)/10000;
}
void robot3_posCB(const geometry_msgs::Point & pos)
{  robot_pos[3].x=roundf(pos.x*10000)/10000; // round to 5 decimal place
   robot_pos[3].y=roundf(pos.y*10000)/10000;
}
int main(int argc, char** argv) 
{
 ros::init(argc, argv, "vl_force");
 ros::NodeHandle nh;
 ros::Rate loopRate(20);
 //load param from launch file
 nh.getParam("vl_force/team_size", team_size);
 nh.getParam("vl_force/Kvl", Kvl);
 // load param for initial formation from YAML file
 std::vector<double> initial_pos_x;
 std::vector<double> initial_pos_y;
 nh.getParam("initial_pos_x",initial_pos_x);
 nh.getParam("initial_pos_y",initial_pos_y);

 geometry_msgs::Twist send_fvl [team_size];
 geometry_msgs::Point Dist_vl [team_size];
 geometry_msgs::Point Force_vl [team_size];

 ros::Subscriber vl_pos_sub = nh.subscribe("vl_robot/pub_pos", 1000, vl_posCB);
 //ros::Subscriber vl_angular_sub = nh.subscribe("vl_robot/pub_velocity", 1000, vl_angCB);
 
 ros::Subscriber robot0_pos_sub = nh.subscribe("amr_0/pub_pos", 1000, robot0_posCB);
 ros::Subscriber robot1_pos_sub = nh.subscribe("amr_1/pub_pos", 1000, robot1_posCB);
 ros::Subscriber robot2_pos_sub = nh.subscribe("amr_2/pub_pos", 1000, robot2_posCB);
 ros::Subscriber robot3_pos_sub = nh.subscribe("amr_3/pub_pos", 1000, robot3_posCB);
 //ros::Subscriber vl_quat_sub = nh.subscribe("vl_robot/pub_quat", 1000, Callback);
 //ros::Subscriber robot_pos_sub = nh.subscribe<multi_amr_nectec::pos_msg>("robot_pos", 1000, boost::bind(robot_pos_Callback,_1,team_size));
 ros::Publisher force0_pub = nh.advertise<geometry_msgs::Twist>("amr_0/cmd_vel", 1000);
 ros::Publisher force1_pub = nh.advertise<geometry_msgs::Twist>("amr_1/cmd_vel", 1000); 
 ros::Publisher force2_pub = nh.advertise<geometry_msgs::Twist>("amr_2/cmd_vel", 1000);
 ros::Publisher force3_pub = nh.advertise<geometry_msgs::Twist>("amr_3/cmd_vel", 1000);
 

while (nh.ok()) 
{ 
   for (int i = 0; i < team_size; i++)
      {                  
              int unit_vec_x=0;
              int unit_vec_y=0;
              ROS_INFO("robot pos=[%f,%f] ",robot_pos[i].x,robot_pos[i].y);               
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
                  //send_fvl[i].angular.z=get_angular_vl.angular.z; 
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
