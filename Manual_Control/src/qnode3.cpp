/**
 * @file /eros_qtalker/src/QNode3.cpp
 *
 * @brief Ros communication central!
 *
 * @date February 2011
 **/

/*****************************************************************************
** Includes
*****************************************************************************/

#include <ros/ros.h>
#include <ros/network.h>
#include <string>
#include "../include/Manual_Control/qnode3.hpp"
#include <std_msgs/String.h>
#include <sstream>

/*****************************************************************************
** Implementation
*****************************************************************************/
namespace Manual_Control {
using namespace std;


QNode3::QNode3(int argc, char** argv, const std::string &name ) :
    init_argc(argc),
    init_argv(argv),
    node_name(name)
    {}

QNode3::~QNode3() {
    shutdown();
    //delete n;
}

void QNode3::shutdown() {
    if(ros::isStarted()) {
      ros::shutdown(); // explicitly needed since we use ros::start();
      ros::waitForShutdown();
    }
    wait();
}

bool QNode3::on_init() {
    qDebug()<<"am in init"<<endl;
    ros::init(init_argc,init_argv,node_name);
    qDebug()<<"am after init"<<endl;

    if ( ! ros::master::check() ) {
        qDebug()<<"ros master not working"<<endl;
        return false;

    }
    qDebug()<<"am after init 222"<<endl;

    ros::start(); // our node handles go out of scope, so we want to control shutdown explicitly.
    //ros::NodeHandle n;
    qDebug()<<"am after ros::start"<<endl;

    ros_comms_init();
    start();
    return true;
}
}//namespace
