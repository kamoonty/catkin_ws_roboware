#include <stdio.h>
#include <stdlib.h>

#include "ros/ros.h"
int main(int argc, char **argv)
{
	ros::init(argc, argv, "diff_funcr");

	ros::NodeHandle n;
	ros::Time prev_time_;
    ros::Duration delta_t_;
    float x1=0;
    float x2;
    float diff,delta_T=0.5;
    float first_data ;
    float second_data ;
	while (ros::ok())
	{  
       /*diff=x2-x1;
       ROS_INFO("[x1,x2]=[%f,%f] diff %f",x1,x2,diff);
       x1=x2;
       x2=x2+1;
       */
       first_data=x1;
       ROS_INFO("first_data= %f",first_data);
       if(second_data!=0)
       {  ROS_INFO("second_data= %f",second_data);
        diff= (first_data-second_data)/delta_T;
       second_data=first_data;
       ROS_INFO("diff= %f",diff);
       }
       else
       {second_data=first_data;
       ROS_INFO("First loop");
       }
       x1=x1+1;


		//Do this.
		ros::spinOnce();
		//Added a delay so not to spam
		sleep(1);
	}

}