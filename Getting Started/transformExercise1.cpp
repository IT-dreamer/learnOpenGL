#include "../common/Utils.h"
#include <SOIL2/SOIL2.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define _WINDOW_WIDTH_      600
#define _WINDOW_HEIGHT_     600

int main(void)
{
    //init opengl and create window
    auto window = openglInit(_WINDOW_WIDTH_, _WINDOW_HEIGHT_, "shader", nullptr, nullptr);

    //set the render program
    auto program = creatShaderProgram("../shader/transform.vert", "../shader/transform.frag");

    //data
    float vertices[] = {
    //---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
    };

    unsigned int indices[] = {
    0, 1, 3, // triangleA
    1, 2, 3  // triangleB
    };

    //set the vao vbo and ebo
    GLuint vao, vbo, ebo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    //bind the vbo to vao
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //bind the ebo to vao
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //set the Attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    //generate texture1 object
    GLuint texture1;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);

    //Set the surround and filter methods for the currently bound texture object
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //load target texture 
    const char *texture1_path = "../texture/container.jpg";
    int texture1_width, texture1_height;
    auto image1 = SOIL_load_image(texture1_path, &texture1_width, &texture1_height, 0, SOIL_LOAD_RGB);

    if(image1)
    {
        //bind the target texture to object
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture1_width, texture1_height, 0, GL_RGB, GL_UNSIGNED_BYTE, image1);
        glGenerateMipmap(GL_TEXTURE_2D);

        //unbind current texture
        SOIL_free_image_data(image1);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    else
    {
        std::cerr << "Failed to load texture: " << texture1_path;
        std::cerr << std::endl; 
    }

    //generate texture2 object
    GLuint texture2;
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);

    //Set the surround and filter methods for the currently bound texture object
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //load target texture
    const char *texture2_path = "../texture/awesomeface.png";
    int texture2_width, texture2_height;
    auto image2 = SOIL_load_image(texture2_path, &texture2_width, &texture2_height, 0, SOIL_LOAD_RGB);

    if(image2)
    {
        //bind the target texture to object
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture2_width, texture2_height, 0, GL_RGB, GL_UNSIGNED_BYTE, image2);
        glGenerateMipmap(GL_TEXTURE_2D);

        //unbind current texture
        SOIL_free_image_data(image2);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    else
    {
        std::cerr << "Failed to load texture: " << texture2_path;
        std::cerr << std::endl; 
    }

    //unbind the vao
    glBindVertexArray(0);
    
    //rend loop
    while(!glfwWindowShouldClose(window))
    {
        //set the background color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //set which shader program used
        glUseProgram(program);

        //set texture1
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glUniform1i(glGetUniformLocation(program, "texture1"), 0);

        //set texture2
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        glUniform1i(glGetUniformLocation(program, "texture2"), 1);

        //set transform matrix
        glm::mat4 trans(1.0f);
        trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

        //set uniform
        GLuint transformLoc = glGetUniformLocation(program, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

        //set which vao rendered
        glBindVertexArray(vao);

        //render
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        //set transform matrix
        glm::mat4 trans1(1.0f);
        trans1 = glm::translate(trans1, glm::vec3(-0.5f, 0.5f, 0.0f));
        trans1 = glm::scale(trans1, glm::vec3(sin((float)glfwGetTime()), sin((float)glfwGetTime()), 0));

        //set uniform
        GLuint transformLoc1 = glGetUniformLocation(program, "transform");
        glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(trans1));

        //render
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        //swap buffer
        glfwSwapBuffers(window);

        //update window's status
        glfwPollEvents();        
    }

    glfwDestroyWindow(window);
    glDeleteBuffers(1, &ebo);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &vao);
    glfwTerminate();
    return 0;
}