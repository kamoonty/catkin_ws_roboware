#include "ros/ros.h"
#include "geometry_msgs/Point.h"
#include "beginner_tutorials/my_msg.h"
#include <vector>

struct Point {
    float x;
    float y;
};

int main(int argc, char **argv)
{
  // ROS objects
  ros::init(argc, argv, "my_publisher");
  ros::NodeHandle n;
  ros::Publisher pub = n.advertise<beginner_tutorials::my_msg>("my_topic", 1);
  ros::Rate loop_rate(0.5);

  // the message to be published
  beginner_tutorials::my_msg msg;
  msg.another_field = 0;

  // creating the vector
  Point my_array[11];
  Point point;
  for (int i=0; i < 11; i++) {
    point.x = i;
    point.y = i;
   // point.z=0;
    my_array[i] = point;
  }
  std::vector<Point> my_vector (my_array, my_array + sizeof(my_array) / sizeof(Point));

  // loop control
  int count = 0;
  while (ros::ok())
  {
    msg.points.clear();
    
    msg.another_field = count;
    int i = 0;
    for (std::vector<Point>::iterator it = my_vector.begin(); it != my_vector.end(); ++it) {
        geometry_msgs::Point point;
        point.x = (*it).x;
        point.y = (*it).y;
        point.z = 0;
        msg.points.push_back(point);
        i++;
        
    }

    //ROS_INFO("%d", msg.another_field);
  
    pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }


  return 0;
}