#include "../common/Utils.h"

#define _WINDOWS_WIDTH 800
#define _WINDOWS_HEIGHT 600

int main(void)
{
    //initial OpenGL
    auto windows = openglInit(_WINDOWS_WIDTH, _WINDOWS_HEIGHT, "hello triangle", nullptr, nullptr);
    if(windows == nullptr)
    {
        exit(EXIT_FAILURE);
    }

    //load the shader file
    auto shaderProgram = creatShaderProgram("../shader/helloTriangle.vert", "../shader/helloTriangle.frag");
    
    glfwSwapInterval(1);

    //set VAO and VBO
    float vertices[] = 
    {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };
    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
    //glBindBuffer(GL_ARRAY_BUFFER, 0); 
    //glBindVertexArray(0); 

    //render loop
    while(!glfwWindowShouldClose(windows))
    {
        //set the background color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //set which shader program used
        glUseProgram(shaderProgram);

        //set which VAO rendered
        glBindVertexArray(vao);

        //render
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