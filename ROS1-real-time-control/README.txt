Realtime control by ros_control and gazebo

my_controller pkg is a customized controller managed by controller_manager and inherited from controller_interface.

To run this control system:
you should have ros_control and gazebo_ros installed in your ros.

Create a catkin workspace:
$ mkdir -p ~/catkin_ws/src
$ cd ~/catkin_ws/
$ catkin_make
$ source devel/setup.bash

Download this directory to  /catkin_ws/src

Steps to run:
Open a terminal and enter the workspace   cd ~/catkin_ws/
1. catkin_make -DCATKIN_WHITELIST_PACKAGES="my_controller"            compile the my_controller package
2. source devel/setup.bash
3. rosrun rrbot_gazebo rrbot_world.launch          Then the model in gazebo (without GUI) and controller are running.
4. open another terminal
enter: rostopic echo -p /rrbot/joint1_position_controller/chatter > data.txt
wait for data capture
Ctrl C to stop
Then you will get a data.txt file, in which stores the update time that we need.
The first column is simulation time, and the second column is wall-time.


The parameters of controller can be adjusted in my_controller/config/my_controller.yaml