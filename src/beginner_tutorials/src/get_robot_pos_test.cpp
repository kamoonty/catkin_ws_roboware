/*
 * print_location.cpp
 *
 *  Created on: Mar 31, 2014
 *      Author: roiyeho
 */

#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <boost/lexical_cast.hpp>

using namespace std;
string tf_prefix;

pair<double, double> getRobotPosition(int robot_no);

int main(int argc, char** argv) {
	ros::init(argc, argv, "print_position");
	ros::NodeHandle nh;
    ros::Publisher force0_pub = nh.advertise<geometry_msgs::Twist>("amr_0/cmd_vel", 1000);
    ros::Publisher force1_pub = nh.advertise<geometry_msgs::Twist>("amr_1/cmd_vel", 1000);
 
	// Get tf_prefix from the parameter server
	//nh.getParam("tf_prefix", tf_prefix);

	pair<double, double> currPosition;
	ros::Rate loopRate(20);

	int team_size = 2;
    geometry_msgs::Twist send_Fij [team_size];

	while (ros::ok()) {
		for (int i = 0; i < team_size; i++) {
			currPosition = getRobotPosition(i);
            send_Fij[i].linear.x=currPosition.first;
            send_Fij[i].linear.y=currPosition.second;
			ROS_INFO("Position of robot %d = [%f,%f]", i, currPosition.first, currPosition.second);
		}
		ROS_INFO("----------------------------------");
      force0_pub.publish(send_Fij[0]);
      force1_pub.publish(send_Fij[1]);
      
      ros::spinOnce();
	  loopRate.sleep();
	}

	//return 0;
}

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

/*pair<double, double> getRobotPosition()
{
    tf::TransformListener listener;
    tf::StampedTransform transform;
    pair<double, double> currPosition;

    try {
    	string base_footprint_frame = tf::resolve(tf_prefix, "base_footprint");

        listener.waitForTransform("/map", base_footprint_frame, ros::Time(0), ros::Duration(10.0));
        listener.lookupTransform("/map", base_footprint_frame, ros::Time(0), transform);

        currPosition.first = transform.getOrigin().x();
        currPosition.second = transform.getOrigin().y();
    }
    catch (tf::TransformException &ex) {
        ROS_ERROR("%s",ex.what());
    }
    return currPosition;
}*/


