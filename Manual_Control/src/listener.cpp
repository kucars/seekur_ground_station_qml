/**
 * @file /qlistener/listener.cpp
 *
 * @brief Ros communication central!
 *
 * @date February 2011
 **/

/*****************************************************************************
** Includes
*****************************************************************************/

#include <ros/ros.h>
#include <string>
#include <sstream>
#include "../include/Manual_Control/listener.hpp"
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include "../include/Manual_Control/qnode3.hpp"

/*****************************************************************************
** Implementation
*****************************************************************************/

Listener::Listener(int argc, char** argv ) :
    Manual_Control::QNode3(argc,argv,"qlistener")
    {
    //it_(n);
    }

void Listener::ros_comms_init() {
    qDebug()<<"am in ros_comms_init"<<endl;

    ros::NodeHandle n;//just returned the nodehandle here and deleted everything inside on connect button except the init
    image_transport::ImageTransport it_(n);
    //image_sub_ = it_.subscribe("/camera/rgb/image_raw", 1,
     //     &Listener::chatterCallback, this);

    image_sub_ = it_.subscribe("/camera/rgb/image_raw", 1, &Listener::chatterCallback, this);
    qDebug()<<"am after sub"<<endl;
    // joy_sub_ = n_.subscribe<sensor_msgs::Joy>("/cjlk;j/jljoy", 10, &QNode::joyCallback, this);

   // chatter_subscriber = n.subscribe("chatter", 1000, &Listener::chatterCallback, this);
   // chatter_publisher = n_.advertise<std_msgs::String>("chatter", 1000);

}
QImage Listener::cvtCvMat2QImage(const cv::Mat & image)
{
    QImage qtemp;
    if(!image.empty() && image.depth() == CV_8U)
    {
        const unsigned char * data = image.data;
        qtemp = QImage(image.cols, image.rows, QImage::Format_RGB32);
        for(int y = 0; y < image.rows; ++y, data += image.cols*image.elemSize())
        {
            for(int x = 0; x < image.cols; ++x)
            {
                QRgb * p = ((QRgb*)qtemp.scanLine (y)) + x;
                *p = qRgb(data[x * image.channels()+2], data[x * image.channels()+1], data[x * image.channels()]);
            }
        }
    }
    else if(!image.empty() && image.depth() != CV_8U)
    {
        printf("Wrong image format, must be 8_bits\n");
    }
    return qtemp;
}
void Listener::chatterCallback(const sensor_msgs::ImageConstPtr& msg){

    qDebug()<<"am in chatterCallback"<<endl;


//(const std_msgs::String::ConstPtr &msg) {
    //ROS_INFO("I heard: [%s]", msg->data.c_str());
    cv_bridge::CvImagePtr cv_ptr;
      try
        {
          cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);

        }
        catch (cv_bridge::Exception& e)
        {
          ROS_ERROR("cv_bridge exception: %s", e.what());
          return;
        }
        px = QPixmap::fromImage(cvtCvMat2QImage(cv_ptr->image));
    logging.insertRows(0,1);
    std::stringstream logging_msg;
    logging_msg << "[ INFO] [" << ros::Time::now() << "]: I heard: " << "camera";
    QVariant new_row(QString(logging_msg.str().c_str()));
    logging.setData(logging.index(0),new_row);
    Q_EMIT Update_Image(&px);
}

void Listener::run() {
    qDebug()<<"am in run"<<endl;

    ros::spin();

    //ros::spinOnce();

    std::cout << "Ros shutdown, proceeding to close the gui." << std::endl;
    Q_EMIT rosShutdown(); // used to signal the gui for a shutdown (useful to roslaunch)
}
