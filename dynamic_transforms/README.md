# calibration

## one_shot_calib_node

tbd

## dynamic_transform_publisher

tbd


## calibrator.py

Load `calibration.yaml` (sensor pose, path rosbag tracking data) via rosparam.
It performs a calibration of given sensors by graph optimization provided from g2o.
Via dynamic reconfiguration it calibrates the cameras from launch file `calibration_demo` (run it after launching).

### Preliminaries for Installation

Testet with ROS kinetik and Ubuntu 16.04

* Build and install g2o: https://github.com/RainerKuemmerle/g2o#compilation
* Build and install g2opy: https://github.com/uoip/g2opy#installation
 * Substitute `cmake ..` with `cmake -DPYBIND11_PYTHON_VERSION=2.7 ..`
 * Substitute `python setup.py install` with `sudo cp lib/g2o.so /usr/lib/python2.7/dist-packages/g2o.so`

### Demo

* Start playing the bags and visualization: `roslaunch calibration calibration_demo.launch`
* Run calibration: `rosrun calibration calibrator.py`
* Store the calibrated data `roslaunch calibration calibration_dump.launch`
* Optional: Load the calibrated data `roslaunch calibration calibration_load.launch`

### CITrack calibration

* Start cameras: `roslaunch demo start_cameras.launch`
* Start tracking wrt. marker setup: `roslaunch demo start_aruco3_calibration.launch`
* Record tracks in bags (stores bags to `/tmp/cam[1,2,3,4].bag`): `roslaunch demo calibration_record.launch`
* Stop tracking
* Start playing the bags and visualization: `roslaunch calibration calibration_citrack.launch`
* Run calibration: `rosrun calibration calibrator.py`
* Store the calibrated data `roslaunch calibration calibration_dump.launch`
* Optional: Load the calibrated data `roslaunch calibration calibration_load.launch`

## inverse_transform.py

Calculates the inverse transformation and prints it to std::out so that it can be used by tf static_transform_publisher

### Examples

```
$ ./inverse_transform.py -x 100. -y 2 -z 0 -R 0 -P 0 -Y 0
-100.0000 -2.0000 0.0000 0.0000 0.0000 0.0000 1.0000
```

`static_inverse_transform_publisher` does the following in a generic way:
```
$ rosrun tf static_transform_publisher $(./inverse_transform.py -x 100. -y 2 -z 0 -R 0 -P 0 -Y 0) source_frame target_frame 100
```

## odom_to_tf

This node updates a transformation between two coordinate frames with a given ros::nav_msgs::Odometry.

### Parameter

|          Name           |  Type  | Default |                                                            Description                                                            |
| ----------------------- | ------ | ------- | --------------------------------------------------------------------------------------------------------------------------------- |
| ros_listener_odom_topic | string | /topic  | Listenertopic for the ros::nav_msgs::Odometry to update the tf.                                                                   |
| parent_frame            | string | /parent | Parent frame id                                                                                                                   |
| child_frame             | string | /child  | Child frame id                                                                                                                    |
| rostimenow              | bool   | false   | If this is set to true, ros::now as headertimestamp will be used otherwhise the timestamp from the input ros::nav_msgs::Odometry. |
