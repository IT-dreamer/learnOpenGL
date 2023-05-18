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

bool texture2DRGBBind(GLuint texture, const char *texture_path)
{
    bool result = false;
    int textureWidth, textureHeight;
    auto image = SOIL_load_image(texture_path, &textureWidth, &textureHeight, 0, SOIL_LOAD_RGB);

    if(image)
    {
        //bind the target texture to object
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);

        //unbind current texture
        SOIL_free_image_data(image);

        result = true;
        return result;
    }
    else
    {
        std::cerr << "Failed to load texture: " << texture_path;
        std::cerr << std::endl;
        return result;
    }
}

bool keyboardCameraMove(GLFWwindow *window, AFei::Camera &cam, float speed_factor)
{
    if(cam.is_keyboard_move)
    {
        static float lastFrame = 0.0f; // last frame time    
        static float deltaTime = 0.0f; // the time difference between current time and last frame time
        float currentTime = glfwGetTime();

        deltaTime = currentTime - lastFrame;
        lastFrame = currentTime;

        float camera_speed = deltaTime * speed_factor;

        auto cameraPosition = cam.getPosition();
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            cameraPosition += camera_speed * cam.getDirection();
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            cameraPosition -= camera_speed * cam.getDirection();
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            cameraPosition -= glm::normalize(glm::cross(cam.getDirection(), cam.getUp())) * camera_speed;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            cameraPosition += glm::normalize(glm::cross(cam.getDirection(), cam.getUp())) * camera_speed;
        
        auto temp = glm::normalize(glm::cross(cam.getDirection(), cam.getUp()));
        cam.setPosition(cameraPosition);
        
        return true;
    }
    else
    {
        return false;
    }
}

bool mouseCameraMove(GLFWwindow *window, AFei::Camera &cam, AFei::Cursor &cur)
{
    if(cam.is_mouse_move)
    {
        static bool firstMouse = true;
        static float lastX = 400;
        static float lastY = 300;
        static float yaw   = -90.0f;
        static float pitch =  0.0f;

        if(firstMouse)
        {
            lastX = cur.getX();
            lastY = cur.getY();
            firstMouse = false;
        }

        float xOffSet = cur.getX() - lastX;
        float yOffSet = lastY - cur.getY();
        lastX = cur.getX();
        lastY = cur.getY();

        xOffSet *= cur.cursorSpeed;
        yOffSet *= cur.cursorSpeed;
        yaw += xOffSet;
        pitch += yOffSet;
        if(pitch > 89.0f)   pitch = 89.0f;
        if(pitch < -89.0f)  pitch = -89.0f;

        glm::vec3 front;
        front.x = cos(glm::radians(yaw) * cos(glm::radians(pitch)));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        front = glm::normalize(front);
        cam.setDirection(front);

        return true;
    }
    else
    {
        return false;
    }
}
