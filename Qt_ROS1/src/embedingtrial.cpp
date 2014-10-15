//#include <QLabel>
#include <QGraphicsProxyWidget>
#include <QLabel>
#include <QWidget>
#include <QVBoxLayout>
#include <QSlider>
#include <QGridLayout>
#include "embedingtrial.h"
#include "listener.hpp"
#include "main_window.hpp"
#include <QtDeclarative/QDeclarativeView>


class MainWindow;
EmbedingTrial::EmbedingTrial(QDeclarativeItem *parent)
    :QDeclarativeItem(parent)
{
    Listener m(a,c);
    win = new MainWindow(&m);
    mProxy = new QGraphicsProxyWidget(this);
    mProxy->setWidget(win);
    win->show();
}

EmbedingTrial::~EmbedingTrial()
{
    delete win;
}

int EmbedingTrial::a=0;
char** EmbedingTrial::c;




