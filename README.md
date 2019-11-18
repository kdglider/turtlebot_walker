# TurtleBot Random Walker
This project is a simple TurtleBot simulator in Gazebo that acts like a Roomba vacuum cleaner. It moves forward until its 2D LIDAR detects an object with the safe distance, at which point the robot will turn for a constrained random time before moving forward again.


## Dependencies
The system must run Ubuntu 16.04 that has C++11.

The ROS Kinetic full desktop version can be installed using these instructions: http://wiki.ros.org/kinetic/Installation/Ubuntu

The TurtleBot software can be install using these instructions: http://wiki.ros.org/turtlebot/Tutorials/indigo/Turtlebot%20Installation

Change all indigo text to kinetic and omit "ros-indigo-rocon-remocon" and "ros-indigo-rocon-qt-library" since these have equivalent in ROS Kinetic.


## Build Instructions
Create a new directory on the local system to designate as the Catkin workspace and create another directory called "src" within it (eg. catkin_ws/src). Clone the project into the src directory:
```
git clone https://github.com/kdglider/turtlebot_walker.git
```
From the catkin_ws directory, build the code and run the setup script:
```
catkin_make
source devel/setup.bash
```


## Run Demonstration
Run the demonstration launch file after building the code:
```
roslaunch beginner_tutorials talkerListener.launch record:=X
```
where X is set to 'true' or 'false' to indicate whether rosbag recording should take place. This will load Gazebo and the TurtleBot will begin moving automatically.

If recording is set to true, all topics except for /camera/* will be recorded for 15s and the output file will be saved to the results directory. These settings can be changed in the launch file. 

The bag file can be inspected using 'rosbag info'. The bag file can be played back using 'rosbag play' and the walker can now be run independently without Gazebo. To run a sample bag file, download from: https://drive.google.com/open?id=1gsMGmc-O9Cs-62TGM6QUza6kbIy-W9oV.


