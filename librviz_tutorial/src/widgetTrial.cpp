//#include <QLabel>
#include <QGraphicsProxyWidget>
#include "myviz.h"
#include "widgetTrial.h"
#include <QLabel>
#include <QWidget>
#include "rviz/visualization_manager.h"
#include "rviz/render_panel.h"
#include "rviz/display.h"
#include <QVBoxLayout>
#include <QSlider>
#include <QGridLayout>
#include <QtOpenGL/QGLWidget>
#include <QGraphicsScene>
WidgetTrial::WidgetTrial(QDeclarativeItem *parent) :
    QDeclarativeItem(parent)
{
      qDebug()<<"1.2"<<endl;
      viz = new MyViz();

      viz->render_panel_->initialize( viz->manager_->getSceneManager(), viz->manager_ );
      viz->manager_->initialize();
      viz->manager_->startUpdate();
     qDebug()<<"3"<<endl;
      // Create a Grid display.
        viz->grid_ = viz->manager_->createDisplay( "rviz/Grid", "adjustable grid", true );
        ROS_ASSERT( viz->grid_ != NULL );

    // Configure the GridDisplay the way we like it.
      viz->grid_->subProp( "Line Style" )->setValue( "Billboards" );
      viz->grid_->subProp( "Color" )->setValue( Qt::green );

      viz->main_layout->addWidget(  viz->render_panel_ );
       viz->setLayout( viz->main_layout);

      qDebug()<<"1.222"<<endl;

      //QGraphicsScene scene;
      //scene.addWidget(viz);
      mProxy = new QGraphicsProxyWidget(this);
      mProxy->setWidget(viz);
 //     mProxy = scene.addWidget(viz);
      qDebug()<<"1.3"<<endl;
      qDebug()<<"1.4"<<endl;
      //showing();
     // viz->create(0,true,true);
      //viz->connect()
      //viz->setFocusProxy(mProxy);
      //mProxy->update();

   viz->show();
    //  QWidget h = new QWidget();


}

WidgetTrial::~WidgetTrial()
{
    delete viz;
}

//void WidgetTrial::showRviz(const QString &rvizName)
//{
//    viz->show();
//}

//QString WidgetTrial::rviz() const
//{
//}

//QString QmlLabel::text() const
//{
//    return viz->text();
//}

void WidgetTrial::showing()
{

    qDebug()<<"1.5"<<endl;
    viz->show();
    qDebug()<<"1.5555"<<endl;


        }



