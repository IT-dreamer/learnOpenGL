#ifndef CHECKTOOL_H_
#define CHECKTOOL_H_

#include "camera.h"
#include "cursor.h"

#include <iostream>
#include <string>
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL2/SOIL2.h>

std::string readShaderSource(const char *filePath);
GLuint creatShaderProgram(const char *vertexFile, const char *fragmentFile);
GLFWwindow *openglInit(int window_width, int window_height, const char *window_name, GLFWmonitor *monitor, GLFWwindow *share);
void printShaderLog(GLuint shader);
void printProgramLog(int prog);
bool checkOpenGLError();
bool texture2DRGBBind(GLuint texture, const char *texture_path);


/// @brief change the camera view when keyboard has input
/// @param window current window
/// @param cam camera object
/// @param speed_factor the speed of camera move
bool keyboardCameraMove(GLFWwindow *window, AFei::Camera &cam, float speed_factor);

/// @brief change the camera view when keyboard has input
/// @param window current window
/// @param cam camera object
/// @param cur cursor object
bool mouseCameraMove(GLFWwindow *window, AFei::Camera &cam, AFei::Cursor &cur);


#endif