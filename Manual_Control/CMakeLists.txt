##############################################################################
# CMake
##############################################################################

cmake_minimum_required(VERSION 2.8.0)
project(Manual_Control)

##############################################################################
# Catkin
##############################################################################

# qt_build provides the qt cmake glue, roscpp the comms for a default talker
find_package(catkin REQUIRED COMPONENTS rviz qt_build roscpp image_transport cv_bridge)
include_directories(${catkin_INCLUDE_DIRS})
# Use this to define what the package will export (e.g. libs, headers).
# Since the default here is to produce only a binary, we don't worry about
# exporting anything. 
catkin_package()
add_definitions(-DQT_NO_KEYWORDS)
##############################################################################
# Qt Environment
##############################################################################

# this comes from qt_build's qt-ros.cmake which is automatically 
# included via the dependency call in package.xml
rosbuild_prepare_qt4(QtCore QtGui) # Add the appropriate components to the component list here

##############################################################################
# Sections
##############################################################################

file(GLOB QT_FORMS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ui/*.ui)
file(GLOB QT_RESOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} resources/*.qrc)
file(GLOB_RECURSE QT_MOC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS include/Manual_Control/*.hpp)

QT4_ADD_RESOURCES(QT_RESOURCES_CPP ${QT_RESOURCES})
QT4_WRAP_UI(QT_FORMS_HPP ${QT_FORMS})
QT4_WRAP_CPP(QT_MOC_HPP ${QT_MOC})



QT4_WRAP_CPP(QT_MOC_HPP
    include/Manual_Control/main_window.hpp
    include/Manual_Control/qnode.hpp
    include/Manual_Control/qnode2.hpp
    include/Manual_Control/myviz.h
    include/Manual_Control/qnode3.hpp
    include/Manual_Control/listener.hpp
${QT_MOC})

##############################################################################
# Sources
##############################################################################


set(SOURCE_FILES
  src/main.cpp
  src/main_window.cpp
  src/qnode.cpp
  src/qnode2.cpp
  src/myviz.cpp
  src/qnode3.cpp
  src/listener.cpp
  ${MOC_FILES}
)


file(GLOB_RECURSE QT_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS src/*.cpp)

##############################################################################
# Binaries
##############################################################################

add_executable(Manual_Control ${QT_SOURCES} ${QT_RESOURCES_CPP} ${QT_FORMS_HPP} ${QT_MOC_HPP})
target_link_libraries(Manual_Control ${QT_LIBRARIES} ${catkin_LIBRARIES})
install(TARGETS Manual_Control RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

