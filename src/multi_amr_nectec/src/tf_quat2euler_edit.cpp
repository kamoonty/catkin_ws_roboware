
#include <tf/tf.h>
//#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Pose2D.h>
#include <geometry_msgs/PoseStamped.h>
std::string robot_name; //use for get param from launch file
ros::Publisher pub_pose_;

void odometryCallback_(const geometry_msgs::PoseStamped::ConstPtr msg) {
geometry_msgs::Pose2D pose2d; //Pos2d consists of x y and theta (yaw) 
pose2d.x = msg->pose.position.x;
pose2d.y = msg->pose.position.y;
tf::Quaternion q(
msg->pose.orientation.x,
msg->pose.orientation.y,
msg->pose.orientation.z,
msg->pose.orientation.w);
tf::Matrix3x3 m(q);
double roll, pitch, yaw;
m.getRPY(roll, pitch, yaw);
pose2d.theta = yaw;
pub_pose_.publish(pose2d);

ROS_INFO("Yaw= %f",yaw); 
}

int main(int argc, char **argv)
{
ros::init(argc, argv, "tf_quat2euler_edit");

ros::NodeHandle nh_;
nh_.getParam("tf_quat2euler_edit/robot_name", robot_name);
  ROS_INFO(" robot name= %s",robot_name); 
std::string follower_robot ("/vrpn_client_node/mocap_");
 follower_robot =follower_robot+"robot_name"+"/pose";
  ROS_INFO("Follower robot= %s",follower_robot);  
// still have a problem when pass string to cpp code
ros::Subscriber sub_odom_ = nh_.subscribe(follower_robot, 1000, odometryCallback_);
pub_pose_ = nh_.advertise<geometry_msgs::Pose2D>("pose2d", 1000);
//ros::Publisher pos_pub = nh.advertise<geometry_msgs::Pose2D>("pos", 1000);


ros::Rate loop_rate(100);
while (ros::ok())
  { 
    
    ros::spinOnce();

    loop_rate.sleep();
    
  }

//ros::spin();

return 0;
}