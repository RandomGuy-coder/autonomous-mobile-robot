#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <find_object_2d/ObjectsStamped.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <QtCore/QString>
#include <stdlib.h>

using namespace std;

class ObjectFollow {

    typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
    
    public:
    MoveBaseClient* ac;

    ObjectFollow() {
        system("rosnode kill /explore");

        ros::NodeHandle nd("~");
        nd.param("target_frame_id", targetFrameId_, targetFrameId_);
        nd.param("object_prefix", objFramePrefix_, objFramePrefix_);
        ros::NodeHandle subNode;
        ac = new MoveBaseClient("move_base", true);

        subs_ = subNode.subscribe("objectsStamped", 1, &ObjectFollow::objectsDetectedCallback, this);
    }

    void objectsDetectedCallback(const find_object_2d::ObjectsStampedConstPtr & msg) {
        if(msg->objects.data.size() && !objectGoalSent) {

            move_base_msgs::MoveBaseGoal goal;
            goal.target_pose.header.frame_id = targetFrameId_;
            goal.target_pose.header.stamp = ros::Time::now();

            std::string targetFrameId = targetFrameId_;

            int id = (int)msg->objects.data[0];

            // "object_1", "object_1_b", "object_1_c", "object_2"
            std::string objectFrameId = QString("%1_%2").arg(objFramePrefix_.c_str()).arg(id).toStdString();

            tf::StampedTransform pose;
                
            try {
                // Get transformation from "object_#" frame to target frame
                // The timestamp matches the one sent over TF
                system("rosnode kill /explore");
                tfListener_.lookupTransform(targetFrameId, objectFrameId, msg->header.stamp, pose);
                    ROS_INFO("%s [x,y,z] [x,y,z,w] in \"%s\" frame: [%f,%f,%f] [%f,%f,%f,%f]",
                    objectFrameId.c_str(), targetFrameId.c_str(),
                    pose.getOrigin().x(), pose.getOrigin().y(), pose.getOrigin().z(),
                    pose.getRotation().x(), pose.getRotation().y(), pose.getRotation().z(), pose.getRotation().w());

                    goal.target_pose.pose.position.x = pose.getOrigin().x();
                    goal.target_pose.pose.position.y = pose.getOrigin().y();
                    goal.target_pose.pose.orientation.w = 1.0;
                    ac->sendGoal(goal);

                    ac->waitForResult();
                    if(ac->getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
                        objectGoalSent = true;
                        std::cout << "Successfully found object" << std::endl;
                    }
                

            } catch(tf::TransformException & ex) {
                ROS_WARN("%s",ex.what());
            }

            

            // Here "pose" is the position of the object "id" in target frame.
            

        }
    }

    private:
        std::string targetFrameId_;
        std::string objFramePrefix_;
        ros::Subscriber subs_;
        tf::TransformListener tfListener_;
        bool objectGoalSent = false;

};

int main(int argc, char * argv[])
{
    ros::init(argc, argv, "objectFollow");

    ObjectFollow follow;
    ros::spin();
}
