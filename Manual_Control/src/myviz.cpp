#include "../include/Manual_Control/myviz.h"
#include <QSlider>
#include <QLabel>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QDebug>
#include <QPushButton>
#include "rviz/visualization_manager.h"
#include "rviz/render_panel.h"
#include "rviz/display.h"
#include "rviz/tool_manager.h"
#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
#include <geometry_msgs/PoseStamped.h>
#include <tf/transform_listener.h>
#include <ros/network.h>
#include <string>
#include <std_msgs/String.h>
#include <sstream>
#include <sensor_msgs/Joy.h>
#include <string.h>
#include "rviz/display_context.h"
#include "rviz/properties/string_property.h"
#include "rviz/properties/property.h"
#include "rviz/default_plugin/tools/goal_tool.h"
#include "rviz/default_plugin/tools/point_tool.h"

// BEGIN_TUTORIAL
// Constructor for MyViz.  This does most of the work of the class.
MyViz::MyViz(int argc, char** argv, QWidget* parent )
 // : QWidget( parent )
{


    if( !ros::isInitialized() )
    {
      ros::init( argc, argv, "myviz", ros::init_options::AnonymousName );
    }

  // Construct and lay out labels and slider controls.
  QLabel* thickness_label = new QLabel( "Line Thickness" );
  QSlider* thickness_slider = new QSlider( Qt::Horizontal );
  thickness_slider->setMinimum( 1 );
  thickness_slider->setMaximum( 100 );
  QLabel* cell_size_label = new QLabel( "Cell Size" );
  QSlider* cell_size_slider = new QSlider( Qt::Horizontal );
  cell_size_slider->setMinimum( 1 );
  cell_size_slider->setMaximum( 100 );
  QGridLayout* controls_layout = new QGridLayout();
  controls_layout->addWidget( thickness_label, 0, 0 );
  controls_layout->addWidget( thickness_slider, 0, 1 );
  controls_layout->addWidget( cell_size_label, 1, 0 );
  controls_layout->addWidget( cell_size_slider, 1, 1 );



  select = new QPushButton( "Select" );
  navGoal = new QPushButton( "2D Nav Goal" );
  poseEstimate = new QPushButton( "2D Pose Estimate" );
  //moveCamera = new QPushButton( "Move Camera" );
  interact = new QPushButton( "Interact" );
  publishPoint = new QPushButton("Publish Point" );

  // Construct and lay out render panel.
  render_panel_ = new rviz::RenderPanel();
   main_layout = new QVBoxLayout;
  main_layout->addLayout( controls_layout );
 // main_layout->addWidget(moveCamera);
  main_layout->addWidget(interact);
  main_layout->addWidget(select);
  main_layout->addWidget(navGoal);
  main_layout->addWidget(poseEstimate);
  main_layout->addWidget(publishPoint);
  main_layout->addWidget( render_panel_ );

  // Set the top-level layout for this MyViz widget.
  setLayout( main_layout );

  // Make signal/slot connections.
  connect( thickness_slider, SIGNAL( valueChanged( int )), this, SLOT( setThickness( int )));
  connect( cell_size_slider, SIGNAL( valueChanged( int )), this, SLOT( setCellSize( int )));
  connect( select, SIGNAL(clicked()), this, SLOT( onClickSelect()));
  connect( navGoal, SIGNAL(clicked()), this, SLOT( onClickNavGoal()));
  connect( poseEstimate, SIGNAL(clicked()), this, SLOT( onClickPoseEstimate()));
  //connect( moveCamera, SIGNAL(clicked()), this, SLOT( onClickMoveCamera()));
  connect( interact, SIGNAL(clicked()), this, SLOT( onClickInteract()));
  connect( publishPoint, SIGNAL(clicked()), this, SLOT( onClickPublishPoint()));

  // Next we initialize the main RViz classes.
  //
  // The VisualizationManager is the container for Display objects,
  // holds the main Ogre scene, holds the ViewController, etc.  It is
  // very central and we will probably need one in every usage of
  // librviz.
  manager_ = new rviz::VisualizationManager( render_panel_ );
  render_panel_->initialize( manager_->getSceneManager(), manager_ );
  manager_->initialize();
  manager_->startUpdate();
  // Create a Grid display.

manager_->setFixedFrame("map");

robotModel_ = manager_->createDisplay( "rviz/RobotModel", "robot model", true );
grid_       = manager_->createDisplay( "rviz/Grid", "grid", true );
poseAraay_  = manager_->createDisplay( "rviz/PoseArray", "pose array", true );
tF_         = manager_->createDisplay( "rviz/TF","TF", true );
laserScan_  = manager_->createDisplay( "rviz/LaserScan","Laser", true );
map1_       = manager_->createDisplay( "rviz/Map","Map1", true );
polygon_    = manager_->createDisplay( "rviz/Polygon","Polygon", true );
path1_      = manager_->createDisplay( "rviz/Path","Path1", true );
path2_      = manager_->createDisplay( "rviz/Path","Path2", true );
marker_     = manager_->createDisplay( "rviz/Marker","Marker", true );
map2_       = manager_->createDisplay( "rviz/Map","Map2", true );
//map3_       = manager_->createDisplay( "rviz/Map","Map3", true );
pointCloud_ = manager_->createDisplay( "rviz/PointCloud2","PointCloud", true );

ROS_ASSERT( grid_ != NULL );


  // Configure the GridDisplay the way we like it.
  grid_->subProp( "Line Style" )->setValue( "Billboards" );
  grid_->subProp( "Color" )->setValue( Qt::gray );

  poseAraay_->subProp( "Topic" )->setValue("/particlecloud");
  poseAraay_->subProp( "Color" )->setValue(Qt::red);
  poseAraay_->subProp( "Arrow Length" )->setValue(0.3);

  tF_->subProp( "Show Names" )->setValue(true);
  tF_->subProp( "Show Axes" )->setValue(true);
  tF_->subProp( "Show Arrows" )->setValue(true);manager_->setFixedFrame("map");

  tF_->subProp( "Marker Scale" )->setValue(1);
  tF_->subProp( "Frame Timeout" )->setValue(15);

  laserScan_->subProp( "Topic" )->setValue("/scan");

  map1_->subProp( "Topic" )->setValue("/map");
  map1_->subProp( "Alpha" )->setValue(0.7);
  map1_->subProp( "Color Scheme" )->setValue("map");
  map1_->subProp( "Position" )->setValue("0; 0; 0");
  map1_->subProp( "Orientation" )->setValue("0; 0; 0; 1");


  polygon_->subProp( "Topic" )->setValue("/move_base/local_costmap/obstacle_layer_footprint/footprint_stamped");
  polygon_->subProp("Color")->setValue(Qt::green);
  polygon_->subProp("Alpha")->setValue(1);

  path1_->subProp( "Topic" )->setValue("/move_base/TrajectoryPlannerROS/global_plan");
  path1_->subProp("Color")->setValue(Qt::black);
  path1_->subProp("Alpha")->setValue(1);
  path1_->subProp("Buffer Length")->setValue(1);

  path2_->subProp( "Topic" )->setValue("/move_base/NavfnROS/plan");
  path2_->subProp("Color")->setValue(Qt::yellow);
  path2_->subProp("Alpha")->setValue(1);
  path2_->subProp("Buffer Length")->setValue(1);

  marker_->subProp( "Marker Topic" )->setValue("/exploration_polygon_marker");
  //marker_->subProp("Topic")->subProp("Color")->setValue(Qt::blue);
  //marker_->subProp( "Color" )->setValue(Qt::green);

  map2_->subProp( "Topic" )->setValue("/explore_server/explore_costmap/costmap");

  //map3_->subProp( "Topic" )->setValue("/explore_server/explore_costmap/costmap");//costmap for navigation stack

  pointCloud_->subProp( "Topic" )->setValue("/camera/depth_registered/points");

  //camera
 // grid2_->subProp( "Image Topic" )->setValue("/camera/rgb/image_raw");

  // Initialize the slider values.
  thickness_slider->setValue( 25 );
  cell_size_slider->setValue( 10 );
}

// Destructor.
MyViz::~MyViz()
{
  delete manager_;
}

// This function is a Qt slot connected to a QSlider's valueChanged()
// signal.  It sets the line thickness of the grid by changing the
// grid's "Line Width" property.
void MyViz::setThickness( int thickness_percent )
{
  if( grid_ != NULL )
  {
    grid_->subProp( "Line Style" )->subProp( "Line Width" )->setValue( thickness_percent / 100.0f );
  }
}

// This function is a Qt slot connected to a QSlider's valueChanged()
// signal.  It sets the cell size of the grid by changing the grid's
// "Cell Size" Property.
void MyViz::setCellSize( int cell_size_percent )
{
  if( grid_ != NULL )
  {
    grid_->subProp( "Cell Size" )->setValue( cell_size_percent / 10.0f );
  }
}


//void MyViz::setIcons()
//{
//    allTools_ = manager_->getToolManager();
//    navGoal->setIcon(allTools_->getTool(3)->getIcon());

//}

void MyViz::onClickNavGoal()
{
  if( grid_ != NULL )
  {
      allTools_ = manager_->getToolManager();

      for(int i=0; i<allTools_->numTools(); i++)
      {
          if(allTools_->getTool(i)->getName() == "2D Nav Goal")
          {
              allTools_->getTool(i)->getPropertyContainer()->subProp("Topic")->setValue("/move_base_simple/goal");
              allTools_->setCurrentTool(allTools_->getTool(i));
              navGoal->setIcon(allTools_->getTool(i)->getIcon());
          }
      }

}

}
  void MyViz::onClickPoseEstimate()
  {
      if( grid_ != NULL )
      {
          allTools_ = manager_->getToolManager();


        for(int i=0; i<allTools_->numTools(); i++)
        {
            if(allTools_->getTool(i)->getName() == "2D Pose Estimate")
            {
                allTools_->setCurrentTool(allTools_->getTool(i));
                poseEstimate->setIcon(allTools_->getTool(i)->getIcon());
            }
        }
      }
  }
    void MyViz::onClickSelect()
    {
        allTools_ = manager_->getToolManager();

          for(int i=0; i<allTools_->numTools(); i++)
          {
              if(allTools_->getTool(i)->getName() == "Select")
              {
                  allTools_->setCurrentTool(allTools_->getTool(i));
                  select->setIcon(allTools_->getTool(i)->getIcon());

              }
          }

    }



    void MyViz::onClickInteract()
    {
        allTools_ = manager_->getToolManager();

          for(int i=0; i<allTools_->numTools(); i++)
          {
              if(allTools_->getTool(i)->getName() == "Interact")
              {
                  allTools_->setCurrentTool(allTools_->getTool(i));
                  interact->setIcon(allTools_->getTool(i)->getIcon());

              }
          }

    }
    void MyViz::onClickPublishPoint()
    {
        allTools_ = manager_->getToolManager();
        allTools_->addTool("rviz/PublishPoint");

          for(int i=0; i<allTools_->numTools(); i++)
          {
              if(allTools_->getTool(i)->getName() == "Publish Point")
              {
                  allTools_->setCurrentTool(allTools_->getTool(i));
                  publishPoint->setIcon(allTools_->getTool(i)->getIcon());
                  qDebug()<<allTools_->getTool(i)->getPropertyContainer()->subProp("Topic")->getValue();
                  qDebug()<<allTools_->getTool(i)->getPropertyContainer()->subProp("Color")->getValue();

              }

          }

    }





