# ROS1-Real-time-Control <br>
Realtime control by ros_control and gazebo <br>
ROS1 control stack to real-time control a simulated pendulum in Gazebo <br>


my_controller pkg is a customized controller managed by controller_manager and inherited from controller_interface. <br>

## Dependencies:
- ros_control <br>
- gazebo_ros  <br>

Create a catkin workspace: <br>
$ `mkdir -p ~/catkin_ws/src`<br>
$ `cd ~/catkin_ws/`<br>
$ `catkin_make`<br>
$ `source devel/setup.bash`<br>



## Steps to run:
Download this directory to  /catkin_ws/src<br>
Open a terminal and enter the workspace   cd ~/catkin_ws/<br>
1. compile the my_controller package: `catkin_make -DCATKIN_WHITELIST_PACKAGES="my_controller"` <br>            
2. `source devel/setup.bash`<br>
3. `rosrun rrbot_gazebo rrbot_world.launch  `        Then the model in gazebo (without GUI) and controller are running.<br>
4. open another terminal<br>
enter: `rostopic echo -p /rrbot/joint1_position_controller/chatter > data.txt`<br>
wait for data capture<br>
Ctrl C to stop<br>
Then you will get a data.txt file, in which stores the update time that we need.<br>
The first column is simulation time, and the second column is wall-time.<br>


The parameters of controller can be adjusted in my_controller/config/my_controller.yaml<br>
