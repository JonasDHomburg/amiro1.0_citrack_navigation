rostopic pub -1 /move_base_simple/goal geometry_msgs/PoseStamped '{header: {frame_id: "map"}, pose: {position: {x: +1.0, y: -1.0, z: 0.0}, orientation: {x: 0.0, y: 0.0, z: 0.924, w: 0.383}}}'
read -p "Press enter to continue"
rostopic pub -1 /move_base_simple/goal geometry_msgs/PoseStamped '{header: {frame_id: "map"}, pose: {position: {x: -1.0, y: 0.0, z: 0.0}, orientation: {x: 0.0, y: 0.0, z: 0.383, w: 0.924}}}'
rostopic pub -1 /move_base_simple/goal geometry_msgs/PoseStamped '{header: {frame_id: "map"}, pose: {position: {x: +1.0, y: +1.0, z: 0.0}, orientation: {x: 0.0, y: 0.0, z: 0.383, w: 0.924}}}'
