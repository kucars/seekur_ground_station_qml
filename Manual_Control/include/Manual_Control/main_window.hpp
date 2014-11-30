/**
 * @file /include/Manual_Control/main_window.hpp
 *
 * @brief Qt based gui for Manual_Control.
 *
 * @date November 2010
 **/
#ifndef Manual_Control_MAIN_WINDOW_H
#define Manual_Control_MAIN_WINDOW_H

/*****************************************************************************
** Includes
*****************************************************************************/
/*****************************************************************************
** Includes
*****************************************************************************/

#include <QtGui/QMainWindow>
#include "ui_main_window.h"
#include "qnode.hpp"
#include "qnode2.hpp"
#include "qnode3.hpp"
#include <string.h>
#include <fstream>
#include <ostream>
#include <iostream>
using namespace std;
/*****************************************************************************
** Namespace
*****************************************************************************/

namespace Manual_Control {

/*****************************************************************************
** Interface [MainWindow]
*****************************************************************************/
/**
 * @brief Qt central, all operations relating to the view part here.
 */
class MainWindow : public QMainWindow {
Q_OBJECT

public:
    ofstream myfile;

    MainWindow(int argc, char** argv, QNode3 *node, QWidget *parent = 0);
    ~MainWindow();

    QNode qnode;
    qnode2 qnode_2;
    QNode3 *qnode_3;


    void closeEvent(QCloseEvent *event); // Overloaded function
    void showNoMasterMessage();
   void keyPressEvent(QKeyEvent *e);


public Q_SLOTS:
   void radioButton_setjoint();
   void radioButton_2_setjoint();
   void radioButton_3_setjoint();
   void radioButton_4_setjoint();
   void radioButton_5_setjoint();
   void setGripper();
   void setGrasp();
   void on_radioButton_toggled();
   void on_radioButton_2_toggled();
   void on_radioButton_3_toggled();
   void on_radioButton_4_toggled();

    /******************************************
    ** Auto-connections (connectSlotsByName())
    *******************************************/
    void on_actionAbout_triggered();
    void on_button_connect_clicked(bool check );
    //void on_radioButton_2_toggled();
    //void on_radioButton_toggled();

    void on_checkBox_2_toggled();
    void on_checkBox_toggled();


   // void on_button_connect_clicked(bool check );
    //void on_checkbox_use_environment_stateChanged(int state);
    //void on_quit_button_clicked();
   // void on_button_clicked(bool check );


   /* void on_joint_one_clicked();
    void on_joint_two_clicked();
    void on_joint_three_clicked();
    void on_joint_four_clicked();
    void on_joint_five_clicked();*/


    //void on_radiobutton_radiobutton_stateChanged(int state);


    /******************************************
    ** Manual connections
    *******************************************/
    void updateLoggingView(); // no idea why this can't connect automatically
    void updateLoggingView2();
    void updateLoggingView3();
    void updatePixmap(const QPixmap* image);

private:
    Ui::MainWindowDesign ui;
};

}  // namespace Manual_Control

#endif // learningjoint_MAIN_WINDOW_H
