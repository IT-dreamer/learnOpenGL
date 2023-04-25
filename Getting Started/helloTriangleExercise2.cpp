#include "../common/Utils.h"

#define _WINDOWS_WIDTH_ 800
#define _WINDOWS_HEIGHT_ 600

#define _VAO_NUM_ 1
#define _VBO_NUM_ 2

int main(void)
{
    //initial OpenGL
    auto windows = openglInit(_WINDOWS_WIDTH_, _WINDOWS_HEIGHT_, "hello triangle", nullptr, nullptr);
    if(windows == nullptr)
    {
        exit(EXIT_FAILURE);
    }

    //load the shader file
    auto shaderProgram = creatShaderProgram("../shader/helloTriangleExercise1.vert", "../shader/helloTriangleExercise1.frag");
    
    glfwSwapInterval(1);

    //set VAO and VBO
    float triangleA[] = 
    {
        1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.0f
    };

    float triangleB[] = 
    {
        -1.0f, -0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.0f
    };

    //initial vao and vbo
    GLuint vao[2], vbo[2];
    glGenVertexArrays(2, vao);
    glGenBuffers(2, vbo);

    //Triangle A
    glBindVertexArray(vao[0]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleA), triangleA, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    //Triangle B
    glBindVertexArray(vao[1]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleB), triangleB, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    //render loop
    while(!glfwWindowShouldClose(windows))
    {
        //set the background color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //set which shader program used
        glUseProgram(shaderProgram);

        //render Triangle A
        glBindVertexArray(vao[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        //render Triangle B
        glBindVertexArray(vao[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);        

        //swap buffer
        glfwSwapBuffers(windows);

        //update window's status
        glfwPollEvents();
    }

    glfwDestroyWindow(windows);
    glfwTerminate();

    return 0;
}