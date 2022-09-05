#include "ros/ros.h"
#include "std_msgs/Float64.h"

int main(int argc, char **argv) {
    ros::init(argc, argv, "talker");

    ros::NodeHandle n;

    ros::Publisher pub = n.advertise<std_msgs::Float64>("/rotate_model/kinect_joint_controller/command", 10);

    ros::Rate loop_rate(0.2);

    
    double lastTime = 0.0;
    while(ros::ok())
    {
        std_msgs::Float64 msg;

        if(lastTime == 0.0 || lastTime == -0.5) {
            msg.data = 0.5;
            lastTime = 0.5;
        } else if (lastTime == 0.5) {
            msg.data = -0.5;
            lastTime = -0.5;
        }    
        
        pub.publish(msg);
        loop_rate.sleep();
    }

    return 0;

}