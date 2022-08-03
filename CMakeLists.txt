cmake_minimum_required(VERSION 3.22)
project(GLFW)

set(CMAKE_CXX_STANDARD 14)

link_directories(F:/ProgramFiles/GLFW/lib-vc2022 F:/ProgramFiles/GLFW/GLEW) #lib
include_directories(F:/ProgramFiles/GLFW/include) #h
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /execution-charset:SHIFT_JIS /source-charset:UTF-8") #JP

add_executable(GLFW main.cpp)

# GLEW GLFW dll copy
file(GLOB dlls F:/ProgramFiles/GLFW/lib-vc2022/glfw3.dll F:/ProgramFiles/GLFW/GLEW/glew32.dll)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${dlls} $<TARGET_FILE_DIR:${PROJECT_NAME}>)

# Shader copy
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E make_directory ${shader} $<TARGET_FILE_DIR:${PROJECT_NAME}>/Shader)
file(GLOB shader
        Shader/*.frag
        Shader/*.vert)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${shader} $<TARGET_FILE_DIR:${PROJECT_NAME}>/Shader/)

target_link_libraries(GLFW glew32 glfw3 opengl32.lib)
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^^^^^^^^^^^^ Windows saisho kara aru!!!!!!!