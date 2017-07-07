#include <ros/ros.h>
#include <nodelet/nodelet.h>
#include <pluginlib/class_list_macros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <boost/thread.hpp>
#include <pylon_camera/pylon_camera_node.h>
#include <boost/bind.hpp>

namespace pylon_camera
{
    class PylonNodelet : public nodelet::Nodelet
    {
        private:
            PylonCameraNode pylon_camera_node;

            void spinPylon()
            {
                // poll the camera infinitely
                ros::Rate rate(30);
                while (ros::ok())
                {
                    pylon_camera_node.spin();
                    rate.sleep();
                }
            }

        public:
            virtual void onInit()
            {
                NODELET_INFO_STREAM("Start image grabbing if node connects to topic with "
                        << "a frame_rate of: " << pylon_camera_node.frameRate() << " Hz");

                // Main thread and brightness-service thread
                boost::thread th(boost::bind(&PylonNodelet::spinPylon, this));
            }

    };

}
PLUGINLIB_EXPORT_CLASS(pylon_camera::PylonNodelet, nodelet::Nodelet)
