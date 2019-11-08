
#include <tf/tf.h>
//#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Pose2D.h>
#include <geometry_msgs/PoseStamped.h>

ros::Publisher pub_pose_amr_0;
ros::Publisher pub_pose_amr_1;
void amr_0_CB(const geometry_msgs::PoseStamped::ConstPtr msg) {
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
pub_pose_amr_0.publish(pose2d);
//ROS_INFO("Yaw= %f",yaw); 
}

void amr_1_CB(const geometry_msgs::PoseStamped::ConstPtr msg) {
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
pub_pose_amr_1.publish(pose2d);
//ROS_INFO("Yaw= %f",yaw); 
}
int main(int argc, char **argv)
{
ros::init(argc, argv, "pose2d_real_robot");

ros::NodeHandle nh_;


ros::Subscriber sub_pose1 = nh_.subscribe("/vrpn_client_node/mocap_amr_0/pose", 1000, amr_0_CB);
ros::Subscriber sub_pose2 = nh_.subscribe("/vrpn_client_node/mocap_amr_1/pose", 1000, amr_1_CB);

pub_pose_amr_0 = nh_.advertise<geometry_msgs::Pose2D>("amr_0/pose2d", 1000);
pub_pose_amr_1 = nh_.advertise<geometry_msgs::Pose2D>("amr_1/pose2d", 1000);
//ros::Publisher pos_pub = nh.advertise<geometry_msgs::Pose2D>("pos", 1000);


ros::Rate loop_rate(100);
while (ros::ok())
  { 
    
    ros::spinOnce();

    loop_rate.sleep();
    
  }


}