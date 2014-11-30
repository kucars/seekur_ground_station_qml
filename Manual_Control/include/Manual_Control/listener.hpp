#ifndef LISTENER_HPP
#define LISTENER_HPP

#include <ros/ros.h>
#include "qnode3.hpp"
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>


class Listener : public Manual_Control::QNode3
{
     Q_OBJECT
public:
    Listener(int argc, char** argv);
    virtual ~Listener() {}
    void run();
    void ros_comms_init();
Q_SIGNALS:
    void Update_Image(const QPixmap* image);
private:

    image_transport::Subscriber image_sub_;
//	void chatterCallback(const std_msgs::String::ConstPtr &msg);
    void chatterCallback(const sensor_msgs::ImageConstPtr& msg);
    QImage cvtCvMat2QImage(const cv::Mat & image);
    //ros::Subscriber chatter_subscriber;
};


#endif // LISTENER_HPP


