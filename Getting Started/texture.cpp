#include "../common/Utils.h"
#include <SOIL2/SOIL2.h>

#define _WINDOW_WIDTH_      600
#define _WINDOW_HEIGHT_     600

int main(void)
{
    //init opengl and create window
    auto window = openglInit(_WINDOW_WIDTH_, _WINDOW_HEIGHT_, "shader", nullptr, nullptr);

    //set the render program
    auto program = creatShaderProgram("../shader/shader.vert", "../shader/shader.frag");

    //data
    float vertices[] = {
    //---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
    };



    return 0;
}