/**
 * @file /eros_qtalker/include/eros_qtalker/qnode3.hpp
 *
 * @brief Ros communication central!
 *
 * @date February 2011
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef QNODE3_HPP
#define QNODE3_HPP
/*****************************************************************************
** Includes
*****************************************************************************/

#include <ros/ros.h>
#include <string>
#include <QThread>
#include <QStringListModel>
#include <QDebug>
/*****************************************************************************
** Class
*****************************************************************************/
namespace Manual_Control {
using namespace std;

class QNode3 : public QThread {
Q_OBJECT

public:
    QNode3(int argc, char** argv, const std::string &name );
    virtual ~QNode3();

    bool on_init();
    bool on_init(const std::string &master_url, const std::string &host_url);
    void shutdown();
    virtual void run() = 0;

    QStringListModel* loggingModel() { return &logging; }
    QPixmap PixmapModel (){return px;}
    const std::string& nodeName() { return node_name; }

Q_SIGNALS:
    void loggingUpdated3();
    void rosShutdown();

protected:
    virtual void ros_comms_init() = 0;
    int init_argc;
    char** init_argv;
    QStringListModel logging;
    QPixmap px;
    const std::string node_name;
     //ros::NodeHandle  *n;
};
}//namespace
#endif
