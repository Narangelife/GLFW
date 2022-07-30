#include <iostream>
#include <glew.h>
#include <glfw3.h>

int main() {
    std::cout << "Hello, World!" << std::endl;

    if (glfwInit() == GL_FALSE){
        return 1;
    }

    GLFWwindow *const window(glfwCreateWindow(640, 480, "Taku", NULL, NULL));
    if (window == NULL){
        return 1;
    }
    glfwMakeContextCurrent(window);
    glClearColor(0.1f, 0.1f, 0.1f, 0.f);

    while (glfwWindowShouldClose(window) == GL_FALSE){
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwWaitEvents();
    }
    return 0;
}
