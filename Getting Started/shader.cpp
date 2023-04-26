#include "../common/Utils.h"
#include <cmath>

#define _WINDOW_WIDTH_      600
#define _WINDOW_HEIGHT_     600

using std::sin;

int main(void)
{
    //init opengl and create window
    auto window = openglInit(_WINDOW_WIDTH_, _WINDOW_HEIGHT_, "shader", nullptr, nullptr);

    //set the render program
    auto program = creatShaderProgram("../shader/shader.vert", "../shader/shader.frag");

    //data
    float vertices[] = {
    0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
    0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f
    };

    //factor
    float timeValue, factor;

    //set the vao and vbo
    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    //bind the vbo to vao
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //set the Attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //render loop
    while(!glfwWindowShouldClose(window))
    {
        //set the background color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //set which shader program used
        glUseProgram(program);

        //set the Uniform Variable
        timeValue = (float)glfwGetTime();
        factor = (sin(timeValue) / 2.0f) + 0.8f;
        auto u_factor = glGetUniformLocation(program, "factor");
        glUniform1f(u_factor, factor);

        //render
        glDrawArrays(GL_TRIANGLES, 0, 3);

        //swap buffer
        glfwSwapBuffers(window);

        //update window's status
        glfwPollEvents();        
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}