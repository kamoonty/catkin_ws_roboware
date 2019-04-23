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
geometry_msgs::Point get_vl;
geometry_msgs::Point robot_pos[10] ; //allocate for max 10 robots
//multi_amr_nectec::pos_msg get_msg;
int team_size; //use for get param
float Kvl;
float dist_from_vl_x ;
float dist_from_vl_y ;
// We need to round value after subscribe because if not it can cause problem
// when VL= 0.00000003 and Robot 1 Pos X = 0.00000004 it is not equal
// roundf (number*100)/100
void vl_posCB(const geometry_msgs::Point & vl_pos)
{  get_vl.x=roundf(vl_pos.x*10000)/10000; // round to 5 decimal place
   get_vl.y=roundf(vl_pos.y*10000)/10000;
  ROS_INFO("****Get VL Position [%f,%f]*****",get_vl.x,get_vl.y);
}
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
 nh.getParam("vl_force/team_size", team_size);
 nh.getParam("vl_force/Kvl", Kvl);
 nh.getParam("vl_force/dist_from_vl_x", dist_from_vl_x);
 nh.getParam("vl_force/dist_from_vl_y", dist_from_vl_y);
 //nh.getParam("vl_force/dist_from_vl_y_triangle", dist_from_vl_y_triangle);
 geometry_msgs::Twist send_fvl [team_size];
 geometry_msgs::Point Dist_vl [team_size];
 geometry_msgs::Point Force_vl [team_size];
 geometry_msgs::Point formation_pos[team_size];
 // Formation depend on those values below It is dVL in equation
 formation_pos[0].x=0;
 formation_pos[0].y=3;

 formation_pos[1].x=-3;
 formation_pos[1].y=0;

 formation_pos[2].x=0;
 formation_pos[2].y=-3;

 formation_pos[3].x=3;
 formation_pos[3].y=0;

 ros::Subscriber vl_pos_sub = nh.subscribe("vl_robot/pub_pos", 1000, vl_posCB);
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
   for (int j = 0; j < team_size; j++)
      {                   
              int unit_vec_x=0;
              int unit_vec_y=0;
              ROS_INFO("robot pos=[%f,%f] ",robot_pos[j].x,robot_pos[j].y);               
            
               Dist_vl[j].x=get_vl.x-robot_pos[j].x;
               Dist_vl[j].y=get_vl.y-robot_pos[j].y;
               if(Dist_vl[j].x<0)
               {unit_vec_x=-1;}
               else if (Dist_vl[j].x>0)
               {unit_vec_x=1;}
               
               if(Dist_vl[j].y<0)
               {unit_vec_y=-1;}
               else if (Dist_vl[j].y>0)
               {unit_vec_y=1;}
               float abs_dist = sqrt(pow((robot_pos[j].x-get_vl.x),2)+pow((robot_pos[j].y-get_vl.y),2)) ;         
               //ROS_INFO("Dist from VL of AMR %d=[%f,%f]",j,Dist_vl[j].x,Dist_vl[j].y);
               //ROS_INFO("Absolute distance of AMR %d from VL =%f",j,abs_dist);
               ROS_INFO("Ux= %d Uy= %d",unit_vec_x,unit_vec_y);
               ROS_INFO("Dist_vl [%f,%f]",Dist_vl[j].x,Dist_vl[j].y);
               float abs_dist_vl_x=abs(Dist_vl[j].x);
               float abs_dist_vl_y=abs(Dist_vl[j].y);
               ROS_INFO("ABS dist from VL =[%f,%f]",abs_dist_vl_x,abs_dist_vl_y);
                Force_vl[j].x=Kvl*(abs(Dist_vl[j].x)-abs(formation_pos[j].x));
                Force_vl[j].y=Kvl*(abs(Dist_vl[j].y)-abs(formation_pos[j].y));            
                ROS_INFO("Virtual Force of robot %d[%.3f,%.3f]",j,Force_vl[j].x,Force_vl[j].y);           
                  send_fvl[j].linear.x =unit_vec_x*Force_vl[j].x;
                  send_fvl[j].linear.y =unit_vec_y*Force_vl[j].y;  
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
