/**
 * @file /src/main.cpp
 *
 * @brief Qt based gui.
 *
 * @date November 2010
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include <QtGui>
#include <QApplication>
#include "../include/Manual_Control/main_window.hpp"
#include"../include/Manual_Control/myviz.h"
#include "../include/Manual_Control/listener.hpp"


/*****************************************************************************
** Main
*****************************************************************************/

int main(int argc, char **argv) {

    /*********************
    ** Qt
    **********************/
    QApplication app(argc, argv);
    Listener listener(argc,argv);
    Manual_Control::MainWindow w(argc,argv,&listener);
    w.show();
    app.connect(&app, SIGNAL(lastWindowClosed()), &app, SLOT(quit()));
    QObject::connect(&listener,SIGNAL(Update_Image(const QPixmap*)),&w,SLOT(updatePixmap(const QPixmap*)));//+

    int result = app.exec();
    return result;
}
