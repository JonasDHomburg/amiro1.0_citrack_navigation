#include <ros/ros.h>
#include <tf/tf.h>
#include <boost/algorithm/string.hpp>
#include <tf/transform_broadcaster.h>
#include <dynamic_reconfigure/server.h>
#include <calibration/TransformConfig.h>
#include <calibration/dynamic_transform_publisher.h>

static tf::Transform transform;

void callback(calib::TransformConfig &config, uint32_t level) {
  ROS_DEBUG("Reconfigure Request:\nx:\t%f\ny:\t%f\nz:\t%f\nroll:\t%f\npitch:\t%f\nyaw:\t%f",
            config.x, config.y, config.z,
            config.roll, config.pitch, config.yaw);
  transform = tf::Pose(
            tf::createQuaternionFromRPY(config.roll, config.pitch, config.yaw),
            tf::Vector3(config.x, config.y, config.z));
}

int main(int argc, char** argv) {

  ros::init(argc, argv, "dynamic_transform_publisher");
  ros::NodeHandle n("~");

  std::string tfStr, targetFrameId, sourceFrameId, reconfTopic;
  double rate;
  const int tfEulerComponents = 6, tfQuatComponents = 7;
  std::vector<std::string> tfVecStr;
  std::vector<double> tfVecDbl;
  tf::StampedTransform transformToBr;
  tf::TransformBroadcaster br;
  dynamic_reconfigure::Server<calib::TransformConfig> server;
  dynamic_reconfigure::Server<calib::TransformConfig>::CallbackType f;

  n.param<std::string>("tf", tfStr, ""); // (m,m,m,rad,rad,rad) or (m,m,m,1,1,1,1) in the form "2 1.1 4 3.2 1 4"
  n.param<std::string>("source_frame", sourceFrameId, "");
  n.param<std::string>("target_frame", targetFrameId, "");
  n.param<double>("rate", rate, 1); // (Hz) Publish rate

  // Setup dynamic reconfiguration
  f = boost::bind(&callback, _1, _2);
  server.setCallback(f);

  boost::split(tfVecStr, tfStr, boost::is_any_of(" "));

  // Sanity checks and configuration
  if (sourceFrameId.empty() || targetFrameId.empty()) {
      ROS_ERROR("source_frame or target_frame cannot be empty");
      return 1;
  } else if (!sourceFrameId.compare(targetFrameId)) {
      ROS_ERROR("source_frame and target_frame cannot be the same");
      return 1;
  } else if (tfVecStr.size() == tfEulerComponents || tfVecStr.size() == tfQuatComponents) {
    if (tfVecStr.size() == tfEulerComponents) {
        ROS_INFO("Use tf with (x,y,z,r,p,y): %s", tfStr.c_str());
        tfVecDbl.resize(tfEulerComponents);
        for (int idx = 0; idx < tfEulerComponents; ++idx) {
            tfVecDbl.at(idx) = std::stod(tfVecStr.at(idx));
        }
        transform = tf::Pose(
            tf::createQuaternionFromRPY(tfVecDbl.at(3), tfVecDbl.at(4), tfVecDbl.at(5)),
            tf::Vector3(tfVecDbl.at(0), tfVecDbl.at(1), tfVecDbl.at(2)));
    } else if (tfVecStr.size() == tfQuatComponents) {
        ROS_INFO("Use tf with (x,y,z,qx,qy,qz,qw): %s", tfStr.c_str());
        tfVecDbl.resize(tfQuatComponents);
        for (int idx = 0; idx < tfQuatComponents; ++idx) {
            tfVecDbl.at(idx) = std::stod(tfVecStr.at(idx));
        }
        transform = tf::Pose(
//            tf::createQuaternionFromRPY(tfVecDbl.at(3), tfVecDbl.at(4), tfVecDbl.at(5)),
            tf::Quaternion(tfVecDbl.at(3), tfVecDbl.at(4), tfVecDbl.at(5), tfVecDbl.at(6)),
            tf::Vector3(tfVecDbl.at(0), tfVecDbl.at(1), tfVecDbl.at(2)));
    }
    // Tell the reconfiguration server about the given setup, but keep the local values by spinning once
    tf::Transform transformTmp = transform;
    ros::AsyncSpinner spinner(1);
    spinner.start();
    dynamic_transform_publisher::reconfigureTf(transform, n.getNamespace());
    spinner.stop();
    transform = transformTmp;
  } else if (tfStr.empty()) {
      ROS_INFO("Using standard parameters defined by dynamic reconfiguration");
  } else {
      ROS_ERROR("tf components error '%d' given and '%d' or '%d' needed for quaternions or euler. Maybe there are trailing spaces?",
                int(tfVecStr.size()), tfQuatComponents, tfEulerComponents);
      return 1;
  }

  // The tf broadcaster
  ros::Rate sleeper(rate);
  while (n.ok()) {
    ros::spinOnce(); // Get new configuration
    transformToBr = tf::StampedTransform(transform, ros::Time::now(), sourceFrameId, targetFrameId);
    br.sendTransform(transformToBr);
    sleeper.sleep();
  }
  return 0;
}
