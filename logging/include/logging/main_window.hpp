/**
 * @file /include/logging/main_window.hpp
 *
 * @brief Qt based gui for logging.
 *
 * @date November 2010
 **/
#ifndef logging_MAIN_WINDOW_H
#define logging_MAIN_WINDOW_H

/*****************************************************************************
** Includes
*****************************************************************************/

#include <QtGui/QMainWindow>
#include "ui_main_window.h"
#include "qnode.hpp"
#include <fstream>
using namespace std;
/*****************************************************************************
** Namespace
*****************************************************************************/

namespace logging {

/*****************************************************************************
** Interface [MainWindow]
*****************************************************************************/
/**
 * @brief Qt central, all operations relating to the view part here.
 */
class MainWindow : public QMainWindow {
Q_OBJECT

public:
	MainWindow(int argc, char** argv, QWidget *parent = 0);
	~MainWindow();
    void updateui(const geometry_msgs::Twist::ConstPtr& top);
	void ReadSettings(); // Load up qt program settings at startup
    void WriteSettings(); // Save qt program settings when closing
	void closeEvent(QCloseEvent *event); // Overloaded function
    void showNoMasterMessage();
    ofstream myfile;

public Q_SLOTS:
	/******************************************
	** Auto-connections (connectSlotsByName())
	*******************************************/
	void on_actionAbout_triggered();
	void on_button_connect_clicked(bool check );
	void on_checkbox_use_environment_stateChanged(int state);
   // void on_checkBox_stateChanged(int state);
   // void on_checkBox_2_stateChanged(int state);
  // void on_pushButton_clicked(bool check );
   //void on_checkBox_5_stateChanged();
    //void on_checkBox_6_stateChanged();
    void on_radioButton_toggled();
    void on_radioButton_2_toggled();
    void on_radioButton_3_toggled();
    void on_radioButton_4_toggled();






    /******************************************
    ** Manual connections
    *******************************************/
    void updateLoggingView(); // no idea why this can't connect automatically

private:
	Ui::MainWindowDesign ui;
	QNode qnode;
};

}  // namespace logging

#endif // logging_MAIN_WINDOW_H
