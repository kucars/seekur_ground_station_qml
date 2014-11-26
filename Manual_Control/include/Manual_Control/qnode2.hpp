
/**
 * @file /include/logging/qnode.hpp
 *
 * @brief Communications central!
 *
 * @date February 2011
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef QNODE2_H
#define QNODE2_H

/*****************************************************************************
** Includes
*****************************************************************************/

#include <ros/ros.h>
#include <string>
#include <QThread>
#include <QStringListModel>
#include <sensor_msgs/Joy.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Image.h>
#include <QMutexLocker>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>


/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace Manual_Control {

/*****************************************************************************
** Class
*****************************************************************************/

class qnode2 : public QThread {
    Q_OBJECT
public:
    qnode2(int argc, char** argv );
    virtual ~qnode2();
    bool init();
    bool init(const std::string &master_url, const std::string &host_url);
    void run();
    ros::Subscriber topic;
    ros::Subscriber topiclaser;
    ros::Subscriber topic_cmd_vel;
    ros::Subscriber topic_odom;
    void topiccallback(const sensor_msgs::ImageConstPtr& top);
    void lasercallback(const sensor_msgs::LaserScanPtr& top);
    void cmdvelcallback(const geometry_msgs::TwistPtr& top);
    void odomcallback(const nav_msgs::OdometryPtr& top);


    ros::NodeHandle *pt;
    ros::NodeHandle *pt2;
    ros::NodeHandle *pt3;
    ros::NodeHandle *pt4;

    void subscribe_camera();
    void subscribe_laser();
    void unSubscribe();
    void unSubscribeLaser();

    void subscribe_cmd_vel();
    void subscribe_odom();
    void unSubscribe_cmd_vel();
    void unSubscrib_odom();
    void test(int en);
    int check;
   QMutex mutex;
    /*********************
    ** Logging
    **********************/
    enum LogLevel {
             Debug,
             Info,
             Warn,
             Error,
             Fatal
     };

    QStringListModel* loggingModel() { return &logging_model; }
    void log( const LogLevel &level, const std::string &msg);

Q_SIGNALS:
    void loggingUpdated2();
    void rosShutdown();


private:
    int init_argc;
    char** init_argv;
    ros::Publisher chatter_publisher;
    QStringListModel logging_model;
};

}  // namespace logging

#endif /* logging_QNODE_HPP_ */
