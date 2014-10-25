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

#ifndef logging_QNODE_HPP_
#define logging_QNODE_HPP_

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
/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace logging {

/*****************************************************************************
** Class
*****************************************************************************/

class QNode : public QThread {
    Q_OBJECT
public:
	QNode(int argc, char** argv );
	virtual ~QNode();
	bool init();
	bool init(const std::string &master_url, const std::string &host_url);
	void run();
    ros::Subscriber topic;
    ros::Subscriber topiclaser;
    void topiccallback(const sensor_msgs::ImageConstPtr& top);
    void lasercallback(const sensor_msgs::LaserScanPtr& top);
    void unSubscribeLaser();
    ros::NodeHandle *pt;
    ros::NodeHandle *pt2;
    void subscribe_camera();
    void subscribe_laser();
    void unSubscribe();
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
	void loggingUpdated();
    void rosShutdown();

private:
	int init_argc;
	char** init_argv;
	ros::Publisher chatter_publisher;
    QStringListModel logging_model;
};

}  // namespace logging

#endif /* logging_QNODE_HPP_ */
