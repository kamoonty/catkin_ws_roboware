#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <std_msgs/Float32.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Twist.h>
#include <stdlib.h> 
#include <boost/lexical_cast.hpp>


int team_size; //use for get param from launch file
float Kij;
using namespace std;
std::vector<double> initial_pos_x;
std::vector<double> initial_pos_y;
// We need to round value after subscribe because if not it can cause problem
// when VL= 0.00000003 and Robot 1 Pos X = 0.00000004 it is not equal so useroundf (number*100)/100
pair<double, double> CalcF_ij(int i,int j);
int main(int argc, char** argv) 
{
 ros::init(argc, argv, "inter_agent_force");
 ros::NodeHandle nh;
 ros::Rate loopRate(20);
 //load param from launch file
 nh.getParam("inter_agent_force/team_size", team_size);
 nh.getParam("inter_agent_force/Kij", Kij);
 // load param for initial formation from YAML file

 nh.getParam("initial_pos_x",initial_pos_x);
 nh.getParam("initial_pos_y",initial_pos_y);

 ros::Publisher force0_pub = nh.advertise<geometry_msgs::Twist>("amr_0/cmd_vel", 1000);
 ros::Publisher force1_pub = nh.advertise<geometry_msgs::Twist>("amr_1/cmd_vel", 1000); 
 ros::Publisher force2_pub = nh.advertise<geometry_msgs::Twist>("amr_2/cmd_vel", 1000);
 ros::Publisher force3_pub = nh.advertise<geometry_msgs::Twist>("amr_3/cmd_vel", 1000);
 
 geometry_msgs::Twist send_Fij [team_size];
 geometry_msgs::Twist F_ij_node_left  [team_size];
 geometry_msgs::Twist F_ij_node_right [team_size];
 pair<double, double> F_ij;
while (nh.ok()) 
{ // robot 0 
  /*F_ij=CalcF_ij(0,1);
  F_ij_node_left[0].linear.x=F_ij.first;
  F_ij_node_left[0].linear.y=F_ij.second;
  F_ij=CalcF_ij(0,3);
  F_ij_node_right[0].linear.x=F_ij.first;              
  F_ij_node_right[0].linear.y=F_ij.second;
  //robot 1
  F_ij=CalcF_ij(1,2);
  F_ij_node_left[1].linear.x=F_ij.first;
  F_ij_node_left[1].linear.y=F_ij.second;
  F_ij=CalcF_ij(1,0);
  F_ij_node_right[1].linear.x=F_ij.first;              
  F_ij_node_right[1].linear.y=F_ij.second;
  //robot 2
  F_ij=CalcF_ij(2,3);
  F_ij_node_left[2].linear.x=F_ij.first;
  F_ij_node_left[2].linear.y=F_ij.second;
  F_ij=CalcF_ij(2,1);
  F_ij_node_right[2].linear.x=F_ij.first;              
  F_ij_node_right[2].linear.y=F_ij.second;
  // robot 3
  F_ij=CalcF_ij(3,0);
  F_ij_node_left[3].linear.x=F_ij.first;
  F_ij_node_left[3].linear.y=F_ij.second;
  F_ij=CalcF_ij(3,2);
  F_ij_node_right[3].linear.x=F_ij.first;              
  F_ij_node_right[3].linear.y=F_ij.second;
  */
  //for 2 robot 
  F_ij=CalcF_ij(0,1);
  F_ij_node_left[0].linear.x=F_ij.first;
  F_ij_node_left[0].linear.y=F_ij.second;
  F_ij=CalcF_ij(1,0);
  F_ij_node_left[1].linear.x=F_ij.first;
  F_ij_node_left[1].linear.y=F_ij.second;

  for (int n=0;n<team_size;n++)
{send_Fij[n].linear.x=F_ij_node_left[n].linear.x+F_ij_node_right[n].linear.x;  
  send_Fij[n].linear.y=F_ij_node_left[n].linear.y+F_ij_node_right[n].linear.y;  
ROS_INFO("Total Fij robot %d = [%.3f,%.3f]",n,send_Fij[n].linear.x,send_Fij[n].linear.y);                                 
}             
      force0_pub.publish(send_Fij[0]);
      force1_pub.publish(send_Fij[1]);
      force2_pub.publish(send_Fij[2]);
      force3_pub.publish(send_Fij[3]);          
      ros::spinOnce();
      loopRate.sleep();  
}
  //return 0;
}


pair<double, double> CalcF_ij(int i,int j)
{geometry_msgs::Twist Fi_to_j ;
 geometry_msgs::Point Dist_ij ;
 geometry_msgs::Point absolute_distance ;        
 tf::TransformListener listener;     
 tf::StampedTransform transform;
 pair<double, double> F_ij;
try{
 std::string robot_i ("/amr_");
 robot_i =robot_i+ boost::lexical_cast<std::string>(i);
 robot_i =robot_i+"/base_link";

 std::string robot_j ("/amr_");
 robot_j =robot_j+ boost::lexical_cast<std::string>(j);
 robot_j =robot_j+"/base_link";
    listener.waitForTransform(robot_i,robot_j, ros::Time(0), ros::Duration(10.0) );
    listener.lookupTransform(robot_i,robot_j,ros::Time(0), transform);
    }
    catch (tf::TransformException &ex) 
    {ROS_ERROR("%s",ex.what());
      ros::Duration(1.0).sleep();
     }
double x = transform.getOrigin().getX();
double y = transform.getOrigin().getY();
double th = tf::getYaw(transform.getRotation());                       
              int spring_state_x=0;
              int spring_state_y=0;
              int n=0;
               Dist_ij.x=x; // get distance between two robots from TF
               Dist_ij.y=y;
               if(Dist_ij.x<0)
               {spring_state_x=-1;}
               else if (Dist_ij.x>0)
               {spring_state_x=1;}
               
               if(Dist_ij.y<0)
               {spring_state_y=-1;}
               else if (Dist_ij.y>0)
               {spring_state_y=1;}
               ROS_INFO("Spring state (%d, %d)",spring_state_x,spring_state_y);
               ROS_INFO("Dist_ij [%f,%f]",Dist_ij.x,Dist_ij.y);
               // calculate initial distance for each pair of robots
               float initial_dij_x = sqrt(pow((initial_pos_x[i])-(initial_pos_x[j]),2)) ;         
               float initial_dij_y = sqrt(pow((initial_pos_y[i])-(initial_pos_y[j]),2)) ; 

                // Use fabs for float absolute
                absolute_distance.x=(fabs(Dist_ij.x)-initial_dij_x);
                absolute_distance.y=(fabs(Dist_ij.y)-initial_dij_y);            
               Fi_to_j.linear.x =Kij*spring_state_x*absolute_distance.x;
               Fi_to_j.linear.y =Kij*spring_state_y*absolute_distance.y; 
                   
                   //set Linear velocity threshold 
              if(Fi_to_j.linear.x>=0.5)
              {Fi_to_j.linear.x=0.5;
              ROS_INFO("Threshold Vx max");}
              else if (Fi_to_j.linear.x<=-0.5)
              {Fi_to_j.linear.x=-0.5;
                ROS_INFO("Threshold Vx min");}
              if(Fi_to_j.linear.y>=0.5)
              {Fi_to_j.linear.y=0.5;
              ROS_INFO("Threshold Vy max");}
              else if (Fi_to_j.linear.y<=-0.5)
              {Fi_to_j.linear.y=-0.5;
                ROS_INFO("Threshold Vy min");} 
                //Return result 
                F_ij.first=Fi_to_j.linear.x;
                F_ij.second=Fi_to_j.linear.y;
              ROS_INFO(" Calculated Fij of robot [%d,%d]= [%.3f,%.3f]",i,j,F_ij.first,F_ij.second);           
                ROS_INFO("----------------------------"); 
return F_ij;
}
