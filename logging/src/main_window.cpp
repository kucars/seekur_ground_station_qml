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
#include "../include/logging/main_window.hpp"
#include <QDebug>
/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace logging {

using namespace Qt;

/*****************************************************************************
** Implementation [MainWindow]
*****************************************************************************/

MainWindow::MainWindow(int argc, char** argv, QWidget *parent)
	: QMainWindow(parent)
	, qnode(argc,argv)
{
	ui.setupUi(this); // Calling this incidentally connects all ui's triggers to on_...() callbacks in this class.
    QObject::connect(ui.actionAbout_Qt, SIGNAL(triggered(bool)), qApp, SLOT(aboutQt())); // qApp is a global variable for the application

    ReadSettings();
	setWindowIcon(QIcon(":/images/icon.png"));
	ui.tab_manager->setCurrentIndex(0); // ensure the first tab is showing - qt-designer should have this already hardwired, but often loses it (settings?).
    QObject::connect(&qnode, SIGNAL(rosShutdown()), this, SLOT(close()));
	/*********************
	** Logging
	**********************/
	ui.view_logging->setModel(qnode.loggingModel());
    QObject::connect(&qnode, SIGNAL(loggingUpdated()), this, SLOT(updateLoggingView()));
    /*********************
    ** Auto Start
    **********************/
    if ( ui.checkbox_remember_settings->isChecked() ) {
        on_button_connect_clicked(true);
    }
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






void MainWindow::on_radioButton_toggled()
{
    QDateTime current = QDateTime::currentDateTime();
    QString time = current.toString("yyyy-MM-dd hh:mm:ss");




    qDebug()<<"radio 1 toggled\n";
        if(ui.radioButton->isChecked())
        {
            myfile <<time.toStdString()<<": User chose camera topic\n"<<endl;
            qnode.test(0);
        }

        else
            qnode.test(1);

qnode.init();
}


void MainWindow::on_radioButton_2_toggled()
{

    QDateTime current = QDateTime::currentDateTime();
    QString time = current.toString("yyyy-MM-dd hh:mm:ss");
        if(ui.radioButton_2->isChecked())
        {
            myfile <<time.toStdString()<<": User choose laser /scan topic\n"<<endl;
            qnode.test(2);
        }
        else
            qnode.test(3);

qnode.init();
}

void MainWindow::on_radioButton_3_toggled()
{
    QDateTime current = QDateTime::currentDateTime();
    QString time = current.toString("yyyy-MM-dd hh:mm:ss");

        if(ui.radioButton_3->isChecked())
        {
            myfile <<time.toStdString()<<": User choose velocity command topic\n"<<endl;
            qnode.test(4);
        }
        else
            qnode.test(5);
        qnode.init();

}

void MainWindow::on_radioButton_4_toggled()
{

    QDateTime current = QDateTime::currentDateTime();
    QString time = current.toString("yyyy-MM-dd hh:mm:ss");

        if(ui.radioButton_4->isChecked())
        {
        qnode.test(6);
        myfile <<time.toStdString()<<": User User chose odom topic\n"<<endl;
        }
        else
        qnode.test(7);
qnode.init();
}




void MainWindow::on_button_connect_clicked(bool check ) {

     QDateTime current = QDateTime::currentDateTime();
     QString time = current.toString("yyyy-MM-dd hh:mm:ss");


    myfile.open ("/home/kurisdp/catkin_ws/src/logging/src/logs.txt");
    myfile <<time.toStdString()<<": User clicked connect button"<<endl;
   // myfile.close();
    qnode.init();
}


void MainWindow::on_checkbox_use_environment_stateChanged(int state) {
	bool enabled;
	if ( state == 0 ) {
		enabled = true;
	} else {
		enabled = false;
	}
	ui.line_edit_master->setEnabled(enabled);
	ui.line_edit_host->setEnabled(enabled);
	//ui.line_edit_topic->setEnabled(enabled);
}



//void MainWindow::on_checkBox_stateChanged(int state)
//{
//    qDebug()<<"check box changed value 2"<<endl;

//    if ( ui.checkBox->isChecked() )
//    {
//        qDebug()<<"i am checked 3"<<endl;
//       // qnode.test(1);


//    }

//   else {
//        qnode.test(0);
//        }

//    qnode.init();

//}

//void MainWindow::on_checkBox_2_stateChanged(int state)
//{
//    qDebug()<<"check box changed value 2"<<endl;

//    if ( ui.checkBox_2->isChecked() )
//    {
//        qDebug()<<"i am checked 3"<<endl;
//        qnode.test(3);

//    }

//   else {
//        qnode.test(2);
//        }

//    qnode.init();

//}


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

/*****************************************************************************
** Implementation [Menu]
*****************************************************************************/

void MainWindow::on_actionAbout_triggered() {
    QMessageBox::about(this, tr("About ..."),tr("<h2>PACKAGE_NAME Test Program 0.10</h2><p>Copyright Yujin Robot</p><p>This package needs an about description.</p>"));
}

/*****************************************************************************
** Implementation [Configuration]
*****************************************************************************/

void MainWindow::ReadSettings() {
    QSettings settings("Qt-Ros Package", "logging");
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("windowState").toByteArray());
    QString master_url = settings.value("master_url",QString("http://192.168.1.2:11311/")).toString();
    QString host_url = settings.value("host_url", QString("192.168.1.3")).toString();
    //QString topic_name = settings.value("topic_name", QString("/chatter")).toString();
    ui.line_edit_master->setText(master_url);
    ui.line_edit_host->setText(host_url);
    //ui.line_edit_topic->setText(topic_name);
    bool remember = settings.value("remember_settings", false).toBool();
    ui.checkbox_remember_settings->setChecked(remember);
    bool checked = settings.value("use_environment_variables", false).toBool();
    ui.checkbox_use_environment->setChecked(checked);
    if ( checked ) {
    	ui.line_edit_master->setEnabled(false);
    	ui.line_edit_host->setEnabled(false);
    	//ui.line_edit_topic->setEnabled(false);

    }
}

void MainWindow::WriteSettings() {
    QSettings settings("Qt-Ros Package", "logging");
    settings.setValue("master_url",ui.line_edit_master->text());
    settings.setValue("host_url",ui.line_edit_host->text());
    //settings.setValue("topic_name",ui.line_edit_topic->text());
    settings.setValue("use_environment_variables",QVariant(ui.checkbox_use_environment->isChecked()));
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState());
    settings.setValue("remember_settings",QVariant(ui.checkbox_remember_settings->isChecked()));

}


void MainWindow::updateui(const geometry_msgs::Twist::ConstPtr& top)
{
 //ui.label_3
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    myfile.close();
	WriteSettings();
	QMainWindow::closeEvent(event);
}

}  // namespace logging

