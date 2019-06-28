#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <std_msgs/Float32.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Twist.h>
#include <stdlib.h> 
#include <boost/lexical_cast.hpp>

#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"
#include "std_msgs/Float32MultiArray.h"
int team_size; //use for get param from launch file
float Kvl,Cvl;

int main(int argc, char** argv) 
{
 ros::init(argc, argv, "vl_force");
 ros::NodeHandle nh;
 ros::Rate loopRate(20);
 float diff_time=0.05; //20Hz=0.05 sec
 //ros::Time prev_time;
 //ros::Duration diff_time;
 //load param from launch file
 nh.getParam("vl_force/team_size", team_size);
 nh.getParam("vl_force/Kvl", Kvl);
 nh.getParam("vl_force/Cvl", Cvl);
 // load param for initial formation from YAML file
 std::vector<double> initial_pos_x;
 std::vector<double> initial_pos_y;
 nh.getParam("initial_pos_x",initial_pos_x);
 nh.getParam("initial_pos_y",initial_pos_y);

 ros::Publisher pub_cmd_vel_x = nh.advertise<std_msgs::Float32MultiArray>("F_vl_x", 100);
 ros::Publisher pub_cmd_vel_y = nh.advertise<std_msgs::Float32MultiArray>("F_vl_y", 100);
 geometry_msgs::Twist send_fvl [team_size];
 geometry_msgs::Point Dist_vl [team_size];
 geometry_msgs::Point absolute_distance [team_size];
 geometry_msgs::Point first_data [team_size];
 geometry_msgs::Point second_data [team_size];
 geometry_msgs::Point diff_value [team_size];
 tf::TransformListener listener;
while (nh.ok()) 
{  std_msgs::Float32MultiArray robot_cmd_vel_linear_x;
   std_msgs::Float32MultiArray robot_cmd_vel_linear_y;
   robot_cmd_vel_linear_x.data.clear();
   robot_cmd_vel_linear_y.data.clear();
   for (int i = 0; i < team_size; i++)
      {  
 tf::StampedTransform transform;
try{std::string follower_robot ("/amr_");
 std::string leader_robot ("/base_link");
 follower_robot =follower_robot+ boost::lexical_cast<std::string>(i);
 follower_robot =follower_robot+"/base_link";
 
    listener.waitForTransform(follower_robot,leader_robot, ros::Time(0), ros::Duration(10.0) );
    listener.lookupTransform(follower_robot,leader_robot,ros::Time(0), transform);
    //base_link is refer to virtual leader robot
    // we should replace to vl_robot/base_link later
    }
    catch (tf::TransformException &ex) {
      ROS_ERROR("%s",ex.what());
      ros::Duration(1.0).sleep();
      continue;
    }
double x = transform.getOrigin().getX();
double y = transform.getOrigin().getY();
double th = tf::getYaw(transform.getRotation());                       
              int spring_state_x=0;
              int spring_state_y=0;
        
               Dist_vl[i].x=x;
               Dist_vl[i].y=y;
               if(Dist_vl[i].x<0)
               {spring_state_x=-1;}
               else if (Dist_vl[i].x>0)
               {spring_state_x=1;}
               
               if(Dist_vl[i].y<0)
               {spring_state_y=-1;}
               else if (Dist_vl[i].y>0)
               {spring_state_y=1;}
               //float abs_dist = sqrt(pow((robot_pos[i].x-get_pos_vl.x),2)+pow((robot_pos[i].y-get_pos_vl.y),2)) ;           
               //ROS_INFO("Dist from VL of AMR %d=[%f,%f]",i,Dist_vl[i].x,Dist_vl[i].y);
               //ROS_INFO("Absolute distance of AMR %d from VL =%f",i,abs_dist);
               ROS_INFO("Spring state=[%d,%d]",spring_state_x,spring_state_y);
               ROS_INFO("Dist_vl [%f,%f]",Dist_vl[i].x,Dist_vl[i].y);
                absolute_distance[i].x=(fabs(Dist_vl[i].x)-fabs(initial_pos_x[i]));
                absolute_distance[i].y=(fabs(Dist_vl[i].y)-fabs(initial_pos_y[i]));            
                ROS_INFO("Absolute distance of robot %d[%.3f,%.3f]",i,absolute_distance[i].x,absolute_distance[i].y);           
     
      // calculate delta_t
        //rate = 20Hz
         first_data[i].x= absolute_distance[i].x;
         first_data[i].y= absolute_distance[i].y;
      if(second_data[i].x!=0&&second_data[i].y!=0)
       {  ROS_INFO("first_data robot %d= [%f,%f]",i,first_data[i].x,first_data[i].y);
         ROS_INFO("second_data robot %d= [%f,%f]",i,second_data[i].x,second_data[i].y);
        diff_value[i].x= (fabs(first_data[i].x)-fabs(second_data[i].x))/diff_time;
        diff_value[i].y= (fabs(first_data[i].y)-fabs(second_data[i].y))/diff_time;
       second_data[i].x=first_data[i].x;
       second_data[i].y=first_data[i].y;
       ROS_INFO("Diff of robot %d = [%f,%f]",i,diff_value[i].x,diff_value[i].y);
       }
       else
       {second_data[i].x=first_data[i].x;
       second_data[i].y=first_data[i].y;
       ROS_INFO("!!!!Enter First loop!!!");
       }     
                  send_fvl[i].linear.x =spring_state_x*(Kvl*absolute_distance[i].x+Cvl*diff_value[i].x);
                  send_fvl[i].linear.y =spring_state_y*(Kvl*absolute_distance[i].y+Cvl*diff_value[i].y);                    
                ROS_INFO("F_vl of robot %d x=%f y=%f",i, send_fvl[i].linear.x,send_fvl[i].linear.y);  
                ROS_INFO("-----------------------");
                
                robot_cmd_vel_linear_x.data.push_back(send_fvl[i].linear.x);
                robot_cmd_vel_linear_y.data.push_back(send_fvl[i].linear.y);
                }              
           
      pub_cmd_vel_x.publish(robot_cmd_vel_linear_x);
      pub_cmd_vel_y.publish(robot_cmd_vel_linear_y);
      ros::spinOnce();
      loopRate.sleep();

}

  //return 0;

}
