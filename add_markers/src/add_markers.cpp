#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include "nav_msgs/Odometry.h"
#include <unistd.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
const float initialX = -5.;
const float initialY = -5.;
const float pickupX = 4.;
const float pickupY = -5.;
const float dropoffX = 4.;
const float dropoffY = 2.;
float currentGoalX;
float currentGoalY;
bool reached;
void odomCallback(const nav_msgs::Odometry::ConstPtr& odom_msg) {
  reached = pow(currentGoalX-odom_msg->pose.pose.position.x, 2) + 
            pow(currentGoalY-odom_msg->pose.pose.position.y, 2) < 2.25;
}

int main(int argc, char** argv){
  // Initialize the simple_navigation_goals node
  ros::init(argc, argv, "add_markers");

  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Subscriber odometry_sub = n.subscribe("odom", 1000, odomCallback);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE;

    visualization_msgs::Marker marker;
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "/map";
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "object";
    marker.id = 0;

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    marker.type = shape;

    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    marker.action = visualization_msgs::Marker::ADD;

    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
    currentGoalX = pickupX-initialX;
    currentGoalY = pickupY-initialY;
    marker.pose.position.x = pickupX;
    marker.pose.position.y = pickupY;
    marker.pose.position.z = 1.;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 0.5;
    marker.scale.y = 0.5;
    marker.scale.z = 0.25;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 0.0f;
    marker.color.g = 1.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;

    marker.lifetime = ros::Duration();

    // Publish the marker
    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }
    marker_pub.publish(marker);

    // Cycle between different shapes
    switch (shape)
    {
    case visualization_msgs::Marker::CUBE:
      shape = visualization_msgs::Marker::SPHERE;
      break;
    case visualization_msgs::Marker::SPHERE:
      shape = visualization_msgs::Marker::ARROW;
      break;
    case visualization_msgs::Marker::ARROW:
      shape = visualization_msgs::Marker::CYLINDER;
      break;
    case visualization_msgs::Marker::CYLINDER:
      shape = visualization_msgs::Marker::CUBE;
      break;
    }
    
    while (ros::ok() && !reached) {
      ros::spinOnce();
      r.sleep();
    }
    currentGoalX = dropoffX-initialX;
    currentGoalY = dropoffY-initialY;
    marker.pose.position.x = dropoffX;
    marker.pose.position.y = dropoffY;
    sleep(5);
    marker.action = visualization_msgs::Marker::DELETE;
    marker_pub.publish(marker);
    reached = false;
    while (ros::ok() && !reached) {
      ros::spinOnce();
      r.sleep();
    }
    marker.action = visualization_msgs::Marker::ADD;
    sleep(5);
    marker_pub.publish(marker);
  
    r.sleep();
}