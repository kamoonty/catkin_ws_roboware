/*
   Created on: Apr 18, 2019
 *      Author: Kanin Soloist
 */
#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <boost/lexical_cast.hpp>
#include <std_msgs/Float32.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Twist.h>
#include <stdlib.h>
#include "geometry_msgs/Point.h"
#include "multi_amr_nectec/pos_msg.h"
#include <vector> 
// global variable here
using namespace std;

int team_size; //use for get param
pair<double, double> getRobotPosition(int robot_no);
struct Point { float x;   float y;};

int main(int argc, char** argv) {
    ros::init(argc, argv, "Robot_position");
    ros::NodeHandle nh;   
    // send array
    ros::Publisher robot_pos_pub = nh.advertise<multi_amr_nectec::pos_msg>("robot_pos",1000);
    pair<double, double> currPosition;
	ros::Rate loopRate(100);
    multi_amr_nectec::pos_msg msg;  // the message to be published  
    nh.getParam("position_robot/team_size", team_size);
    geometry_msgs::Point robot_pos [team_size];
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
       robot_pos_pub.publish(msg);  //array of robot pos 
       
        //ROS_INFO("--------Published robot pos----");
        ros::spinOnce();
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