## BEGIN_TUTORIAL
## This CMakeLists.txt file for rviz_plugin_tutorials builds both the TeleopPanel tutorial and the ImuDisplay tutorial.
##
## First start with some standard catkin stuff.
cmake_minimum_required(VERSION 2.8.3)
project(librviz_tutorial)
#added qt_build
find_package(catkin REQUIRED COMPONENTS rviz qt_build roscpp)
catkin_package()
include_directories(${catkin_INCLUDE_DIRS})
link_directories(${catkin_LIBRARY_DIRS})

## This plugin includes Qt widgets, so we must include Qt like so:
find_package(Qt4 COMPONENTS QtCore QtGui REQUIRED)
include(${QT_USE_FILE})

## I prefer the Qt signals and slots to avoid defining "emit", "slots",
## etc because they can conflict with boost signals, so define QT_NO_KEYWORDS here.
add_definitions(-DQT_NO_KEYWORDS)

## Here we specify which header files need to be run through "moc",
## Qt's meta-object compiler.
qt4_wrap_cpp(MOC_FILES
  src/myviz.h
  src/widgetTrial.h
)

## Here we specify the list of source files, including the output of
## the previous command which is stored in ``${MOC_FILES}``.
set(SOURCE_FILES
  src/myviz.cpp
  src/main.cpp
  src/widgetTrial.cpp
  ${MOC_FILES}
)



install(DIRECTORY ./src

 DESTINATION ${CMAKE_INSTALL_PREFIX}/plugin

 FILES_MATCHING PATTERN "*.qml"

 PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)




## Add the "myviz" executable and specify the list of source files we
## collected above in ``${SOURCE_FILES}``.
add_executable(librviz_tutorial ${SOURCE_FILES})
#ADD_EXECUTABLE( widgetTrial ${SAMPLE_SRCS} ${SAMPLE_MOC_SRCS} ${SAMPLE_UI_HDRS} )
## Link the myviz executable with whatever Qt libraries have been defined by
## the ``find_package(Qt4 ...)`` line above, and with whatever libraries
## catkin has included.
message("------------------declerative ${QT_QTDECLARATIVE_LIBRARY}")
target_link_libraries(librviz_tutorial ${QT_LIBRARIES} ${catkin_LIBRARIES}
${QT_QTDECLARATIVE_LIBRARY} default_plugin ${catkin_LIBRARIES} ${KDE4_KIO_LIBRARY}
)



## END_TUTORIAL
