/**
 * @file /qlistener/main.cpp
 *
 * @brief Qt based gui.
 *
 * @date November 2010
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include <QtGui>
#include <QDebug>
#include <QApplication>
#include "main_window.hpp"
#include "listener.hpp"
#include "embedingtrial.h"
#include <QtDeclarative/QDeclarativeView>
#include "QtDeclarative/QDeclarativeItem"
#include <QtDeclarative/QtDeclarative>
/*****************************************************************************
** Main
*****************************************************************************/
 int a;
 char** c;

int main(int argc, char **argv) {

    /*********************
    ** Qt
    **********************/

    QApplication app(argc, argv);
    Listener listener(argc,argv);

EmbedingTrial::a=argc;
EmbedingTrial::c=argv;
EmbedingTrial emb();

    MainWindow w(&listener);
    w.show();
    QObject::connect(&listener,SIGNAL(Update_Image(const QPixmap*)),&w,SLOT(updatePixmap(const QPixmap*)));
    app.connect(&app, SIGNAL(lastWindowClosed()), &app, SLOT(quit()));    

    qmlRegisterType<EmbedingTrial>("emb",1,0,"EmbedingTrial");
    QDeclarativeView *view = new QDeclarativeView();
    view->setSource(QUrl("/home/viki/catkin_ws/src/Qt_ROS1/cameraui/cameraui.qml"));
    view->show();


    int result = app.exec();

	return result;
}
