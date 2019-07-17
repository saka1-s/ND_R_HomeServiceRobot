export ROBOT_INITIAL_POSE="-x 5.0 -y -5. -z 0. -R 0. -P 0. -Y 1.57"
xterm  -e  " roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=/home/workspace/catkin_ws/src/turtlebot_simulator/turtlebot_gazebo/worlds/Project1.world " &
sleep 15
xterm  -e  " roslaunch turtlebot_gazebo amcl_demo.launch map_file:=/home/workspace/catkin_ws/src/map/myworld.yaml  initial_pose_x:=-5. initial_pose_y:=-5." &
sleep 5
xterm  -e  " roslaunch turtlebot_rviz_launchers view_navigation.launch " &