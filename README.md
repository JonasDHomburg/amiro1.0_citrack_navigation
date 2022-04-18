# Vector Field Navigation - Vicon Version
This is a refresh and adaptation of the [amiro_potential_field_navigation](https://github.com/tik0/amiro_potential_field_navigation).
The main changes are:
- Replacing visual tracking with the more precise Vicon tracking system.
- using directly vector fields instead of generating a vector field based on a potential field

## Amiro Bridges
Collection of bridges from and to ROS based on the used AMiRo version.
Currently provided:
- rsb - ros

## AMiRo Robot
ROS AMiRo model and configurations. 
Definition of sensor dependent rsb messages.
See [amiro_robot/README.md](amiro_robot/README.md) for further information.

## CITrack Vicon
Driver for Motion Capture Systems - ROS only with lab specific launch files.

## Dynamic Transform
Dynamic changeable transforms for lab calibration.
See [dynamic_transform/README.md](dynamic_transform/README.md) for further information.

## Launch Scripts
ROS launch files for different demonstration scenarios.

## Ouster Lidar
Ousters lidar example repository for ROS.
Full [example](https://github.com/ouster-lidar/ouster_example).

## Radar Ethernet Ros
Part of an unfinished project.

## RVIZ Textured Quads
RVIZ plugin to display textured images (realtime or static sensor_msgs/Image topics) in 3D space. 
See [rviz_textured_quads/README.md](rviz_textured_quads/README.md) for further information.

## Vector Field Navigation
Former developed as 'potentialfield navigation'.
Now adapted and extended as a navigation based on a vector field.