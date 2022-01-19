#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include <thread>
#define MINUTE 60
#define ITERATIONS 10


void broadcast(ros::Publisher chatter_pub)
{

	while(chatter_pub.getNumSubscribers() < 1)
	{
		ros::WallDuration sleep_t(0.1);
		sleep_t.sleep();
	}

	ros::Rate loop_rate(1);

	int count = 0;

	while(ros::ok() && (count < MINUTE))
		{
			std_msgs::String msg;

			std::stringstream ss;
			ss << "Hello World" << count;
			msg.data = ss.str();

			std::cout << msg.data.c_str() << std::endl;
			chatter_pub.publish(msg);

			ros::spinOnce();
			loop_rate.sleep();

			++count;
		}

}

int main(int argc, char **argv)
{
	std::cout << "Initialising talker......" << std::endl;

	int steps = 0;

	ros::init(argc, argv, "talker");
	ros::NodeHandle n;
	ros::Publisher pub0, pub1, pub2, pub3, pub4, pub5, pub6, pub7, pub8, pub9;
	std::vector<ros::Publisher> pubs {pub0, pub1, pub2, pub3, pub4, pub5, pub6, pub7, pub8, pub9};
	std::vector<std::thread> workers;


	while(steps < ITERATIONS)
	{

		std::cout << "Talker: Starting " << steps+1 << "th iteration" << std::endl;

		for(int i = 0; i < (steps+1); i++)
		{
			pubs[i] = n.advertise<std_msgs::String>("chatter" + std::to_string(i), 1000);
		}

		for(int i = 0; i < (steps+1); i++)
		{
			workers.push_back(std::thread(broadcast, pubs[i]));
		}

		for(auto &t : workers) t.join();
		workers.clear();
		steps++;
	}

	std::cout << "Talker Node exiting execution" << std::endl;

	return 0;
}
