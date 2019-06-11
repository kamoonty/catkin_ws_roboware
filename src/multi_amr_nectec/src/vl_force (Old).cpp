#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <std_msgs/Float32.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Twist.h>
#include <stdlib.h> 
#include <geometry_msgs/Pose2D.h>
//#include "multi_amr_nectec/pos_msg.h"
//#include "math.h"
//#include "std_msgs/String.h"
geometry_msgs::Point get_pos_vl;
geometry_msgs::Point robot_pos[10] ; //allocate for max 10 robots
geometry_msgs::Pose2D get_pose2d_agent [10]; //allocate for max 10 robots
geometry_msgs::Pose2D get_pose2d_vl;

int team_size; //use for get param from launch file
float Kvl;
// We need to round value after subscribe because if not it can cause problem
// when VL= 0.00000003 and Robot 1 Pos X = 0.00000004 it is not equal so useroundf (number*100)/100
void vl_posCB(const geometry_msgs::Point & vl_pos)
{  get_pos_vl.x=roundf(vl_pos.x*10000)/10000; // round to 5 decimal place
   get_pos_vl.y=roundf(vl_pos.y*10000)/10000;
  //ROS_INFO("****Get VL Position [%f,%f]*****",get_pos_vl.x,get_pos_vl.y);
}
void vl_pose2D_CB(const geometry_msgs::Pose2D & vl_pose2d) //robot pose 2d contain x y pos and theta (yaw position)
{ get_pose2d_vl.theta=roundf(vl_pose2d.theta*10000)/10000;
//ROS_INFO("**** VL angle(theta)= [%f]*****", get_pose2d_vl.theta);
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
/*
float convert_to_degree(float theta)
{            
  if(theta<0)
    {//ROS_INFO("Theta<0");  
    theta =(2*M_PI)+theta;
    theta=(theta/M_PI)*180;}
else theta=(theta/M_PI)*180;
return theta;
} */
struct rotate_matrix
{
   float  x_rotated;;    
   float  y_rotated;;
};

struct rotate_matrix rotation(float x,float y,float theta)
{
   struct rotate_matrix obj;        /*structure object which contains both*/ 
   if(theta>=0)
  { obj.x_rotated=x*cos(theta)-y*sin(theta);
   obj.y_rotated=x*sin(theta)+y*cos(theta);
   ROS_INFO("Case theta>0 [%f,%f]",obj.x_rotated,obj.y_rotated);}
  else
  {obj.x_rotated=x*cos(theta)+y*sin(theta);
  obj.y_rotated=-x*sin(theta)+y*cos(theta);
  ROS_INFO("Case theta<0 [%f,%f]",obj.x_rotated,obj.y_rotated);}
   return obj;
}
/*
void rotation_matrix(float* x, float* y,float theta)
{if(theta>=0)
  {*x=(*x)*cos(theta)-(*y)*sin(theta);
  *y=(*x)*sin(theta)+(*y)*cos(theta);}
else
  {*x=(*x)*cos(theta)+(*y)*sin(theta);
  *y=-(*x)*sin(theta)+(*y)*cos(theta);}
}*/

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
 ros::Subscriber vl_pos_sub = nh.subscribe("vl_robot/pub_pos", 1000, vl_posCB);
 //ros::Subscriber vl_angular_sub = nh.subscribe("vl_robot/pub_velocity", 1000, vl_angCB);
 
 ros::Subscriber robot0_pos_sub = nh.subscribe("amr_0/pub_pos", 1000, robot0_posCB);
 ros::Subscriber robot1_pos_sub = nh.subscribe("amr_1/pub_pos", 1000, robot1_posCB);
 ros::Subscriber robot2_pos_sub = nh.subscribe("amr_2/pub_pos", 1000, robot2_posCB);
 ros::Subscriber robot3_pos_sub = nh.subscribe("amr_3/pub_pos", 1000, robot3_posCB);
 ros::Subscriber vl_pose2d_sub = nh.subscribe("vl_robot/pose2d", 1000, vl_pose2D_CB);
 ros::Subscriber agent0_pose2d_sub = nh.subscribe("amr_0/pose2d", 1000, agent0_pose2D_CB);
 ros::Subscriber agent1_pose2d_sub = nh.subscribe("amr_1/pose2d", 1000, agent1_pose2D_CB);
 ros::Subscriber agent2_pose2d_sub = nh.subscribe("amr_2/pose2d", 1000, agent2_pose2D_CB);
 ros::Subscriber agent3_pose2d_sub = nh.subscribe("amr_3/pose2d", 1000, agent3_pose2D_CB);

 ros::Publisher force0_pub = nh.advertise<geometry_msgs::Twist>("amr_0/cmd_vel", 1000);
 ros::Publisher force1_pub = nh.advertise<geometry_msgs::Twist>("amr_1/cmd_vel", 1000); 
 ros::Publisher force2_pub = nh.advertise<geometry_msgs::Twist>("amr_2/cmd_vel", 1000);
 ros::Publisher force3_pub = nh.advertise<geometry_msgs::Twist>("amr_3/cmd_vel", 1000);
 geometry_msgs::Twist send_fvl [team_size];
 geometry_msgs::Point Dist_vl [team_size];
 geometry_msgs::Point Absolute_dist [team_size];

while (nh.ok()) 
{ 
   for (int i = 0; i < team_size; i++)
      {                  
              int spring_state_x=0;
              int spring_state_y=0;
              float sum_magnitude=0;
              float robot_theta=0;
              robot_theta=get_pose2d_agent[i].theta;
              ROS_INFO("robot %d pos=[%f,%f] ",i,robot_pos[i].x,robot_pos[i].y); 
              struct rotate_matrix  vl_rotate =rotation(get_pos_vl.x,get_pos_vl.y,robot_theta);
              //ROS_INFO("VL rotate %f rad=[%f,%f]",robot_theta,vl_rotate.x_rotated,vl_rotate.y_rotated);
              struct rotate_matrix  agent_rotate =rotation(robot_pos[i].x,robot_pos[i].y,robot_theta);
              
               //ROS_INFO("Agent %d rotate %f rad =[%f,%f]",i,robot_theta,agent_rotate.x_rotated,agent_rotate.y_rotated);
               //Dist_vl[i].x=get_pos_vl.x-robot_pos[i].x;
               //Dist_vl[i].y=get_pos_vl.y-robot_pos[i].y;
               Dist_vl[i].x=vl_rotate.x_rotated-agent_rotate.x_rotated;
               Dist_vl[i].y=vl_rotate.y_rotated-agent_rotate.y_rotated;
               if(Dist_vl[i].x<0)
               {spring_state_x=-1;} // stretch spring
               
               else if (Dist_vl[i].x>0)
               {spring_state_x=1;} // push spring
               
               if(Dist_vl[i].y<0)
               {spring_state_y=-1;}
               else if (Dist_vl[i].y>0)
               {spring_state_y=1;}
               //float abs_dist = sqrt(pow((robot_pos[i].x-get_pos_vl.x),2)+pow((robot_pos[i].y-get_pos_vl.y),2)) ;         
               //ROS_INFO("Dist from VL of AMR %d=[%f,%f]",i,Dist_vl[i].x,Dist_vl[i].y);
               //ROS_INFO("Absolute distance of AMR %d from VL =%f",i,abs_dist);
               ROS_INFO("state_x= %d state_y= %d",spring_state_x,spring_state_y);
               ROS_INFO("Dist_vl [%f,%f]",Dist_vl[i].x,Dist_vl[i].y);
               //double abs_dist_vl_x=fabs(Dist_vl[i].x); 
               //double abs_dist_vl_y=fabs(Dist_vl[i].y);
               //ROS_INFO("ABS dist_VL =[%f,%f]",abs_dist_vl_x,abs_dist_vl_y);
                // Use fabs for float absolute
                Absolute_dist[i].x=fabs(fabs(Dist_vl[i].x)-fabs(initial_pos_x[i]));
                Absolute_dist[i].y=fabs(fabs(Dist_vl[i].y)-fabs(initial_pos_y[i]));            
                sum_magnitude=sqrt(pow(Absolute_dist[i].x,2)+pow(Absolute_dist[i].y,2)) ; 
                
                //ROS_INFO("Theta=%f  Cos=%f Sin=%f",robot_theta,cos(robot_theta),sin(robot_theta));
                ROS_INFO("Absolute dist of robot %d[%f,%f]",i,Absolute_dist[i].x,Absolute_dist[i].y);           
                  ROS_INFO("Sum magnitude =%f",sum_magnitude);
                
                  send_fvl[i].linear.x =cos(robot_theta)* Kvl*spring_state_x*sum_magnitude;
                  send_fvl[i].linear.y =sin(robot_theta)* Kvl*spring_state_y*sum_magnitude; 
              
              //set Linear velocity threshold 
              if(send_fvl[i].linear.x>=1)
              {send_fvl[i].linear.x=1;
              ROS_INFO("Threshold Vx max");}
              else if (send_fvl[i].linear.x<=-1)
              {send_fvl[i].linear.x=-1;
                ROS_INFO("Threshold Vx min");}
              if(send_fvl[i].linear.y>=1)
              {send_fvl[i].linear.y=1;
              ROS_INFO("Threshold Vy max");}
              else if (send_fvl[i].linear.y<=-1)
              {send_fvl[i].linear.y=-1;
                ROS_INFO("Threshold Vy min");}
  
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
