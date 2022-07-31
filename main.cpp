#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main() {
    std::cout << "Hello, World!" << std::endl;

    // 初期化 失敗?
    if (glfwInit() == GL_FALSE){
        std::cerr << "Initialize GLFW error" << std::endl;
        return 1;
    }

    atexit(glfwTerminate); // プログラム終了時の処理登録

    // ウィンドウの作成
    GLFWwindow *const window(glfwCreateWindow(640, 480, "TEST", nullptr, nullptr));
    if (window == nullptr){
        std::cerr << "Window GLFW error" << std::endl;
        return 1;
    }

    glfwMakeContextCurrent(window); //ウィンドウのOpenGL処理対称指定

    // GLEW 有効化・初期化
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK){
        std::cerr << "Initialize GLEW error" << std::endl;
        return 1;
    }

    glClearColor(0.1f, 0.1f, 0.1f, 0.f);

    // ウィンドウフレーム描画処理
    while (glfwWindowShouldClose(window) == GL_FALSE){
        glClear(GL_COLOR_BUFFER_BIT); //ウィンドウのクリア

        /* ------------- 描画処理 -------------*/

        glfwSwapBuffers(window); // カラーバッファの入れ替え
        glfwWaitEvents(); //イベントの取り出し
    }
    return 0;
}
