// ============================================================================
// Name        : dynamic_tf_with_odom.cpp
// Author      : Daniel Rudolph <drudolph@techfak.uni-bielefeld.de>
//               Timo Korthals <tkorthals@techfak.uni-bielefeld.de>
// Description : Recieve ros::nav_mags::Odometry and dynamic tf then with given frame_id
// ============================================================================

// ROS
#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <tf/transform_broadcaster.h>

using namespace std;

// Ros Listener Topic
string rosListenerTopic;
string parentFrame;
string childFrame;

// program name
const string programName = "odom_to_tf";

bool rostimenow;

void process(const nav_msgs::Odometry::ConstPtr& msg) {
  static tf::TransformBroadcaster br;
  tf::Transform transform;
  transform.setOrigin(tf::Vector3(msg->pose.pose.position.x, msg->pose.pose.position.y, msg->pose.pose.position.z) );
  transform.setRotation(tf::Quaternion(msg->pose.pose.orientation.x, msg->pose.pose.orientation.y, msg->pose.pose.orientation.z, msg->pose.pose.orientation.w));

  br.sendTransform(tf::StampedTransform(transform, rostimenow?ros::Time::now():msg->header.stamp , parentFrame, childFrame));
}

int main(int argc, char * argv[]) {
  ROS_INFO("Start: %s", programName.c_str());

  // Init ROS
  ros::init(argc, argv, programName);
  ros::NodeHandle node("~");

  node.param<string>("ros_listener_odom_topic", rosListenerTopic, "/topic");
  node.param<string>("parent_frame", parentFrame, "/parent");
  node.param<string>("child_frame", childFrame, "/child");
  node.param<bool>("rostimenow", rostimenow, false);

  ROS_INFO("ros_listener_topic: %s", rosListenerTopic.c_str());
  ROS_INFO("parent_frame: %s", parentFrame.c_str());
  ROS_INFO("child_frame: %s", childFrame.c_str());
  ROS_INFO("rostimenow: %s", rostimenow?"True":"False");

  ros::Subscriber sub = node.subscribe(rosListenerTopic, 1, process);

  ros::spin();

  return 0;
}
