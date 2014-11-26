/**
 * @file /src/qnode.cpp
 *
 * @brief Ros communication central!
 *
 * @date February 2011
 **/

/*****************************************************************************
** Includes
*****************************************************************************/
#include <iostream>
#include <ros/ros.h>
#include <ros/network.h>
#include <string>
#include <std_msgs/String.h>
#include <sstream>
#include "../include/Manual_Control/qnode2.hpp"
#include <sensor_msgs/Joy.h>
#include <QDebug>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/LaserScan.h>
#include <QMutexLocker>
#include <geometry_msgs/Twist.h>

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace Manual_Control {
using namespace std;
/*****************************************************************************
** Implementation
*****************************************************************************/

qnode2::qnode2(int argc, char** argv ) :
    init_argc(argc),
    init_argv(argv)
    {

    check=-1;
}

qnode2::~qnode2() {
    if(ros::isStarted()) {
      ros::shutdown(); // explicitly needed since we use ros::start();
      ros::waitForShutdown();
    }
    wait();
}
bool qnode2::init() {
    qDebug()<<"I am in init 1"<<endl;
    ros::init(init_argc,init_argv,"logging");
    if ( ! ros::master::check() ) {
        return false;
    }
    ros::start(); // explicitly needed since our nodehandle is going out of scope.
    // Add your ros communications here.
    //topic = n_.subscribe<geometry_msgs::Twist>("/cmd_vel", 10, &QNode::topiccallback, this);
    //image_sub_ = it_.subscribe("/camera/rgb/image_raw", 1, &Listener::chatterCallback, this);

  //topic= n.subscribe("/camera/rgb/image_raw", 1, &QNode::topiccallback, this);

    ros::NodeHandle n;
    ros::NodeHandle n2;
    ros::NodeHandle n3;
    ros::NodeHandle n4;

    pt2=&n2;
    pt =&n;
    pt3 = &n3;
    pt4 =&n4;



  // topic= pt->subscribe("/camera/rgb/image_raw", 1, &QNode::topiccallback, this);

   //qDebug()<<"I just subscribed in init"<<endl;

 //   chatter_publisher = n.advertise<geometry_msgs::TwistPtr>("/cmd_vel",)


    if (check==0)
        subscribe_camera();            
        else
        if(check==1)
            unSubscribe();
        else
            if(check==3)
                unSubscribeLaser();
            else
                if(check==2)
                    subscribe_laser();
                else
                   if(check==4)
                       subscribe_cmd_vel();
                   else
                      if(check==5)
                          unSubscribe_cmd_vel();
                       else
                          if(check==6)
                              subscribe_odom();
                           else
                              if(check==7)
                                  unSubscrib_odom();


    start();
    return true;
}

bool qnode2::init(const std::string &master_url, const std::string &host_url) {
    std::map<std::string,std::string> remappings;
    remappings["__master"] = master_url;
    remappings["__hostname"] = host_url;
    ros::init(remappings,"logging");
    if ( ! ros::master::check() ) {
        return false;
    }
    ros::start(); // explicitly needed since our nodehandle is going out of scope.
    ros::NodeHandle n;
    // Add your ros communications here.
    chatter_publisher = n.advertise<std_msgs::String>("chatter", 1000);
    start();
    return true;
}

void qnode2::run() {
    ros::Rate loop_rate(1);
    int count = 0;
    while ( ros::ok() ) {

        std_msgs::String msg;
        std::stringstream ss;
        ss << "hello world " << count;
        msg.data = ss.str();
        //chatter_publisher.publish(msg);
        //log(Info,std::string("I sent: ")+msg.data);
//        mutex.lock();

       /* if (check == true){
    qDebug()<<"checked is true in run 5"<<endl;


}*/


//        mutex.unlock();

     //   ros::spinOnce();
       // subscribe_camera();
        ros::spin();
        loop_rate.sleep();
        ++count;
    }
    std::cout << "Ros shutdown, proceeding to close the gui." << std::endl;
    Q_EMIT rosShutdown(); // used to signal the gui for a shutdown (useful to roslaunch)
}


void qnode2::log( const LogLevel &level, const std::string &msg) {
    logging_model.insertRows(logging_model.rowCount(),1);
    std::stringstream logging_model_msg;
    switch ( level ) {
        case(Debug) : {
                ROS_DEBUG_STREAM(msg);
                logging_model_msg << "[DEBUG] [" << ros::Time::now() << "]: " << msg;
                break;
        }
        case(Info) : {
                ROS_INFO_STREAM(msg);
                //logging_model_msg << "[INFO] [" << ros::Time::now() << "]: " << msg;
                logging_model_msg << "[INFO]:" << msg;
                break;
        }
        case(Warn) : {
                ROS_WARN_STREAM(msg);
                logging_model_msg << "[INFO] [" << ros::Time::now() << "]: " << msg;
                break;
        }
        case(Error) : {
                ROS_ERROR_STREAM(msg);
                logging_model_msg << "[ERROR] [" << ros::Time::now() << "]: " << msg;
                break;
        }
        case(Fatal) : {
                ROS_FATAL_STREAM(msg);
                logging_model_msg << "[FATAL] [" << ros::Time::now() << "]: " << msg;
                break;
        }
    }
    QVariant new_row(QString(logging_model_msg.str().c_str()));
    logging_model.setData(logging_model.index(logging_model.rowCount()-1),new_row);
    Q_EMIT loggingUpdated2(); // used to readjust the scrollbar
}

void qnode2::topiccallback(const sensor_msgs::ImageConstPtr& top)
{
    qDebug()<<"I sm in camera callback\n";
    log(Info,std::string("I am currently subscribed to the topic /camera/rgb/image_raw"));
    //qDebug()<<"I am currently subscribed to the topic /camera/rgb/image_raw and receiving data from it"<<endl;
}


void qnode2::subscribe_camera()
{
    qDebug()<<"I am before the subs 666"<<endl;
    topic = pt->subscribe("/camera/rgb/image_raw", 1, &qnode2::topiccallback, this);
    qDebug()<<"I am after the subs 777"<<endl;

}

void qnode2::unSubscribe()
{
    qDebug()<<"i am in unsubscribe"<<endl;
    topic.shutdown();
}

void qnode2::odomcallback(const nav_msgs::OdometryPtr& top)
{
    log(Info,std::string("I am currently subscribed to the topic /odom"));
}

void qnode2::subscribe_odom()
{

    topic_odom=pt4->subscribe("/RosAria/pose",1,&qnode2::odomcallback,this);
}

void qnode2::unSubscrib_odom()
{
    topic_odom.shutdown();
}

void qnode2::cmdvelcallback(const geometry_msgs::TwistPtr& top)
{
    log(Info,std::string("I am currently subscribed to the topic /cmd_vel"));
}

void qnode2::subscribe_cmd_vel()
{

    topic_cmd_vel=pt3->subscribe("/cmd_vel",1,&qnode2::cmdvelcallback,this);
}

void qnode2::unSubscribe_cmd_vel()
{
    topic_cmd_vel.shutdown();
}

void qnode2::lasercallback(const sensor_msgs::LaserScanPtr& top)
{
    log(Info,std::string("I am currently subscribed to the topic /scan"));

}


void qnode2::subscribe_laser()
{
    qDebug()<<"I am before the subs 6"<<endl;
    topiclaser = pt2->subscribe("/scan", 10, &qnode2::lasercallback, this);
    qDebug()<<"I am after the subs "<<endl;

}

void qnode2::unSubscribeLaser()
{
    qDebug()<<"i am in unsubscribe"<<endl;
    topiclaser.shutdown();
}


void qnode2::test(int en)
{
    qDebug()<<"i am in test4"<<endl;
      check=en;
      qDebug()<<"check value is "<<check<<"\n";

}




}  // namespace logging


