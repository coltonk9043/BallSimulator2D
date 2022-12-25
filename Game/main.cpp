#include "Common.h"

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "Entity.h"
#include <chrono>
#include <random>

using timer = std::chrono::steady_clock;
const char* title = "Particle Simulator";
GLuint shaderProgram;

static std::vector<Entity*> entities;

void initGLFW(unsigned int versionMajor, unsigned int versionMinor) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, versionMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, versionMinor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // MacOS specific parameter
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
}

/// <summary>
/// Creates a Window with a given title, width, and height.
/// </summary>
/// <param name="window">The reference to the Window to be created.</param>
/// <param name="title">The title of the screen.</param>
/// <param name="width">Thw width of the screen.</param>
/// <param name="height">The height of the screen.</param>
/// <param name="framebufferSizeCallback">The callback if the screen size is changed.</param>
void createWindow(GLFWwindow*& window, 
    const char* title) {
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, title, NULL, NULL);
    if (!window) {
        return;
    }
    glfwMakeContextCurrent(window);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
}

/// <summary>
/// Loads the GLAD library for compiling shaders.
/// </summary>
/// <returns>Whether or not the library was loaded properly.</returns>
bool loadGlad() {
    return gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

// read file
std::string readFile(const char* filename) {
    std::ifstream file;
    std::stringstream buf;

    std::string ret = "";

    // open file
    file.open(filename);

    if (file.is_open()) {
        // read buffer
        buf << file.rdbuf();
        ret = buf.str();
    }
    else {
        std::cout << "Could not open " << filename << std::endl;
    }

    // close file
    file.close();

    return ret;
}

// generate shader
int genShader(const char* filepath, GLenum type) {
    std::string shaderSrc = readFile(filepath);
    const GLchar* shader = shaderSrc.c_str();

    // build and compile shader
    int shaderObj = glCreateShader(type);
    glShaderSource(shaderObj, 1, &shader, NULL);
    glCompileShader(shaderObj);

    // check for errors
    int success;
    char infoLog[512];
    glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shaderObj, 512, NULL, infoLog);
        std::cout << "Error in shader compilation: " << infoLog << std::endl;
        return -1;
    }

    return shaderObj;
}

// generate shader program
int genShaderProgram(const char* vertexShaderPath, const char* fragmentShaderPath) {
    int shaderProgram = glCreateProgram();

    // compile shaders
    int vertexShader = genShader(vertexShaderPath, GL_VERTEX_SHADER);
    int fragmentShader = genShader(fragmentShaderPath, GL_FRAGMENT_SHADER);

    if (vertexShader == -1 || fragmentShader == -1) {
        return -1;
    }

    // link shaders
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // check for errors
    int success;
    char infoLog[512];
    glGetShaderiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "Error in shader linking: " << infoLog << std::endl;
        return -1;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

// set projection
void setOrthographicProjection(int shaderProgram,
    float left, float right,
    float bottom, float top,
    float near, float far) {
    float mat[4][4] = {
        { 2.0f / (right - left), 0.0f, 0.0f, 0.0f },
        { 0.0f, 2.0f / (top - bottom), 0.0f, 0.0f },
        { 0.0f, 0.0f, -2.0f / (far - near), 0.0f },
        { -(right + left) / (right - left), -(top + bottom) / (top - bottom), -(far + near) / (far - near), 1.0f }
    };

    glUseProgram(shaderProgram);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, &mat[0][0]);
}

// process input
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    // left paddle
    Vector2 movement (0.0f, 0.0f);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        movement.y = 1.0f;
    }
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        movement.y = -1.0f;
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        movement.x = -1.0f;
    }
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        movement.x = 1.0f;
    }

    for (int i = 0; i < entities.size(); i++) {
        entities[i]->force.y += 5* movement.y;
        entities[i]->force.x += 5* movement.x;
    }
}

int main() {
    // Initialize GLFW.
    initGLFW(3, 3);

    // Create window and return error if it does not initialize.
    GLFWwindow* window = nullptr;
    createWindow(window, title);
    if (!window) {
        std::cout << "GLERROR: Could not create window." << std::endl;
        glfwTerminate();
        return -1;
    }

    // Load GLAD and return error if it does not initialize.
    if (!loadGlad()) {
        std::cout << "GLERROR: Could not initialize GLAD." << std::endl;
        glfwTerminate();
        return -1;
    }

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    // shaders
    shaderProgram = genShaderProgram("main.vs", "main.fs");
    setOrthographicProjection(shaderProgram, 0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0.0f, 1.0f);

    for (int i = 0; i < 3; i++) {
        entities.push_back(new Entity(Vector2(rand() % SCREEN_WIDTH - 20, rand() % SCREEN_HEIGHT - 20)));
    }

    double tickspersecond = 1.0 / TIMESTEP;
    double lastTime = glfwGetTime();
    double deltaTime = 0, nowTime = 0;

    // Render and Logic loop.
    while (!glfwWindowShouldClose(window)) {
        // - Measure time
        nowTime = glfwGetTime();
        deltaTime += (nowTime - lastTime) / tickspersecond;
        lastTime = nowTime;

        // Process input of the Scene
        processInput(window);

        // Clear the screen for a new frame.
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Updates entity in scene.
        while (deltaTime >= 1.0) {
            for (int i = 0; i < entities.size(); i++) {
                entities[i]->Update();
            }
            deltaTime--;
        }
        
        // Bind Shader and Render objects.
        glUseProgram(shaderProgram);
        for (int i = 0; i < entities.size(); i++) {
            entities[i]->Render(deltaTime);
        }
        
        // Swap Frame Buffers and poll for events.
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup memory
    for (int i = 0; i < entities.size(); i++) {
        delete entities[i];
    }

    glDeleteProgram(shaderProgram);
    glfwTerminate();
    return 0;
}