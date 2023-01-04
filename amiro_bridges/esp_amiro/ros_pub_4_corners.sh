rostopic pub -1 /move_base_simple/goal geometry_msgs/PoseStamped '{header: {frame_id: "map"}, pose: {position: {x: +1., y: -1., z: 0.0}, orientation: {x: 0.0, y: 0.0, z: 0.0, w: 1.0}}}'
rostopic pub -1 /move_base_simple/goal geometry_msgs/PoseStamped '{header: {frame_id: "map"}, pose: {position: {x: +1., y: +1., z: 0.0}, orientation: {x: 0.0, y: 0.0, z: 0.707, w: 0.707}}}'
rostopic pub -1 /move_base_simple/goal geometry_msgs/PoseStamped '{header: {frame_id: "map"}, pose: {position: {x: -1., y: +1., z: 0.0}, orientation: {x: 0.0, y: 0.0, z: 1.0, w: 0.0}}}'
rostopic pub -1 /move_base_simple/goal geometry_msgs/PoseStamped '{header: {frame_id: "map"}, pose: {position: {x: -1., y: -1., z: 0.0}, orientation: {x: 0.0, y: 0.0, z: -0.707, w: 0.707}}}'
