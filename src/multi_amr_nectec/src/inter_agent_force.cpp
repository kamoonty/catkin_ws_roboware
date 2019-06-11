#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <std_msgs/Float32.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Twist.h>
#include <stdlib.h> 
#include <boost/lexical_cast.hpp>
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
 
 geometry_msgs::Twist send_Fij [team_size];
 geometry_msgs::Point Dist_ij [team_size];
 geometry_msgs::Point absolute_distance [team_size];
 tf::TransformListener listener;
 
while (nh.ok()) 
{ 
   for (int n = 0; n < team_size; n++)    
{     int i= n; //i= 0 1 2 3
      int j=n+1; // neighbor robot , j= 1 2 3 0
      if (i=team_size-1)  // closed loop robot position 
        {j=0;}
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
    catch (tf::TransformException &ex) 
    {ROS_ERROR("%s",ex.what());
      ros::Duration(1.0).sleep();
      continue;}
double x = transform.getOrigin().getX();
double y = transform.getOrigin().getY();
double th = tf::getYaw(transform.getRotation());                       
              int spring_state_x=0;
              int spring_state_y=0;

               Dist_ij[n].x=x; // get distance between two robots from TF
               Dist_ij[n].y=y;
               if(Dist_ij[n].x<0)
               {spring_state_x=-1;}
               else if (Dist_ij[n].x>0)
               {spring_state_x=1;}
               
               if(Dist_ij[n].y<0)
               {spring_state_y=-1;}
               else if (Dist_ij[n].y>0)
               {spring_state_y=1;}
               ROS_INFO("Spring state (%d, %d)",spring_state_x,spring_state_y);
               ROS_INFO("Dist_ij [%f,%f]",Dist_ij[n].x,Dist_ij[n].y);
               // calculate initial distance for each pair of robots
               float initial_dij_x = sqrt(pow((initial_pos_x[i])-(initial_pos_x[j]),2)) ;         
               float initial_dij_y = sqrt(pow((initial_pos_y[i])-(initial_pos_y[j]),2)) ; 


                // Use fabs for float absolute
                absolute_distance[i].x=(fabs(Dist_ij[i].x)-fabs(initial_pos_x[i]));
                absolute_distance[i].y=(fabs(Dist_ij[i].y)-fabs(initial_pos_y[i]));            
                ROS_INFO("Virtual Force of robot %d[%.3f,%.3f]",i,absolute_distance[i].x,absolute_distance[i].y);           
                  send_Fij[i].linear.x =Kij*spring_state_x*absolute_distance[i].x;
                  send_Fij[i].linear.y =Kij*spring_state_y*absolute_distance[i].y; 
                   //set Linear velocity threshold 
              if(send_Fij[i].linear.x>=1)
              {send_Fij[i].linear.x=1;
              ROS_INFO("Threshold Vx max");}
              else if (send_Fij[i].linear.x<=-1)
              {send_Fij[i].linear.x=-1;
                ROS_INFO("Threshold Vx min");}
              if(send_Fij[i].linear.y>=1)
              {send_Fij[i].linear.y=1;
              ROS_INFO("Threshold Vy max");}
              else if (send_Fij[i].linear.y<=-1)
              {send_Fij[i].linear.y=-1;
                ROS_INFO("Threshold Vy min");}
                  //send_Fij[i].angular.z=get_angular_vl.angular.z; 
                ROS_INFO("Cmd_vel robot %d x=%f y=%f",i, send_Fij[i].linear.x,send_Fij[i].linear.y);  
                ROS_INFO("-----------------------");
         
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
