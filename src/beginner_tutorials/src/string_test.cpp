#include "ros/ros.h"
#include "std_msgs/String.h"
int main(int argc, char **argv)
{ ros::init(argc, argv, "string_test");
  ros::NodeHandle n;
  ros::Rate loop_rate(2);
    while (ros::ok())
  { int team_size =4;
    for (int i=0;i<team_size; i++)
    { std::string robot_str;
      std::string cmd_str ;
    int robot_no=i;
    robot_str= "amr_";
    //robot_str += boost::lexical_cast<std::string>(robot_no);
    ROS_INFO("%s",robot_str);
    }
       loop_rate.sleep();
  }
return 0;
}