#include "ros/ros.h"
#include "std_msgs/String.h"
#include "thread"
#define ITERATIONS 10


void chatterCallback(const std_msgs::String::ConstPtr& msg)
{

	size_t length = strlen(msg->data.c_str());
	std::string counter = std::string(msg->data.c_str(), length - 2, length);

	std::cout << "I heard:" << msg->data.c_str() << std::endl;

	if(counter == "59") ros::shutdown();
}

int main(int argc, char **argv)
{
	std::cout << "Initialising listener....." << std::endl;
	ros::init(argc, argv, "listener");
	ros::MultiThreadedSpinner spinner(0);
	ros::Subscriber sub0, sub1, sub2, sub3, sub4, sub5, sub6, sub7, sub8, sub9;
	std::vector<ros::Subscriber> subs{sub0, sub1, sub2, sub3, sub4, sub5, sub6, sub7, sub8, sub9};
	int steps = 0;

	while(steps < ITERATIONS)
	{
		ros::NodeHandle n;
		std::cout << "Listener: Starting " << steps+1 << "th iteration" << std::endl;

		for(int i = 0; i < (steps+1); i++)
		{
			subs[i] = n.subscribe("chatter" + std::to_string(i), 1000, chatterCallback);
		}
		steps++;
		spinner.spin();
		for(int i = 0; i < steps; i++) subs[i].shutdown();
	}

	std::cout << "Listener node exiting execution" << std::endl;

	return 0;
}


