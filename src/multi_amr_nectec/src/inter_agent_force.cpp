#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <boost/lexical_cast.hpp>
#include <std_msgs/Float32.h>
//#include <geometry_msgs/Point32.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Twist.h>
#include <stdlib.h> 
#include "multi_amr_nectec/pos_msg.h"
#include "math.h"
//#include "std_msgs/String.h"
//#include <sstream>

geometry_msgs::Point get_vl;
geometry_msgs::Point robot_pos[10] ; //allocate for max 10 robots
multi_amr_nectec::pos_msg get_msg;
int team_size; //use for get param
float Kvl;
float dist_from_vl_x ;
float dist_from_vl_y ;


// We need to round value after subscribe because if not it can cause problem
// when VL= 0.00000003 and Robot 1 Pos X = 0.00000004 it is not equal
// roundf (number*100)/100
void VL_Callback(const geometry_msgs::Point & vl_pos)
{  get_vl.x=roundf(vl_pos.x*1)/1; // round to 5 decimal place
   get_vl.y=roundf(vl_pos.y*1)/1;
  ROS_INFO("Get VL Position [%f,%f]",get_vl.x,get_vl.y);
}

void robot_pos_Callback(const multi_amr_nectec::pos_msg::ConstPtr& msg,int index) 
{ for (int i = 0; i<index; i++)
    { robot_pos[i].x=roundf((msg->point_robot[i].x)*1)/1; // round to 5 decimal place
      robot_pos[i].y=roundf((msg->point_robot[i].y)*1)/1;
       //ROS_INFO("Get AMR %d Pos : x=%f, y=%f",i, robot_pos[i].x, robot_pos[i].y);
    }
}   

int main(int argc, char** argv) 
{
 ros::init(argc, argv, "vl_force");
 ros::NodeHandle nh;
 ros::Rate loopRate(1);
 nh.getParam("vl_force/team_size", team_size);
 nh.getParam("vl_force/Kvl", Kvl);
 nh.getParam("vl_force/dist_from_vl_x", dist_from_vl_x);
 nh.getParam("vl_force/dist_from_vl_y", dist_from_vl_y);
 //nh.getParam("vl_force/dist_from_vl_y_triangle", dist_from_vl_y_triangle);
 geometry_msgs::Twist send_fvl [team_size];
 geometry_msgs::Point Dist_vl [team_size];
 geometry_msgs::Point Force_vl [team_size];



 ros::Subscriber vl_sub = nh.subscribe("vl_pos", 1000, VL_Callback);
 ros::Subscriber robot_pos_sub = nh.subscribe<multi_amr_nectec::pos_msg>("robot_pos", 1000, boost::bind(robot_pos_Callback,_1,team_size));
 
 ros::Publisher force0_pub = nh.advertise<geometry_msgs::Twist>("amr_0/cmd_vel", 1000);
 ros::Publisher force1_pub = nh.advertise<geometry_msgs::Twist>("amr_1/cmd_vel", 1000); 
 ros::Publisher force2_pub = nh.advertise<geometry_msgs::Twist>("amr_2/cmd_vel", 1000);
 ros::Publisher force3_pub = nh.advertise<geometry_msgs::Twist>("amr_3/cmd_vel", 1000);

while (nh.ok()) 
{ 
   for (int j = 0; j < team_size; j++)
      {          
                int check_x=1;
                int check_y=1;
               ROS_INFO("robot pos=[%f,%f] ",robot_pos[j].x,robot_pos[j].y);
              
              if(robot_pos[j].x>get_vl.x)
                    {check_x=-1; ROS_INFO("check_x= -1 ");}        
               else if(robot_pos[j].x<get_vl.x)
                    {check_x=1; ROS_INFO("check_x= 1 ");}                   
               else 
                    {check_x=0;ROS_INFO("check_x= 0");
                     }  
              //check_y 
               if(robot_pos[j].y>get_vl.y)
                    {check_y=-1;  ROS_INFO("check_y= -1 ");}
               else if (robot_pos[j].y<get_vl.y)
                    {check_y=1; ROS_INFO("check_y= 1 ");}
               else 
                    {check_y=0; ROS_INFO("check_y= 0 ");}     
               


               Dist_vl[j].x=get_vl.x-robot_pos[j].x;
               Dist_vl[j].y=get_vl.y-robot_pos[j].y;
               float abs_dist = sqrt(pow((robot_pos[j].x-get_vl.x),2)+pow((robot_pos[j].y-get_vl.y),2)) ;         
               //ROS_INFO("Dist from VL of AMR %d=[%f,%f]",j,Dist_vl[j].x,Dist_vl[j].y);
               //ROS_INFO("Absolute distance of AMR %d from VL =%f",j,abs_dist);
                Force_vl[j].x=Kvl*(Dist_vl[j].x-check_x*(dist_from_vl_x));
                Force_vl[j].y=Kvl*(Dist_vl[j].y-check_y*(dist_from_vl_y));            
                //ROS_INFO("Virtual Force of robot %d[%.3f,%.3f]",j,Force_vl[j].x,Force_vl[j].y);           
                  send_fvl[j].linear.x =Force_vl[j].x;
                  send_fvl[j].linear.y =Force_vl[j].y;  
                 ROS_INFO("Cmd_vel robot %d x=%f y=%f",j, send_fvl[j].linear.x,send_fvl[j].linear.y);  
                 ROS_INFO("-----------------------");
                }
                
                force0_pub.publish(send_fvl[0]);
                force1_pub.publish(send_fvl[1]);
                force2_pub.publish(send_fvl[2]);
                force3_pub.publish(send_fvl[3]);
              
      //ROS_INFO("-------SEND CMD VEL------");
      ros::spinOnce();
      loopRate.sleep();

}

  //return 0;

}
