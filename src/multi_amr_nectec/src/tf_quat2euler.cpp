
#include <tf/tf.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Pose2D.h>

ros::Publisher pub_pose_;

void odometryCallback_(const nav_msgs::Odometry::ConstPtr msg) {
geometry_msgs::Pose2D pose2d; //Pos2d consists of x y and theta (yaw) 
pose2d.x = msg->pose.pose.position.x;
pose2d.y = msg->pose.pose.position.y;
tf::Quaternion q(
msg->pose.pose.orientation.x,
msg->pose.pose.orientation.y,
msg->pose.pose.orientation.z,
msg->pose.pose.orientation.w);
tf::Matrix3x3 m(q);
double roll, pitch, yaw;
m.getRPY(roll, pitch, yaw);
pose2d.theta = yaw;
pub_pose_.publish(pose2d);
//ROS_INFO("Yaw= %f",yaw); 

}

int main(int argc, char **argv)
{
ros::init(argc, argv, "tf_quat2euler");

ros::NodeHandle nh_;

ros::Subscriber sub_odom_ = nh_.subscribe("odom", 1000, odometryCallback_);
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