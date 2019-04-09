/*
 *
 *  Created on: Mar 27, 2019
 *      Author: Kanin Soloist
 */

#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <boost/lexical_cast.hpp>
#include <std_msgs/Float32.h>
#include <geometry_msgs/Point32.h>
#include <geometry_msgs/Twist.h>
#include <stdlib.h>
//#include <sstream>
#include "geometry_msgs/Point.h"
#include "multi_amr_nectec/pos_msg.h"
#include <vector> 
// global variable here
using namespace std;
string tf_prefix;
pair<double, double> getRobotPosition(int robot_no);
struct Point {
    float x;
    float y;
};
int main(int argc, char** argv) {
    ros::init(argc, argv, "Virtual_Leader_pos");
    ros::NodeHandle nh;
	// Get tf_prefix from the parameter server
	nh.getParam("tf_prefix", tf_prefix);
   // nh.getParam("team_size", team_size);
 
    ros::Publisher vl_pos_pub = nh.advertise<geometry_msgs::Point32>("vl_pos", 1000);
    // send array
    ros::Publisher robot_pos_pub = nh.advertise<multi_amr_nectec::pos_msg>("robot_pos",1000);
    
    ros::Publisher force0_pub = nh.advertise<geometry_msgs::Twist>("amr_0/cmd_vel", 1000);
    ros::Publisher force1_pub = nh.advertise<geometry_msgs::Twist>("amr_1/cmd_vel", 1000);
    ros::Publisher force2_pub = nh.advertise<geometry_msgs::Twist>("amr_2/cmd_vel", 1000);
    ros::Publisher force3_pub = nh.advertise<geometry_msgs::Twist>("amr_3/cmd_vel", 1000);
	
    pair<double, double> currPosition;
	ros::Rate loopRate(50);
  // the message to be published
     multi_amr_nectec::pos_msg msg;


	int team_size = 4 ;
    geometry_msgs::Point32 sum;
    float Kvl=0.25;
    geometry_msgs::Point32 dist_default;
    dist_default.x=4;
    dist_default.y=4;
    geometry_msgs::Point32 vl_pos;
    geometry_msgs::Point32 robot_pos [team_size];
    geometry_msgs::Point32 Dist_vl [team_size];
    geometry_msgs::Point32 Force_vl [team_size];
    
    Point my_array[team_size];
    Point point;
   
	while (ros::ok()) 
{   msg.point_robot.clear();
    geometry_msgs::Twist send_fvl [team_size];
        //Get each position of robot 
        for (int i = 0; i < team_size; i++) 
        {
			currPosition = getRobotPosition(i);
            robot_pos[i].x=currPosition.first;
            robot_pos[i].y=currPosition.second;
            sum.x+= robot_pos[i].x;
            sum.y+= robot_pos[i].y;
            //ROS_INFO("AMR id= %d : (%.3f, %.3f)", i, robot_pos[i].x, robot_pos[i].y);         
        // creating the vector
            point.x = robot_pos[i].x;
            point.y = robot_pos[i].y;
            my_array[i] = point;
         // ROS_INFO("Put value in array[%d] : (%.3f, %.3f)", i, point.x, point.y);         
   
        }
        std::vector<Point> my_vector (my_array, my_array + sizeof(my_array) / sizeof(Point));
    
		int k = 0;
        for (std::vector<Point>::iterator it = my_vector.begin(); it != my_vector.end(); ++it)
        {
        geometry_msgs::Point point;
        point.x = (*it).x;
        point.y = (*it).y;
        point.z = 0;
        msg.point_robot.push_back(point);
        k++;
        }
        
        
       
       // ROS_INFO("sum = [%.3f,%.3f]",sum.x,sum.y);
              vl_pos.x=sum.x/team_size;
              vl_pos.y=sum.y/team_size;
            ROS_INFO("Send pos VL [%.3f,%.3f]", vl_pos.x,vl_pos.y);
                //fake vl_pos
               
                vl_pos_pub.publish(vl_pos);
                 
             for (int j = 0; j < team_size; j++)
                {Dist_vl[j].x=vl_pos.x-robot_pos[j].x;
                 Dist_vl[j].y=vl_pos.y-robot_pos[j].y;
                int check_x=1;
                int check_y=1;
                if(robot_pos[j].x>=vl_pos.x)
                    {check_x=-1;}
               if(robot_pos[j].y>=vl_pos.y)
                    {check_y=-1;}
                //ROS_INFO("Dist default X=%.3f",dist_default.x);
                ROS_INFO("Dist_vl of robot %d[%.3f,%.3f]",j,Dist_vl[j].x,Dist_vl[j].y);
                Force_vl[j].x=Kvl*(Dist_vl[j].x-check_x*(dist_default.x));
                Force_vl[j].y=Kvl*(Dist_vl[j].y-check_y*(dist_default.y));
             
                //ROS_INFO("Virtual Force of robot %d[%.3f,%.3f]",j,Force_vl[j].x,Force_vl[j].y);
                 
                  send_fvl[j].linear.x =Force_vl[j].x;
                  send_fvl[j].linear.y =Force_vl[j].y;  
                 ROS_INFO("Cmd_vel of robot %d  [%.3f,%.3f]",j, send_fvl[j].linear.x,send_fvl[j].linear.y);  
                
                }
                force0_pub.publish(send_fvl[0]);
                force1_pub.publish(send_fvl[1]);
                force2_pub.publish(send_fvl[2]);
                force3_pub.publish(send_fvl[3]);
                sum.x=0; //set zero
                sum.y=0;
                robot_pos_pub.publish(msg);

        ROS_INFO("----------------------------------");
        //ros::spinOnce();
        loopRate.sleep();
	}
	return 0;
}

// function to get robot pos
pair<double, double> getRobotPosition(int robot_no)
{
    tf::TransformListener listener;
    tf::StampedTransform transform;
    pair<double, double> currPosition;

    try {
    	string robot_str = "/amr_";
    	robot_str += boost::lexical_cast<string>(robot_no);
    	string base_footprint_frame = tf::resolve(robot_str, "base_link");

        listener.waitForTransform("/map", base_footprint_frame, ros::Time(0), ros::Duration(10.0));
        listener.lookupTransform("/map", base_footprint_frame, ros::Time(0), transform);

        currPosition.first = transform.getOrigin().x();
        currPosition.second = transform.getOrigin().y();
    }
    catch (tf::TransformException &ex) {
        ROS_ERROR("%s",ex.what());
    }
    return currPosition;
}