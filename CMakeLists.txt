cmake_minimum_required(VERSION 3.22)
project(GLFW)

set(CMAKE_CXX_STANDARD 14)

link_directories(F:/ProgramFiles/GLFW/lib-vc2022) #lib
include_directories(F:/ProgramFiles/GLFW/include/GLFW F:/ProgramFiles/GLFW/include/GL) #h

add_executable(GLFW main.cpp)
target_link_libraries(GLFW glfw3 glew32 opengl32.lib)
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^^^^^^^^^^^^ Windows saisho kara aru!!!!!!!