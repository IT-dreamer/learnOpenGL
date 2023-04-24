#ifndef CHECKTOOL_H_
#define CHECKTOOL_H_

#include <iostream>
#include <string>
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using std::string;

string readShaderSource(const char *filePath);
GLuint creatShaderProgram(const char *vertexFile, const char *fragmentFile);
GLFWwindow *openglInit(int window_width, int window_height, const char *window_name, GLFWmonitor *monitor, GLFWwindow *share);
void printShaderLog(GLuint shader);
void printProgramLog(int prog);
bool checkOpenGLError();

#endif