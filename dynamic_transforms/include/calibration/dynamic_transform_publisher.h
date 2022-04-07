#include <dynamic_reconfigure/DoubleParameter.h>
#include <dynamic_reconfigure/Reconfigure.h>
#include <dynamic_reconfigure/Config.h>
#include <tf/tf.h>

namespace dynamic_transform_publisher {
  void reconfigureTf(tf::Transform trans, std::string nodeName) {
    dynamic_reconfigure::ReconfigureRequest srv_req;
    dynamic_reconfigure::ReconfigureResponse srv_resp;
    dynamic_reconfigure::DoubleParameter double_param;
    dynamic_reconfigure::Config conf;

    double roll, pitch, yaw;
    tf::Matrix3x3(trans.getRotation()).getRPY(roll, pitch, yaw);

    double_param.name = "x";
    double_param.value = trans.getOrigin().getX();
    conf.doubles.push_back(double_param);

    double_param.name = "y";
    double_param.value = trans.getOrigin().getY();
    conf.doubles.push_back(double_param);

    double_param.name = "z";
    double_param.value = trans.getOrigin().getZ();
    conf.doubles.push_back(double_param);

    double_param.name = "roll";
    double_param.value = roll;
    conf.doubles.push_back(double_param);

    double_param.name = "pitch";
    double_param.value = pitch;
    conf.doubles.push_back(double_param);

    double_param.name = "yaw";
    double_param.value = yaw;
    conf.doubles.push_back(double_param);

    srv_req.config = conf;
    const std::string serviceName = nodeName + std::string("/set_parameters");
    const int timeout_ms = 1000;
    if (ros::service::waitForService(serviceName, timeout_ms)) {
        ROS_DEBUG_STREAM("Call " << serviceName << " with request:\n" << srv_req);
        ros::service::call(serviceName, srv_req, srv_resp);
    } else {
        ROS_DEBUG_STREAM("Service " << serviceName << " got timeout after " << timeout_ms << " ms");
    }
  }

  std::string getEulerString(const tf::Pose &pose) {

    double roll, pitch, yaw;
    tf::Matrix3x3(pose.getRotation()).getRPY(roll, pitch, yaw);

    std::stringstream ss;
    ss << "(X Y Z roll pitch yaw): " <<
                    pose.getOrigin().getX() << " " <<
                    pose.getOrigin().getY() << " " <<
                    pose.getOrigin().getZ() << " " <<
                    roll  << " " <<
                    pitch << " " <<
                    yaw;
    return ss.str();
  }

  std::string getQuatString(const tf::Pose &pose) {
    std::stringstream ss;
    ss << "(X Y Z x y z w): " <<
                    pose.getOrigin().getX() << " " <<
                    pose.getOrigin().getY() << " " <<
                    pose.getOrigin().getZ() << " " <<
                    pose.getRotation().x() << " " <<
                    pose.getRotation().y() << " " <<
                    pose.getRotation().z() << " " <<
                    pose.getRotation().w();
    return ss.str();
  }
}
