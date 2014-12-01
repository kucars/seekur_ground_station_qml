
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

#include <ros/ros.h>
#include <ros/network.h>
#include <string>
#include <std_msgs/String.h>
#include <sstream>
#include "../include/Manual_Control/qnode.hpp"
#include <sensor_msgs/JointState.h>
#include <geometry_msgs/Twist.h>
#include<string.h>

/*****************************************************************************
** Namespaces
********************
*********************************************************/

// at full joystick depression you'll go this fast
double max_speed_arm = 0.100; // m/second
double max_turn_arm = 60.0*M_PI/180.0; // rad/second
// should we continuously send commands?

namespace Manual_Control {
using namespace std;
/*****************************************************************************
** Implementation
*****************************************************************************/
QNode::QNode(){
     qDebug()<<"am in qnode constructor1"<<endl;

      max_tv_ = max_speed_arm;
      max_rv_ = max_turn_arm;
      check=-1;
}

QNode::QNode(int argc, char** argv ) :
    init_argc(argc),
    init_argv(argv)

    {
    check=-1;
    }

QNode::~QNode() {
    if(ros::isStarted()) {
      ros::shutdown(); // explicitly needed since we use ros::start();
      ros::waitForShutdown();
    }
    wait();
}

bool QNode::init() {
  ros::init(init_argc,init_argv,"Manual_Control");
   qDebug()<<"am in init"<<endl;
 if ( ! ros::master::check() ) {
      return false;
  }

  ros::start(); // explicitly needed since our nodehandle is going out of scope.
  ros::NodeHandle n_;
  ros::NodeHandle n2;
  qDebug()<<"i am now checking for check value"<<endl;


  if (check==0)
  {
       qDebug()<<"check value... is 0"<<endl;
      pub = n_.advertise<sensor_msgs::JointState>("/joint_states",1);
  }

  else
      if(check==1)
      {
            qDebug()<<"check value...is 1"<<endl;
            pub2 = n2.advertise<geometry_msgs::Twist>("/RosAria/cmd_vel",1);
      }

      else if(check==2)
   {
        qDebug()<<"check value.. is 2"<<endl;
        pub.shutdown();
   }

    else if(check==3)
     {
     qDebug()<<" check value..is 3"<<endl;
     pub2.shutdown();
     qDebug()<<" check value..is 3 after"<<endl;

      }

   chatter_publisher = n_.advertise<std_msgs::String>("chatter", 1000);
   start();
    return true;
}

void QNode::keyPressed(int keyId)
{
    QMutexLocker lock(&mutex);
    isKeyPressed = true;
    this->keyId = keyId;
     qDebug()<<"here in keypressed key id is "<<keyId;
}


void QNode::test(int en)
{
      qDebug()<<"i am in test4"<<endl;
      check=en;
      qDebug()<<"check value is "<<check<<"\n";

}


void QNode::run()
{

    if (check==0){
         qDebug()<<" check in run ..is 0"<<endl;
    ros::Rate loop_rate(10);
    int selectedjoint;
    // double i[5]={0,-40,-90,-40,0};
    i[0]=0;
    i[1]=-30;
    i[2]=-90;
    i[3]=-40;
    i[4]= 0;
    double k = 0;
    QString grip_status;

    while(ros::ok() && check==0/*&& pub_*/)
    {
        QString name ;
        if(isKeyPressed)
        {
            //QString name ;
            double jointPose = 0;
            if(joint == QString("j1"))
            {
                name = "j1";
                selectedjoint=0;
                jointPose = i[0];
            }
            else if(joint == QString("j2"))
            {
                qDebug()<<" Joint 2"<<jointPose;
                name = "j2";
                selectedjoint=1;
                jointPose =i[1];

            }
            else if(joint == QString("j3"))
            {
                name = "j3";
                selectedjoint=2;
                jointPose =i[2];
                qDebug()<<" Joint 3"<<jointPose;

            }
            else if(joint == QString("j4"))
            {
                name = "j4";
                selectedjoint=3;
                jointPose =i[3];
                qDebug()<<" Joint 3"<<jointPose;

            }
            else if(joint == QString("j5"))
            {
                name = "j5";
                selectedjoint=4;
                jointPose =i[4];
                qDebug()<<" Joint 3"<<jointPose;

            }
            else if(joint == QString("g"))
            {
                name = "g";

                qDebug()<<" Gripper"<<jointPose;
            }
            else if(joint == QString("grasp"))
            {
                name = "grasp";

            }

            qDebug()<<"Moving Joint"<<name<<" and joint is:"<<joint;
            // do something
            mutex.lock();
            isKeyPressed = false;
            mutex.unlock();
            switch(keyId)
            {
            case UP:
                if(name == QString("g"))
                {
                    grip_status = "open";
                    j.name.push_back(name.toStdString());
                    j.position.push_back(0);
                    pub.publish(j);
                }

                else
                {
                j.name.push_back(name.toStdString());
                i[selectedjoint] = jointPose+10;
                j.position.push_back(i[selectedjoint]);
                pub.publish(j);
                }
                break;
            case DOWN:
                if(name == QString("g"))
                {
                    grip_status = "closed";

                     qDebug()<<"i am now in case down before before publishing"<<endl;
                    j.name.push_back(name.toStdString());
                    j.position.push_back(1);
                    pub.publish(j);
                     qDebug()<<"i am now in case down after publishing"<<endl;
                }
                else if(name == QString("grasp"))
                {
                    j.name.push_back(name.toStdString());
                    j.position.push_back(1);
                    pub.publish(j);
                }
                else
                {
                j.name.push_back(name.toStdString());
                i[selectedjoint] = jointPose-10;
                j.position.push_back(i[selectedjoint]);
                pub.publish(j);
                }

                break;

            }

            QString stringjoint = "joint 1 \t joint 2 \t joint 3 \t joint 4 \t joint 5 \t Gripper\n";
                        QString string1 = "";

                        for (int k=0;k<5;k++)
                         {
                             string1 = string1+QString::number(i[k])+"\t";//qt visualizers seen view //radio checks//regidtry q settings
                         }

                       // log(Info,std::string("Linear velocity:  "+j1.toStdString()));
                        string1 = string1 + grip_status;
                        log(Info,std::string(stringjoint.toStdString()+string1.toStdString()));


            qDebug()<<"Size of j:"<<j.name.size();
        }


        std_msgs::String msg;
        chatter_publisher.publish(msg);
        j.name.clear();
        j.position.clear();
        ros::spinOnce();
        loop_rate.sleep();
    }

}


    else
        if (check==1)//seekur
        {
            ros::Rate loop_rate(1);
            ros::spinOnce();
            int scalingfactor = 1;
            double x = 0.1;
            while(ros::ok() && check==1/*&& pub_*/)
            {
               if(isKeyPressed)
                {
                    // do something
                    mutex.lock();
                    isKeyPressed = false;
                    mutex.unlock();
                    switch(keyId)
                    {
                    case SPACEB:
                       cmdvel.linear.x=0.0;
                       cmdvel.angular.z=0.0;
                        break;
                    case DOWN:
                        cmdvel.linear.x = -x;
                        cmdvel.angular.z = 0.0;
                        break;
                    case UP:
                        cmdvel.linear.x = x;
                        cmdvel.angular.z = 0.0;
                        break;
                    case RIGHTB:
                        cmdvel.linear.x = 0.0;//0.2
                        cmdvel.angular.z = -0.3;//doesn't always work
                        break;
                    case LEFTB:
                        cmdvel.linear.x = 0.0;//0.1
                        cmdvel.angular.z = 0.3;
                        break;
                    case SHIFTB:
                        scalingfactor++;
                        if(scalingfactor == 6)
                        {
                            scalingfactor =  5;
                        }
                        else if(scalingfactor <= 0)
                        {
                            scalingfactor = 1;
                        }
                        x = 0.1 * scalingfactor;
                        if(cmdvel.linear.x<0)
                        {
                            cmdvel.linear.x = -x;
                            cmdvel.angular.z = 0.0;
                        }
                        else if(cmdvel.linear.x>0)
                        {
                            cmdvel.linear.x = x;
                            cmdvel.angular.z = 0.0;
                        }
                        break;
                    case CTRLB:
                        scalingfactor--;
                        if(scalingfactor == 6)
                        {
                            scalingfactor =  5;
                        }
                        else if(scalingfactor <= 0)
                        {
                            scalingfactor = 1;
                        }
                        x = 0.1 * scalingfactor;
                        if(cmdvel.linear.x<0)
                        {
                            cmdvel.linear.x = -x;
                            cmdvel.angular.z = 0.0;
                        }
                        else if(cmdvel.linear.x>0)
                        {
                            cmdvel.linear.x = x;
                            cmdvel.angular.z = 0.0;
                        }
                        break;
                    default:
                        qDebug()<<"unknown key";
                    }

                    QString m= QString::number(cmdvel.linear.x);
                    QString z= QString::number(cmdvel.angular.z);

                    log(Info,std::string("Linear velocity:  "+m.toStdString()+"\nAngular velocity:  "
                                         +z.toStdString()));

                    pub2.publish(cmdvel);

                std_msgs::String msg;
                 chatter_publisher.publish(msg);
                    loop_rate.sleep();
                }
            }
        }
}

double* QNode::jointpostion(){
    double* kk= new double[5];
   // kk[3]=i[3];
    for (int h=0;h<5;h++)
    {
        kk[h]=i[h];
        qDebug()<<"IN joint position:  ";
        qDebug()<<kk[h];
   }
    return kk;
}

double QNode::speed(){
    double kk=cmdvel.linear.x;
    return kk;
   //string m = "Hello";
    //retrun m
}

double QNode::speed2(){
    double kk=cmdvel.linear.z;
    return kk;
   //string m = "Hello";
    //retrun m
}

void QNode::log( const LogLevel &level, const std::string &msg) {
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
                logging_model_msg << "[INFO] [" << ros::Time::now() << "]: " << msg;
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
    Q_EMIT loggingUpdated(); // used to readjust the scrollbar
}

void QNode::setJoint(QString j)
{
    QMutexLocker locker(&mutex);
    this->joint=j;
    qDebug()<<"Setting joint name to :"<<j;
}

void QNode::stopRobot()
{
    cmdvel.linear.x = cmdvel.angular.z = 0.0;
    pub2.publish(cmdvel);
}
}  // namespace Manual_Control
