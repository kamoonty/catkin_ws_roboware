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

// We need to round value after subscribe because if not it can cause problem
// when VL= 0.00000003 and Robot 1 Pos X = 0.00000004 it is not equal so useroundf (number*100)/100
int main(int argc, char** argv) 
{
 ros::init(argc, argv, "inter_agent_force");
 ros::NodeHandle nh;
 ros::Rate loopRate(20);
 //load param from launch file
 nh.getParam("inter_agent_force/team_size", team_size);
 nh.getParam("inter_agent_force/Kij", Kij);
 // load param for initial formation from YAML file
 
 std::vector<double> initial_pos_x;
 std::vector<double> initial_pos_y;
 nh.getParam("initial_pos_x",initial_pos_x);
 nh.getParam("initial_pos_y",initial_pos_y);

 ros::Publisher force0_pub = nh.advertise<geometry_msgs::Twist>("amr_0/cmd_vel", 1000);
 ros::Publisher force1_pub = nh.advertise<geometry_msgs::Twist>("amr_1/cmd_vel", 1000); 
 ros::Publisher force2_pub = nh.advertise<geometry_msgs::Twist>("amr_2/cmd_vel", 1000);
 ros::Publisher force3_pub = nh.advertise<geometry_msgs::Twist>("amr_3/cmd_vel", 1000);
 
 geometry_msgs::Twist send_force [team_size];
 geometry_msgs::Twist F_ij [team_size];
 geometry_msgs::Twist F_ji [team_size];
 tf::TransformListener listener;
 geometry_msgs::Twist Fi_to_j ;
 geometry_msgs::Twist Fj_to_i ;
 geometry_msgs::Point Dist_ij ;
 geometry_msgs::Point absolute_distance ; 
while (nh.ok()) 
{
 for(int n=0;n<team_size;n++)
 { 
 int i=n;   //i=0 1 2 3
 int j=n+1; //j=1 2 3 0
 if(j==team_size) {j=0;}  
 tf::StampedTransform transform;
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
    catch (tf::TransformException &ex) {
      ROS_ERROR("%s",ex.what());
      ros::Duration(1.0).sleep();
      continue;
    }
// get distance between two robots from TF
double x = transform.getOrigin().getX();
double y = transform.getOrigin().getY();
double th = tf::getYaw(transform.getRotation());                       
              int spring_state_x=0;
              int spring_state_y=0;
         
               Dist_ij.x=x; 
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
               ROS_INFO("Initial dist =[%f,%f]",initial_dij_x,initial_dij_y);
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
                Fj_to_i.linear.x=-Fi_to_j.linear.x;
                Fj_to_i.linear.y=-Fi_to_j.linear.y;
              ROS_INFO(" Calculated Fij of robot [%d,%d]= [%.3f,%.3f]",i,j,Fi_to_j.linear.x,Fi_to_j.linear.y);           
              ROS_INFO(" Calculated Fji of robot [%d,%d]= [%.3f,%.3f]",j,i,Fj_to_i.linear.x,Fj_to_i.linear.y);           
              ROS_INFO("----------------------------"); 
              F_ij[n].linear.x=Fi_to_j.linear.x;
              F_ij[n].linear.y=Fi_to_j.linear.y; 

              F_ji[n].linear.x=Fj_to_i.linear.x;
              F_ji[n].linear.y=Fj_to_i.linear.y;
 }



// the value of F_ji depend on the robot position or robot order in formation
send_force[0].linear.x= F_ij[0].linear.x+F_ji[3].linear.x;
send_force[0].linear.y= F_ij[0].linear.y+F_ji[3].linear.y;

send_force[1].linear.x= F_ij[1].linear.x+F_ji[0].linear.x;
send_force[1].linear.y= F_ij[1].linear.y+F_ji[0].linear.y;

send_force[2].linear.x= F_ij[2].linear.x+F_ji[1].linear.x;
send_force[2].linear.y= F_ij[2].linear.y+F_ji[1].linear.y;

send_force[3].linear.x= F_ij[3].linear.x+F_ji[2].linear.x;
send_force[3].linear.y= F_ij[3].linear.y+F_ji[2].linear.y;

  for(int n=0;n<team_size;n++)
  {ROS_INFO("cmd_vel of amr %d=[%f,%f]",n,send_force[n].linear.x,send_force[n].linear.x); 
  }
      force0_pub.publish(send_force[0]);
      force1_pub.publish(send_force[1]);
      force2_pub.publish(send_force[2]);
      force3_pub.publish(send_force[3]);     
          
      ros::spinOnce();
      loopRate.sleep();  
}
  //return 0;
}

