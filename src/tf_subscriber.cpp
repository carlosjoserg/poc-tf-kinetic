/**

#!/usr/bin/python
import rospy
import tf


def check_tfs(listener):
    try:
        (trans, rot) = listener.lookupTransform('world', 'turtle1')
        (trans, rot) = listener.lookupTransform('world', 'turtle1')
    except Exception as e:
        print(e)

if __name__ == '__main__':
    rospy.init_node('tf_listener')
    listener = tf.TransformListener()

    rospy.Timer(rospy.Duration(0.1), lambda e:check_tfs(listener))

    rospy.spin()
**/


#include <ros/ros.h>
#include <tf2_ros/transform_listener.h>

int main(int argc, char **argv)
{
	ros::init(argc, argv, "tf_broadcaster");
	ros::NodeHandle n(ros::this_node::getName());

	tf2_ros::Buffer buffer;
	tf2_ros::TransformListener tf_listener(buffer, n);

	ros::spin();
}
