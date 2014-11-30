#ifndef MYVIZ_H
#define MYVIZ_H

#include <QWidget>
#include <QPushButton>
#include "QVBoxLayout"
namespace rviz
{
class Display;
class RenderPanel;
class VisualizationManager;
class VisualizationPanel;
class ToolManager;
class Tool;
}

// BEGIN_TUTORIAL
// Class "MyViz" implements the top level widget for this example.
class MyViz: public QWidget
{
Q_OBJECT
public:
  MyViz( int argc, char** argv,QWidget* parent = 0);
  virtual ~MyViz();

  QVBoxLayout* main_layout;
  QPushButton* select ;
  QPushButton* navGoal ;
  QPushButton* poseEstimate ;
  QPushButton* interact ;
  QPushButton* publishPoint ;


private Q_SLOTS:
  void setThickness( int thickness_percent );
  void setCellSize( int cell_size_percent );
  void onClickNavGoal();
  void onClickSelect();
  void onClickPoseEstimate();
  void onClickInteract();
  void onClickPublishPoint();


private:
  rviz::VisualizationManager* manager_;
  rviz::RenderPanel* render_panel_;
  rviz::Display* grid_;
  rviz::Display* robotModel_;
  rviz::Display* poseAraay_;
  rviz::Display* tF_;
  rviz::Display* laserScan_;
  rviz::Display* map1_;
  rviz::Display* polygon_;
  rviz::Display* path1_;
  rviz::Display* path2_;
  rviz::Display* marker_;
  rviz::Display* map2_;
  rviz::Display* map3_;
  rviz::Display* pointCloud_;
  rviz::ToolManager* allTools_;
};
// END_TUTORIAL
#endif // MYVIZ_H
