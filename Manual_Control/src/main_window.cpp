/**
 * @file /src/main_window.cpp
 *
 * @brief Implementation for the qt gui.
 *
 * @date February 2011
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include <QtGui>
#include <QMessageBox>
#include <iostream>
#include "../include/Manual_Control/main_window.hpp"
#include <QPushButton>
#include <QRadioButton>
#include <QDebug>
#include "../include/Manual_Control/qnode.hpp"
#include "../include/Manual_Control/qnode2.hpp"
#include <string.h>
#include"../include/Manual_Control/myviz.h"

/*****************************************************************************
** Namespaces
*****************************************************************************/
int current_view=-1;
//0 arm 1 seekur
namespace Manual_Control {

using namespace Qt;
using namespace std;
/*****************************************************************************
** Implementation [MainWindow]
*****************************************************************************/
void MainWindow::keyPressEvent(QKeyEvent *e)
{
    QString string1="";

//arm
    if(current_view==0){

    double *m = qnode.jointpostion();

    if(e->key() == Qt::Key_Up)
    {
        //remove zero
        qnode.keyPressed(UP);

        qDebug()<<"keyPressed "<<e->key();
    }

    else if(e->key() == Qt::Key_Down)
    {
        qnode.keyPressed(DOWN);
        qDebug()<<"keyPressed "<<e->key();
    }


    QString string2 = "joint 1 \t joint 2 \t joint 3 \t joint 4 \t joint 5 \t Gripper\n";

   for (int i=0;i<5;i++)
    {
        string1 = string1+QString::number(m[i])+"\t";//qt visualizers seen view //radio checks//regidtry q settings
    }


   string1=string1+"closed";

    ui.postion_view->setText(string2 + string1);
    }

    else
        if (current_view==1)
        {
            // qDebug()<<"keyPressed "<<e->key();
             if(e->key() == Qt::Key_Up)
             {
                 //remove zero
                 qnode.keyPressed(UP);

                 qDebug()<<"keyPressed "<<e->key();
             }

             else if(e->key() == Qt::Key_Down)
             {
                 qnode.keyPressed(DOWN);
                 qDebug()<<"keyPressed "<<e->key();
             }

             else if(e->key() == Qt::Key_Right)
             {
                 qnode.keyPressed(RIGHTB);
                 qDebug()<<"keyPressed "<<e->key();
             }
             else if(e->key() == Qt::Key_Left)
             {
                 //qDebug("am in left");
                 qnode.keyPressed(LEFTB);
                 qDebug()<<"keyPressed "<<e->key();
             }
             else if (e->key() == Qt::Key_Space)
             {
                 qnode.keyPressed(SPACEB);
                 qDebug()<<"keyPressed "<<e->key();
             }
             else if (e->key() == Qt::Key_Shift)
             {
                 //qDebug("am in shift");
                 qnode.keyPressed(SHIFTB);
                 qDebug()<<"keyPressed "<<e->key();
             }

             else if (e->modifiers().testFlag(Qt::ControlModifier))
             {
                      if(e->key() == Qt::Key_Down)
             {
                 qDebug("am in CTRL+UP");
                 qnode.keyPressed(CTRLB);
                 //qDebug()<<"keyPressed 1"<<e->key();
                 //qDebug()<<"keyPressed 2"<<e->modifiers();

             }
         }

//             double num = qnode.speed();
//              QString m= QString::number(num);
//              QString n="The linear velocity is: ";
//              QString o = "\n";
//              QString p = "The anguler velocity is: ";
//              double num2 = qnode.speed2();
//              QString f= QString::number(num2);
//              ui.label_4->setText(n+m+o+p+f);

        }





}

MainWindow::MainWindow(int argc, char** argv, QNode3 *node, QWidget *parent)
    : QMainWindow(parent), qnode(argc,argv), qnode_2(argc,argv), qnode_3(node)
{

    MyViz* m= new MyViz (argc, argv);

    //m->show();
    ui.setupUi(this); // Calling this incidentally connects all ui's triggers to on_...() callbacks in this class creates user interface.
    QObject::connect(ui.actionAbout_Qt, SIGNAL(triggered(bool)), qApp, SLOT(aboutQt())); // qApp is a global variable for the application


    QObject::connect(ui.radiojoint,SIGNAL(clicked()), this, SLOT(radioButton_setjoint()));
    QObject::connect(this->ui.radiojoint_2,SIGNAL(clicked()), this, SLOT(radioButton_2_setjoint()));
    QObject::connect(this->ui.radiojoint_3,SIGNAL(clicked()), this, SLOT(radioButton_3_setjoint()));
    QObject::connect(this->ui.radiojoint_4,SIGNAL(clicked()), this, SLOT(radioButton_4_setjoint()));
    QObject::connect(this->ui.radiojoint_5,SIGNAL(clicked()), this, SLOT(radioButton_5_setjoint()));
    QObject::connect(this->ui.gripper,SIGNAL(clicked()), this, SLOT(setGripper()));
    QObject::connect(this->ui.grasp_position,SIGNAL(clicked()), this, SLOT(setGrasp()));



    this->setFocusPolicy(Qt::StrongFocus);
//    ReadSettings();
    setWindowIcon(QIcon(":/images/icon.png"));
    ui.tab_manager->setCurrentIndex(0); // ensure the first tab is showing - qt-designer should have this already hardwired, but often loses it (settings?).
    setWindowTitle(QApplication::translate("MainWindowDesign", qnode_3->nodeName().c_str(), 0));


    QObject::connect(&qnode, SIGNAL(rosShutdown()), this, SLOT(close()));

    ui.tab_2->setLayout(m->layout());


    ui.view_logging->setModel(qnode.loggingModel());
    QObject::connect(&qnode, SIGNAL(loggingUpdated()), this, SLOT(updateLoggingView()));

    ui.view_logging_2->setModel(qnode_2.loggingModel());
    QObject::connect(&qnode_2, SIGNAL(loggingUpdated2()), this, SLOT(updateLoggingView2()));

    ui.view_logging_3->setModel(qnode_3->loggingModel());
    QObject::connect(qnode_3, SIGNAL(loggingUpdated3()), this, SLOT(updateLoggingView3()));
    ui.lbimage->setPixmap(qnode_3->PixmapModel());

    qnode_3->on_init();
}

MainWindow::~MainWindow() {}

/*****************************************************************************
** Implementation [Slots]
*****************************************************************************/
void MainWindow::showNoMasterMessage() {
    QMessageBox msgBox;
    msgBox.setText("Couldn't find the ros master.");
    msgBox.exec();
    close();
}

/*
 * These triggers whenever the button is clicked, regardless of whether it
 * is already checked or not.
 */

void MainWindow::on_button_connect_clicked(bool check ) {

    qDebug()<<"IN CONNECT BUTTON";
    qnode.init();
}

//arm
void MainWindow::on_checkBox_toggled()
{
        if(ui.checkBox->isChecked())
        {
            if(ui.checkBox_2->isChecked())
            {
            ui.checkBox_2->setChecked(false);
            }

//            ui.radiojoint->setEnabled(false);
//            ui.radiojoint_2->setEnabled(false);
//            ui.radiojoint_3->setEnabled(false);
//            ui.radiojoint_4->setEnabled(false);
//            ui.radiojoint_5->setEnabled(false);
//            ui.gripper->setEnabled(false);
//            ui.grasp_position->setEnabled(false);

            qnode.test(1);
            current_view=1;

        }

        else
           qnode.test(3);

qnode.init();
}


void MainWindow::on_checkBox_2_toggled()
{
        if(ui.checkBox_2->isChecked())
        {
            if(ui.checkBox->isChecked())
            {
            ui.checkBox->setChecked(false);
            }

             qnode.test(0);
            current_view=0;
//            ui.radiojoint->setEnabled(true);
//            ui.radiojoint_2->setEnabled(true);
//            ui.radiojoint_3->setEnabled(true);
//            ui.radiojoint_4->setEnabled(true);
//            ui.radiojoint_5->setEnabled(true);
//            ui.gripper->setEnabled(true);
//            ui.grasp_position->setEnabled(true);


         }

       else{

        qnode.test(2);

        }
qnode.init();
}



void MainWindow::radioButton_setjoint() {
    if (ui.radiojoint->isEnabled()){

    if(ui.radiojoint->isChecked())
    {
        qnode.setJoint("j1");
    }
}}
void MainWindow::radioButton_2_setjoint() {
    if (ui.radiojoint_2->isEnabled()){

    if(ui.radiojoint_2->isChecked())
    {
        qDebug()<<"IN radioButton_2_setjoint()";
        qnode.setJoint("j2");
    }}
}
void MainWindow::radioButton_3_setjoint() {
    if (ui.radiojoint_3->isEnabled()){

    if(ui.radiojoint_3->isChecked())
    {
        qnode.setJoint("j3");
    }
}}
void MainWindow::radioButton_4_setjoint() {
    if (ui.radiojoint_4->isEnabled()){

    if(ui.radiojoint_4->isChecked())
    {
        qnode.setJoint("j4");
    }
}}
void MainWindow::radioButton_5_setjoint() {
    if (ui.radiojoint_5->isEnabled()){
    if(ui.radiojoint_5->isChecked())
    {
        qnode.setJoint("j5");
    }}
}

void MainWindow::setGripper() {
    if (ui.gripper->isEnabled()){

    if(ui.gripper->isChecked())
    {
        qnode.setJoint("g");
    }}}

void MainWindow::setGrasp() {
    if (ui.grasp_position->isEnabled()){

    if(ui.grasp_position->isChecked())
    {
        qnode.setJoint("grasp");
    }}
}





void MainWindow::on_radioButton_toggled()
{
    QDateTime current = QDateTime::currentDateTime();
    QString time = current.toString("yyyy-MM-dd hh:mm:ss");




    qDebug()<<"radio 1 toggled\n";
        if(ui.radioButton->isChecked())
        {
            myfile <<time.toStdString()<<": User chose camera topic\n"<<endl;
            qnode_2.test(0);

        }

        else
            qnode_2.test(1);

qnode_2.init();
}


void MainWindow::on_radioButton_2_toggled()
{

    QDateTime current = QDateTime::currentDateTime();
    QString time = current.toString("yyyy-MM-dd hh:mm:ss");
        if(ui.radioButton_2->isChecked())
        {
            myfile <<time.toStdString()<<": User choose laser /scan topic\n"<<endl;
            qnode_2.test(2);
        }
        else
            qnode_2.test(3);

qnode_2.init();
}

void MainWindow::on_radioButton_3_toggled()
{
    QDateTime current = QDateTime::currentDateTime();
    QString time = current.toString("yyyy-MM-dd hh:mm:ss");

        if(ui.radioButton_3->isChecked())
        {
            myfile <<time.toStdString()<<": User choose velocity command topic\n"<<endl;
            qnode_2.test(4);
        }
        else
            qnode_2.test(5);
        qnode_2.init();

}

void MainWindow::on_radioButton_4_toggled()
{

    QDateTime current = QDateTime::currentDateTime();
    QString time = current.toString("yyyy-MM-dd hh:mm:ss");

        if(ui.radioButton_4->isChecked())
        {
        qnode_2.test(6);
        myfile <<time.toStdString()<<": User User chose odom topic\n"<<endl;
        }
        else
        qnode_2.test(7);
qnode_2.init();
}

/*****************************************************************************
** Implemenation [Slots][manually connected]
*****************************************************************************/

/**
 * This function is signalled by the underlying model. When the model changes,
 * this will drop the cursor down to the last line in the QListview to ensure
 * the user can always see the latest log message.
 */
void MainWindow::updateLoggingView() {
        ui.view_logging->scrollToBottom();
}
void MainWindow::updateLoggingView2() {
        ui.view_logging_2->scrollToBottom();
}

void MainWindow::updateLoggingView3() {
        ui.view_logging_3->scrollToBottom();
}

/*****************************************************************************
** Implementation [Menu]
*****************************************************************************/

void MainWindow::on_actionAbout_triggered() {
    QMessageBox::about(this, tr("About ..."),tr("<h2>PACKAGE_NAME Test Program 0.10</h2><p>Copyright Yujin Robot</p><p>This package needs an about description.</p>"));
}

/*****************************************************************************
** Implementation [Configuration]
*****************************************************************************/


void MainWindow::closeEvent(QCloseEvent *event)
{
   // WriteSettings();
    QMainWindow::closeEvent(event);
}

void Manual_Control::MainWindow::updatePixmap(const QPixmap* image)
{
    ui.lbimage->setPixmap(*image);

}


}  // namespace Manual_Control
