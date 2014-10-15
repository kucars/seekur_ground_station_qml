
#include <QtDeclarative/QDeclarativeItem>
//#include "myviz.h"
#include <QGraphicsProxyWidget>
#include <QWidget>
#include <QtOpenGL/QGLWidget>

class MyViz;
class WidgetTrial: public QDeclarativeItem
{
Q_OBJECT
//Q_PROPERTY(QString rviz READ rviz WRITE showRviz)
//Q_PROPERTY(READ showing)
public:
   // QWidget* viz;
//   MyViz* viz;
    explicit WidgetTrial(QDeclarativeItem *parent = 0);
    virtual ~WidgetTrial();

public Q_SLOTS:
   // void showRviz (const QString &rvizName);
   void showing();
   // QString rviz() const;
//    QString text() const;


private:
      MyViz* viz;

    QGraphicsProxyWidget* mProxy;

};
