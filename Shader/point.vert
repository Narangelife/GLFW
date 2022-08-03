#version 150 core

// Attribute変数の宣言
in vec4 position; // 入力(in): CPUからの図形データのうち1頂点情報が格納

void main(){
    gl_Position = position;
}