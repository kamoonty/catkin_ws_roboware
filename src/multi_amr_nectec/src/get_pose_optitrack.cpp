
#include <tf/tf.h>

#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Pose2D.h>

ros::Publisher pub_pose_;

void PoseStampedCB(const geometry_msgs::PoseStamped::ConstPtr msg) {
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
//ROS_INFO("Yaw= %f",yaw); 

}

int main(int argc, char **argv)
{
ros::init(argc, argv, "get_pose_optitrack");

ros::NodeHandle nh;

ros::Subscriber sub_odom_ = nh.subscribe("/vrpn_client_node/mocap_amr_0/pose", 1000, PoseStampedCB);
pub_pose_ = nh.advertise<geometry_msgs::Pose2D>("amr_0_pose", 1000);
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