#include "Utils.h"

using std::string;

string readShaderSource(const char *filePath)
{
    try
    {
        string content;
        std::ifstream fileStream(filePath, std::ios::in);
        string line(" ");
        while(!fileStream.eof())
        {
            getline(fileStream, line);
            content.append(line + "\n");
        }
        fileStream.close();
        return content;
    }
    catch(std::ifstream::failure &e)
    {
        std::cerr << e.what() << '\n';
        exit(EXIT_FAILURE);
    }
}

GLuint creatShaderProgram(const char *vertexFile, const char *fragmentFile)
{
    GLint vertCompiled;
    GLint linked;

    auto vShaderStr = readShaderSource(vertexFile);
    auto fShaderStr = readShaderSource(fragmentFile);

    const char *vshaderSource = vShaderStr.c_str();
    const char *fshaderSource = fShaderStr.c_str();

    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vShader, 1, &vshaderSource, NULL);
    glShaderSource(fShader, 1, &fshaderSource, NULL);

    glCompileShader(vShader);
    checkOpenGLError();
    glGetShaderiv(vShader, GL_COMPILE_STATUS, &vertCompiled);
    if(vertCompiled != 1)
    {
        std::cerr << "vertex compilation failed" << std::endl;
        printShaderLog(vShader);
    }

    glCompileShader(fShader);
    checkOpenGLError();
    glGetShaderiv(fShader, GL_COMPILE_STATUS, &vertCompiled);
    if(vertCompiled != 1)
    {
        std::cerr << "fragment compilation failed" << std::endl;
        printShaderLog(fShader);
    }

    GLuint vfProgram = glCreateProgram();
    glAttachShader(vfProgram, vShader);
    glAttachShader(vfProgram, fShader);
    glLinkProgram(vfProgram);
    checkOpenGLError();
    glGetProgramiv(vfProgram, GL_LINK_STATUS, &linked);
    if(linked != 1)
    {
        std::cerr << "linking failed" << std::endl;
        printProgramLog(vfProgram);
    }
    glDeleteShader(vShader);
    glDeleteShader(fShader);
    return vfProgram;
}

GLFWwindow *openglInit(int window_width, int window_height, const char *window_name, GLFWmonitor *monitor, GLFWwindow *share)
{
    int fw_err = glfwInit();
    if(!fw_err)
    {
        std::cerr << "GLFW init fail" << std::endl;
        return nullptr;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(window_width, window_height, window_name, monitor, share);
    if(window == nullptr)
    {
        std::cerr << window_name << "window create failed" << std::endl;
        return nullptr;
    }
    glfwMakeContextCurrent(window);

    GLenum ew_err = glewInit();
    if(ew_err != GLEW_OK)
    {
        std::cerr << "GLEW init fail" << std::endl;
        std::cerr << "Error: %s" << glewGetErrorString(ew_err) << std::endl;
        return nullptr;
    }

    return window;
}

void printShaderLog(GLuint shader)
{
    int len = 0;
    int chWrittn = 0;
    char *log;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
    if(len > 0)
    {
        log = (char *)malloc(len);
        glGetShaderInfoLog(shader, len, &chWrittn, log);
        std::cerr << "Shader Info Log: " << log << std::endl;
        free(log); 
    }
}

void printProgramLog(int prog)
{
    int len = 0;
    int chWritten = 0;
    char *log;
    glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
    if(len > 0)
    {
        log = (char *)malloc(len);
        glGetProgramInfoLog(prog, len, &chWritten, log);
        std::cerr << "Program Info Log: " << log << std::endl;
        free(log);
    }
}

bool checkOpenGLError()
{
    bool foundError = false;
    int glErr = glGetError();
    while(glErr != GL_NO_ERROR)
    {
        std::cerr << "glError: " << glErr << std::endl;
        foundError = true;
        glErr = glGetError();
    }
    return foundError;
}