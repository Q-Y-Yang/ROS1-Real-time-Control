#include <controller_interface/controller.h>
#include <hardware_interface/joint_command_interface.h>
#include <pluginlib/class_list_macros.h>
#include <std_msgs/Float64.h>
#include <geometry_msgs/PoseStamped.h>
#include <std_msgs/Time.h>
#include <std_msgs/UInt64.h>
 
 
namespace my_controller_ns
{    
  class MyPositionController: public controller_interface::Controller<hardware_interface::EffortJointInterface>
 {
 /// Controller initialization in non-realtime
  bool init(hardware_interface::EffortJointInterface* hw,
                              ros::NodeHandle &n)
  {
    std::string my_joint;
    if (!n.getParam("joint", my_joint))
    {
      ROS_ERROR("could not find joint name");
      return false;
    }
 
    joint_ = hw->getHandle(my_joint);
    command_ = joint_.getPosition();
    
    if (!n.getParam("gain", gain_))
    {
      ROS_ERROR("could not find the gain parameter value");
      return false;
    }

    sub_command_ = n.subscribe<std_msgs::Float64>("command", 1, &MyPositionController::setCommandCB, this);

    //chatter_pub = n.advertise<geometry_msgs::PoseStamped>("chatter",1);
    chatter_pub = n.advertise<std_msgs::UInt64>("chatter",1);

    return true;
  }
  
   
  /// Controller startup in realtime
  void starting(const ros::Time& time)
  {
    init_pos_ = joint_.getPosition();
  }

  /// Controller update loop in realtime
  void update(const ros::Time& time, const ros::Duration& period)
  {
    double desired_pos = init_pos_ + 15 * sin(ros::Time::now().toSec());
    //double current_pos = joint_state_->position_;
    //joint_state_->commanded_effort_ = -10 * (current_pos - desired_pos);
    double error = desired_pos - joint_.getPosition();
    double commanded_effort = error*gain_;
    joint_.setCommand(commanded_effort);
    //msg.data = commanded_effort;

    msg.data = ros::WallTime::now().toNSec();
    chatter_pub.publish(msg);

  }
  
   void setCommandCB(const std_msgs::Float64ConstPtr& msg)
{
   command_ = msg->data;
}
  
  /// Controller stopping in realtime
  void stopping(const ros::Time& time)
  {}

private:
  hardware_interface::JointHandle joint_;
  double gain_;
  double command_;
  double init_pos_;
  ros::Subscriber sub_command_;
  ros::Publisher chatter_pub;
  //geometry_msgs::PoseStamped msg;
  std_msgs::UInt64 msg;

};

/// Register controller to pluginlib
PLUGINLIB_EXPORT_CLASS(
                         my_controller_ns::MyPositionController, 
                         controller_interface::ControllerBase)
  } // namespace


