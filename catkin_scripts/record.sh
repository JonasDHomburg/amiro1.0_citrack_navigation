rosbag record --split --duration=128 -O tumbling.bag -e /tf* /vectorfield/image/gridmap/rbg_image /vectorfield/amiro7/gridmap/rgb_image /genicam_cam5/image_color /radar_rl/sensor /radar_rr/sensor /os_cloud_node/points /amiro7/odom /vicon/amiro7/pose

rsb-logger --scope /amiro7/ringProx --style detailed