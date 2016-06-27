cmake_minimum_required(VERSION 3.5.0)
project(proj_padrao)

#Can manually add the sources using the set command as follows:
#set(SOURCES src/mainapp.cpp src/Student.cpp)

#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.cpp")

add_executable(mainOut ${SOURCES})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories(include ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_link_libraries(mainOut ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
