#include <QtDeclarative/QDeclarativeItem>
#include <QGraphicsProxyWidget>
#include <QWidget>
#include "main_window.hpp"
#include "listener.hpp"

class MainWindow;
class EmbedingTrial: public QDeclarativeItem
{

Q_OBJECT
//Q_PROPERTY(QString rviz READ rviz WRITE showRviz)
//Q_PROPERTY(READ showing)

public:
    explicit EmbedingTrial(QDeclarativeItem *parent = 0);
    virtual ~EmbedingTrial();
    static int a;
    static char** c;
  //  Listener lis;
    MainWindow* win;
    QGraphicsProxyWidget* mProxy;

public Q_SLOTS:



};

//  int EmbedingTrial::a=0;
// char** EmbedingTrial::c;
// char** EmbedingTrial::c= new char*;
