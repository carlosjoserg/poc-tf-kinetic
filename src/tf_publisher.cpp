/**
/usr/bin/python
import rospy
import tf


def make_tf(name):
    br = tf.TransformBroadcaster()
    br.sendTransform((0, 0, 0), (1, 0, 0, 0), rospy.Time.now(), name, 'world')

if __name__ == '__main__':
    rospy.init_node('tf_broadcaster')
    name = rospy.get_param('~name')
    rospy.Timer(rospy.Duration(0.01), lambda e:make_tf(name))
    rospy.spin()
**/

#include <ros/ros.h>
#include <tf2_ros/transform_broadcaster.h>
#include <tf2_ros/static_transform_broadcaster.h>

int main(int argc, char **argv)
{
	ros::init(argc, argv, "tf_broadcaster");
	ros::NodeHandle n(ros::this_node::getName());
	std::string name;
	n.getParam("name", name);

	double duration = 0.01;
	n.getParam("duration", duration);
	ROS_INFO_STREAM("MY NAME IS: " << name);

	tf2_ros::TransformBroadcaster tf;
	tf2_ros::StaticTransformBroadcaster static_tf;


	geometry_msgs::TransformStamped transform;
	transform.header.frame_id = "world";
	transform.child_frame_id = name;
	transform.transform.rotation.w = 1;

	geometry_msgs::TransformStamped static_transform = transform;
	static_transform.child_frame_id = name + "_static";

	while(ros::ok())
	{
		transform.header.stamp = ros::Time::now();
		static_transform.header.stamp = ros::Time::now();

		tf.sendTransform(transform);
		static_tf.sendTransform(static_transform);

		ros::Duration(duration).sleep();
		ros::spinOnce();
	}
}
