#include <iostream>
#include <vector>
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// シェーダーのコンパイルログ
GLboolean printShaderInfoLog(GLuint shader, const char *str){
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) std::cerr << "Compile error in " << str << std::endl;

    GLsizei bufsize;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &bufsize);
    if (bufsize > 1){
        std::vector<GLchar> infoLog(bufsize);
        GLsizei length;
        glGetShaderInfoLog(shader, bufsize, &length, &infoLog[0]);
        std::cerr << &infoLog[0] << std::endl;
    }

    return static_cast<GLboolean>(status);
}

//プログラムオブジェクトのリンク結果
GLboolean printProgramInfoLog(GLint program){
    GLint status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) std::cerr << "Link error." << std::endl;

    GLsizei bufSize;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufSize);

    if (bufSize > 1){
        std::vector<GLchar> infoLog(bufSize);
        GLsizei length;
        glGetProgramInfoLog(program, bufSize, &length, &infoLog[0]);
        std::cerr << &infoLog[0] << std::endl;
    }

    return static_cast<GLboolean>(status);
}

//プログラムオブジェクトの作成
GLuint createProgram(const char *vsrc, const char *fsrc){
    const GLuint program(glCreateProgram()); // ShaderのGPU処理指定
    if (vsrc != nullptr){
        // Vertex Shader オブジェクト作成
        const GLuint vobj(glCreateShader(GL_VERTEX_SHADER));
        glShaderSource(vobj, 1, &vsrc, nullptr);
        glCompileShader(vobj);

        // Vertex Shader オブジェクトをプログラムに組み込む
        if (printShaderInfoLog(vobj, "vertex shader")) glAttachShader(program, vobj);
        glDeleteShader(vobj);
    }

    if (fsrc != nullptr){
        // Fragment Shader オブジェクト作成
        const GLuint fobj(glCreateShader(GL_FRAGMENT_SHADER));
        glShaderSource(fobj, 1, &fsrc, nullptr);
        glCompileShader(fobj);

        // Fragment Shader オブジェクトをプログラムに組み込む
        if (printShaderInfoLog(fobj, "fragment shader")) glAttachShader(program, fobj);
        glDeleteShader(fobj);
    }

    //プログラムオブジェクトをリンク
    glBindAttribLocation(program, 0, "position");
    glBindFragDataLocation(program, 0, "fragment");
    glLinkProgram(program);

    if (printProgramInfoLog(program)) return program;

    glDeleteProgram(program);
    return 0;
}

bool readShaderSource(const char *name, std::vector<GLchar> &buffer){
    if (name == nullptr) return false;

    std::ifstream file(name, std::ios::binary);
    if (file.fail()){
        std::cerr << "Error: Can not open source file: " << name << std::endl;
        return false;
    }

    file.seekg(0L, std::ios::end);
    GLsizei length = static_cast<GLsizei>(file.tellg());

    buffer.resize(length + 1);

    file.seekg(0L, std::ios::beg);
    file.read(buffer.data(), length);
    buffer[length] = '\0';

    if (file.fail()){
        std::cerr << "Error: Could not read source file: " << name << std::endl;
        file.close();
        return false;
    }

    file.close();
    return true;
}

GLuint loadProgram(const char *vert, const char *frag){
    std::vector<GLchar> vsrc;
    const bool vstat(readShaderSource(vert, vsrc));
    std::vector<GLchar> fsrc;
    const bool fstat(readShaderSource(frag, fsrc));

    return vstat && fstat ? createProgram(vsrc.data(), fsrc.data()) : 0;
}

int main() {
    std::cout << "Hello, World!" << std::endl;

    // 初期化 失敗?
    if (glfwInit() == GL_FALSE){
        std::cerr << "Initialize GLFW error" << std::endl;
        return 1;
    }

    atexit(glfwTerminate); // プログラム終了時の処理登録

    // ウィンドウの事前設定
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //OpenGL version 3.x
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2); //OpenGL version x.2
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //前方互換使用
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //古い機能を使用しない

    // ウィンドウの作成
    GLFWwindow *const window(glfwCreateWindow(640, 480, "OpenGL_TEST", nullptr, nullptr));
    if (window == nullptr){
        std::cerr << "Window GLFW error" << std::endl;
        return 1;
    }

    glfwMakeContextCurrent(window); //ウィンドウのOpenGL処理対象指定

    // GLEW 有効化・初期化
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK){
        std::cerr << "Initialize GLEW error" << std::endl;
        return 1;
    }

    glfwSwapInterval(1); //垂直同期の待機

    glClearColor(0.1f, 0.1f, 0.1f, 0.f); // 背景色

    const GLuint program(loadProgram("Shader/point.vert", "Shader/point.frag"));

    // ウィンドウフレーム描画処理
    while (glfwWindowShouldClose(window) == GL_FALSE){
        glClear(GL_COLOR_BUFFER_BIT); //ウィンドウのクリア
        glUseProgram(program);

        /* ------------- 描画処理 -------------*/

        glfwSwapBuffers(window); // カラーバッファの入れ替え
        glfwWaitEvents(); //イベントの取り出し
    }
    return 0;
}
