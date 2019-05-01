#include "ros/ros.h"
#include "std_msgs/String.h"
#include <std_msgs/Float32.h>



int main(int argc, char **argv)
{ // Create a ROS node handle
ros::init(argc, argv, "pass_list_test");
ros::NodeHandle nh;
ros::Rate loop_rate(1);
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
while (ros::ok())
  {
for(unsigned i=0; i < my_double_list.size(); i++) {
  ROS_INFO("list[%d]= %f",i,my_double_list[i]);
  //sum += my_double_list[i];
  //ROS_INFO("Sum = %f",sum);
}




 ros::spinOnce();
 loop_rate.sleep();

  }

   

  return 0;
}