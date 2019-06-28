#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
#include "std_msgs/Float32.h"
#include <geometry_msgs/Point32.h>
#include <geometry_msgs/Point.h>

geometry_msgs::Twist get_cmd_vel;
float default_x;
float default_y;
float default_theta;
/*
geometry_msgs::Point get_vl;
void VL_Callback(const geometry_msgs::Point & vl_pos)
{  get_vl=vl_pos;
  //ROS_INFO("Fake odom VL= [%.3f] VL_y=[%.3f]",get_vl.x,get_vl.y);
}*/

void cmd_vel_Callback(const geometry_msgs::Twist & cmd_vel)
{  get_cmd_vel=cmd_vel; 
  //ROS_INFO("linear x=%.3f,y= %.3f",get_cmd_vel.linear.x,get_cmd_vel.linear.y);
  //ROS_INFO("angularx=%.3f,y= %.3f,z=%.3f",get_cmd_vel.angular.x,get_cmd_vel.angular.y,get_cmd_vel.angular.z);
}
int main(int argc, char** argv){
  ros::init(argc, argv, "fake_odometry_publisher");
  ros::NodeHandle nh;
  ros::Publisher odom_pub = nh.advertise<nav_msgs::Odometry>("odom", 1000);
  //ros::Subscriber vl_sub = n.subscribe("vl_pos", 1000, VL_Callback);
  ros::Subscriber cmd_vel_sub = nh.subscribe("cmd_vel", 1000, cmd_vel_Callback);
  tf::TransformBroadcaster odom_broadcaster;
  nh.getParam("fake_odom_vl/default_x",default_x);
  nh.getParam("fake_odom_vl/default_y",default_y);
  nh.getParam("fake_odom_vl/default_theta",default_theta);
  ros::Time current_time, last_time;
  current_time = ros::Time::now();
  last_time = ros::Time::now();
  double x = default_x;
  double y = default_y;
  double th = default_theta;
  ros::Rate loopRate(100);
  while(nh.ok()){
    ros::spinOnce();               // check for incoming messages
    current_time = ros::Time::now();   
    double vx = get_cmd_vel.linear.x;
    double vy = get_cmd_vel.linear.y;
    double vth = get_cmd_vel.angular.z;
    //ROS_INFO("X Y = [%.3f,%.3f]",x,y);
    //ROS_INFO("vx =%.3f, vy=%.3f, vth =%.3f",vx,vy,vth);
    //compute odometry in a typical way given the velocities of the robot
    double dt = (current_time - last_time).toSec();
    double delta_x = (vx * cos(th) - vy * sin(th)) * dt;
    double delta_y = (vx * sin(th) + vy * cos(th)) * dt;
    double delta_th = vth * dt;
    //ROS_INFO("delta x= %.3f, delta y =%.3f ,delta_th =%.3f",delta_x,delta_y,delta_y);
    x += delta_x;
    y += delta_y;
    th += delta_th;
    //since all odometry is 6DOF we'll need a quaternion created from yaw
    geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(th);

    //first, we'll publish the transform over tf
    geometry_msgs::TransformStamped odom_trans;
    odom_trans.header.stamp = current_time;
    odom_trans.header.frame_id = "odom";
    odom_trans.child_frame_id = "base_link";

    odom_trans.transform.translation.x = x;
    odom_trans.transform.translation.y = y;
    odom_trans.transform.translation.z = 0.0;
    odom_trans.transform.rotation = odom_quat;

    //send the transform
    odom_broadcaster.sendTransform(odom_trans);

    //next, we'll publish the odometry message over ROS
    nav_msgs::Odometry odom;
    odom.header.stamp = current_time;
    odom.header.frame_id = "odom";

    //set the position
    odom.pose.pose.position.x = x;
    odom.pose.pose.position.y = y;
    odom.pose.pose.position.z = 0.0;
    odom.pose.pose.orientation = odom_quat;

    //set the velocity
    odom.child_frame_id = "base_link";
    odom.twist.twist.linear.x = vx;
    odom.twist.twist.linear.y = vy;
    odom.twist.twist.angular.z = vth;
    //publish the message
    odom_pub.publish(odom);

    last_time = current_time;
    loopRate.sleep();
  }
}