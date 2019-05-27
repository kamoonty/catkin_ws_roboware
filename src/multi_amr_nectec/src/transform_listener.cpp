#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <geometry_msgs/Twist.h>


int main(int argc, char** argv){
  ros::init(argc, argv, "transform_listener");

  ros::NodeHandle node;

  //ros::service::waitForService("spawn");
  //ros::ServiceClient add_turtle =
   // node.serviceClient<turtlesim::Spawn>("spawn");
  //turtlesim::Spawn srv;
  //add_turtle.call(srv);

  //ros::Publisher pub_data =node.advertise<geometry_msgs::Twist>("turtle2/cmd_vel", 10);

  tf::TransformListener listener;

  ros::Rate rate(2);
  while (node.ok()){
    tf::StampedTransform transform;
  try{std::string robot_frame ("/amr_");
 robot_frame =robot_frame+ boost::lexical_cast<std::string>(2);
 robot_frame =robot_frame+"/base_link";
 //ROS_INFO("Robotframe =%s",robot_frame);
    listener.waitForTransform(robot_frame,"/map", ros::Time(0), ros::Duration(10.0) );
    listener.lookupTransform(robot_frame, "/map",ros::Time(0), transform);
    }
    catch (tf::TransformException &ex) {
      ROS_ERROR("%s",ex.what());
      ros::Duration(1.0).sleep();
      continue;
    }
   
 double x = transform.getOrigin().getX();
double y = transform.getOrigin().getY();
double th = tf::getYaw(transform.getRotation());
ROS_INFO("tf listener  x,y=[%f,%f] Yaw=%f",x,y,th); 

    //geometry_msgs::Twist vel_msg;
    //pub_data.publish(vel_msg);

    rate.sleep();
  }
  return 0;
};

