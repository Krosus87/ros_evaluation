# ros_evaluation

# Setup

This package has thus far only been tested in one environment:

- Ubuntu 16.04 Server ARMHF for Raspberry Pi 3B from https://web.archive.org/web/20190925133116/http://ubuntu-pi-flavour-maker.org/download/
- ROS Kinetic

Note: This Ubuntu image is from a webarchive at the time of writing and does not work for Raspberry 3B+ and newer versions. In this case you will have to set up your OS on your own. Furthermore, ROS Kinetic is only supported for Ubuntu 16.04 and ways to circumvent this is not advised.

# Build

First, source your environment variables if not already done:

```bash
$ source /opt/ros/kinetic/setup.bash
```

Second, one needs to create a workspace before downloading and building this package:

```bash
$ mkdir -p ~/catkin_ws/src
$ cd ..
$ catkin_make
$ source ~/catkin_ws/devel/setup.bash
```

Third, now download and build ros_evaluation:

```bash
$ cd /src
$git clone https://github.com/Krosus87/ros_evaluation.git
$ cd ..
$ catkin_make
```

Well done mate, you have now successfully build this package. Let's get it running.

# Run

This project has been build to run on two Raspberries Pi's to communicate with each other. By default, a roscore will only recognise nodes on "localhost" (Your Computer), thus, for communication with other nodes in the network one needs to declare further environment variables.


If not already done, run this:
```bash
$ source /opt/ros/kinetic/setup.bash
$ source ~/catkin_ws/devel/setup.bash
```


First, choose where "roscore" runs:

```bash
$ export ROS_MASTER_URI=http://192.168.0.159:11311
$ export ROS_IP=192.168.0.159
$ roscore
```

Second, active first node:

```bash
$ export ROS_MASTER_URI=http://192.168.0.159:11311
$ export ROS_IP=192.168.0.159
$ rosrun ros_evaluation listener
```

Third, activate second node:

```bash
$ export ROS_MASTER_URI=http://192.168.0.159:11311
$ export ROS_IP=192.168.0.159
$ rosrun ros_evaluation talker
```

Note: The three steps in this "Run" section are performed in three separate terminals, the ROS_MASTER_URI=http://xxx.xxx.xxx.xxx:11311 value depends on the machine's IP address where roscore is running and the ROS_IP=xxx.xxx.xxx.xxx value is again your individual machine's IP address


Cheers








