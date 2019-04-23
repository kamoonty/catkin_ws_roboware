#include "ros/ros.h"
#include "std_msgs/String.h"
#include <std_msgs/Float32.h>



int main(int argc, char **argv)
{ // Create a ROS node handle
ros::NodeHandle nh;

// Construct a map of strings
std::map<std::string,std::string> map_s, map_s2;
map_s["a"] = "foo";
map_s["b"] = "bar";
map_s["c"] = "baz";

// Set and get a map of strings
nh.setParam("my_string_map", map_s);
nh.getParam("my_string_map", map_s2);

// Sum a list of doubles from the parameter server
std::vector<double> my_double_list;
double sum = 0;
nh.getParam("my_double_list", my_double_list);
for(unsigned i=0; i < my_double_list.size(); i++) {
  sum += my_double_list[i];
  ROS_INFO("Sum = %f",sum);
}

  ros::spin();

  return 0;
}