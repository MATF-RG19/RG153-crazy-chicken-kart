cmake_minimum_required(VERSION 3.16)

project(crazyChickenKart)
add_executable(crazyChickenKart crazyChickenKart.cpp DrawFunctions.cpp DrawFunctions.hpp  Textures/image.cpp Textures/image.hpp) 

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )
target_link_libraries(crazyChickenKart ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )